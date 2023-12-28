#include <iostream>
#include <memory>
#include "DemoTER/glwrapper/Display.hpp"
#include "DemoTER/glwrapper/FrameBuffer.hpp"

#include "DemoTER/utils/Mouse.hpp"
#include "DemoTER/utils/OrbitCamera.hpp"
#include "DemoTER/utils/Parser.hpp"

#include "DemoTER/GuiDrawFunctions.hpp"

#include "DemoTER/PBRShader.hpp"
#include "DemoTER/FlatShader.hpp"
#include "DemoTER/MergeShader.hpp"
#include "DemoTER/Mesh.hpp"
#include "DemoTER/utils/Transform.hpp"

#include "DemoTER/glwrapper/VAO.hpp"
#include "DemoTER/glwrapper/CubeMapTexture.hpp"
#include "DemoTER/glwrapper/MSTexture.hpp"
#include "DemoTER/glwrapper/MSDepthTexture.hpp"
#include "DemoTER/SkyboxShader.hpp"

#include "DemoTER/Environment.hpp"
#include "DemoTER/GuiParams.hpp"
#include "DemoTER/Materials.hpp"
#include "DemoTER/LightsSet.hpp"

#include "DemoTER/BloomFilter.hpp"

#include <glm/gtc/type_ptr.hpp>

#include "DemoTER/CheckError.hpp"

struct Object: public Transform {
	Object(std::string name, bool displayed, std::shared_ptr<Mesh> mesh, std::shared_ptr<Materials::Material> material):
		name{name}, displayed{displayed}, mesh{mesh}, material{material} {}

	std::string name;
	bool displayed;
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Materials::Material> material;
}; /**< Une structure pour un objet. Elle comprend son nom, son maillage et son matériau. */

std::vector<std::shared_ptr<Object>> sceneObjects; /**< Un vecteur d'objets. Comprend tous les objets présents dans la scène. */

std::shared_ptr<FrameBuffer> msFrameBuffer;
std::shared_ptr<FrameBuffer> resolvedFBTex0;
std::shared_ptr<FrameBuffer> resolvedFBTex1;

std::shared_ptr<Object> cerberus;
std::shared_ptr<Object> sword;
std::shared_ptr<Object> statue;
std::shared_ptr<Object> uvSphere;
std::vector<std::shared_ptr<Object>> spheres;
std::shared_ptr<Mesh> sphere;

Display *display;
std::shared_ptr<MergeShader> mergeShader;
std::shared_ptr<VAO> fullScreenTri;

std::shared_ptr<PBRShader> pbrShader;
std::shared_ptr<FlatShader> flatShader;
std::shared_ptr<OrbitCamera> camera;
std::shared_ptr<LightsSet> lightsSet;

std::shared_ptr<SkyboxShader> skyboxShader;
std::shared_ptr<VAO> cubeVao;
std::shared_ptr<CubeMapTexture> skyboxCM;
std::shared_ptr<CubeMapTexture> irradianceCM;
std::shared_ptr<CubeMapTexture> prefiterCM;
std::shared_ptr<Texture> brdfLUT;
std::shared_ptr<CubeMapTexture> blackCM;

std::shared_ptr<BloomFilter> bloomFilter;
BloomFilter::Result bloomedTextures;

/**
* Appellée à chaque fois que la fenêtre change de taille : définit la matrice de projection pour la camera.
*/
void resize(float width, float height) {
	camera->setRatio(width / height);
	msFrameBuffer->resizeAll(width, height);
	resolvedFBTex0->resizeAll(width, height);
	resolvedFBTex1->resizeAll(width, height);
	bloomFilter->resize(width, height);
}

/**
* Appellée à chaque frame : dessine tout ce qui est visible à l'écran.
*/
void draw() {
	msFrameBuffer->bind();
	display->clear(); // Nettoie l'écran

	camera->update();

	lightsSet->update(); // prepare les buffers de positions et de couleurs des lumieres pour les envoyer au shader

	pbrShader->bind();
	pbrShader->setCamera(camera.get());
	pbrShader->setLights(lightsSet->getLightPositions(), lightsSet->getLightColors());
	pbrShader->setExposure(GuiParams::exposure);

	if(GuiParams::displaySkybox) {
		irradianceCM->bind(PBRShader::T_IRRADIANCE);
		prefiterCM->bind(PBRShader::T_PREFILTER);
	} else {
		blackCM->bind(PBRShader::T_IRRADIANCE);
		blackCM->bind(PBRShader::T_PREFILTER);
	}
	brdfLUT->bind(PBRShader::T_BRDFLUT);

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//Affichage des objets
	uvSphere->rotateY(.001);

	for(std::shared_ptr<Object> &o : sceneObjects) {
		if(o->displayed) {
			pbrShader->render(o->mesh.get(), o->material.get(), o->toMatrix());
		}
	}

	//////////////////////////////////////////////////////
	//Affichage des lumieres
	flatShader->bind();
	flatShader->setCamera(camera.get());
	flatShader->setExposure(GuiParams::exposure);

	for(int i = 0; i < lightsSet->getLightCount(); ++i) {
		LightsSet::Light &light = lightsSet->light(i);

		if(light.isOn()) {
			flatShader->sendMat4(FlatShader::U_MODEL, light.toMatrix());
			flatShader->sendVec3(FlatShader::U_COLOR, light.getColor());

			sphere->draw();
		}
	}

	//////////////////////////////////////////////////////
	// Affichage de la carte d'environnement
	if(GuiParams::displaySkybox) {
		skyboxShader->bind();
		skyboxShader->setCamera(camera.get());

		skyboxShader->setExposure(GuiParams::exposure);

		if(GuiParams::showCubeMap == 1) irradianceCM->bind(0);
		else if(GuiParams::showCubeMap == 2) prefiterCM->bind(0);
		else skyboxCM->bind(0);

		display->depthFunc(GL_LEQUAL);
		cubeVao->draw();
		display->depthFunc(GL_LESS);
	}

	//////////////////////////////////////////////////////

	// Resulution des buffers multisamples
	msFrameBuffer->blitTo(0, resolvedFBTex0.get());
	msFrameBuffer->blitTo(1, resolvedFBTex1.get());

	// execution du bloom
	bloomedTextures = bloomFilter->apply(resolvedFBTex1.get(), 0);

	// applique le bloom et effectue le tone mapping
	display->bindDefaultFrameBuffer();
	display->disable(GL_DEPTH_TEST);
	mergeShader->bind();
	mergeShader->setGamma(GuiParams::gamma);
	mergeShader->setShowBloom(GuiParams::showBloom);
	resolvedFBTex0->getTexture(0)->bind(MergeShader::T_BASE);
	bloomedTextures.b5->bind(MergeShader::T_BLOOM);
	fullScreenTri->draw();
	display->enable(GL_DEPTH_TEST);

	//////////////////////////////////////////////////////


	// Lorsque l'environnement a été changé
	if(GuiParams::environmentChanged) {
		std::shared_ptr<Environment::Result> envMaps = Environment::createIBL(GuiParams::environmentMap.c_str());
		skyboxCM = envMaps->skybox;
		irradianceCM = envMaps->irradiance;
		prefiterCM = envMaps->prefilter;
		GuiParams::environmentChanged = false;
	}


	// Lorsque le matériau de l'objet sélectionné a été changé
	if (GuiParams::materialChanged) {
		if (GuiParams::material == Materials::CUSTOM) {
			sceneObjects[GuiParams::selectedObject]->material = std::shared_ptr<Materials::Material>{Materials::customMaterial(GuiParams::customColor,
				GuiParams::customNormal, GuiParams::customRough, GuiParams::customMetal, GuiParams::customAO)};
			GuiParams::materialChanged = false;
		}
		else {
			sceneObjects[GuiParams::selectedObject]->material = std::shared_ptr<Materials::Material>{Materials::changeMaterial(GuiParams::material)};
			GuiParams::materialChanged = false;
		}
	}

	// Lorsque l'objet sélectionné a été changé
	if (GuiParams::selectedObjectChanged) {
		GuiParams::material = -1;
		GuiParams::selectedObjectChanged = false;
	}
}

/**
* Cette méthode s'occupe de tout ce qui correspond à l'interface graphique.
*/
void drawUi() {
	//////// Scène ///////
	drawSettings();

	//////// Bloom texture ///////
	ImGui::Begin("Bloom");
	if(ImGui::RadioButton("bloom5", GuiParams::bloomSelect == 0)) GuiParams::bloomSelect = 0;
	if(ImGui::RadioButton("bloom9", GuiParams::bloomSelect == 1)) GuiParams::bloomSelect = 1;
	if(ImGui::RadioButton("bloom11", GuiParams::bloomSelect == 2)) GuiParams::bloomSelect = 2;

	switch(GuiParams::bloomSelect) {
		case 0: ImGui::Image((ImTextureID)bloomedTextures.b5->getId(), ImVec2(display->getWidth(), display->getHeight()), ImVec2(0, 1), ImVec2(1, 0)); break;
		case 1: ImGui::Image((ImTextureID)bloomedTextures.b9->getId(), ImVec2(display->getWidth(), display->getHeight()), ImVec2(0, 1), ImVec2(1, 0)); break;
		case 2: ImGui::Image((ImTextureID)bloomedTextures.b11->getId(), ImVec2(display->getWidth(), display->getHeight()), ImVec2(0, 1), ImVec2(1, 0)); break;
	}
	ImGui::End();

	//////// Environnements ///////
	drawEnvSelector();

	//////// Matériaux ///////
	drawMaterialSelector();

	//////// Objets ///////
	ImGui::Begin("Object Selector");
	if(ImGui::CollapsingHeader("Spheres")) {
		for(int index = 0; index < 49; index++) {
			if(ImGui::RadioButton(sceneObjects[index]->name.c_str(), GuiParams::selectedObject == index)) {
				GuiParams::selectedObject = index;
				GuiParams::selectedObjectChanged = true;
			}
		}
	}

	for(int index = 49; index < sceneObjects.size(); index++) {
		if(ImGui::RadioButton(sceneObjects[index]->name.c_str(), GuiParams::selectedObject == index)) {
			GuiParams::selectedObject = index;
			GuiParams::selectedObjectChanged = true;
		}
	}
	ImGui::End();

	ImGui::Begin("Objects");
	ImGui::Checkbox("Display Spheres", &sceneObjects[0]->displayed);
	if(sceneObjects[0]->displayed) ImGui::SliderFloat3("Position Spheres", &sceneObjects[0]->getPosition()[0], -10, 10);
	glm::mat4x4 &shpereOrigin = sceneObjects[0]->toMatrix();

	for(int index = 1; index < 49; index++) {
		sceneObjects[index]->displayed = sceneObjects[0]->displayed;
		sceneObjects[index]->setOrigin(shpereOrigin);
	}
	for (int index = 49; index < sceneObjects.size(); index++) {
		ImGui::Checkbox(("Display " + sceneObjects[index]->name).c_str(), &sceneObjects[index]->displayed);
		if(sceneObjects[index]->displayed) {
			ImGui::SliderFloat3(("Position " + sceneObjects[index]->name).c_str(), &sceneObjects[index]->getPosition()[0], -10, 10);
		}
	}
	ImGui::End();

	//////// Lumières ///////
	ImGui::Begin("Lighting Manager");
	for(int i = 0; i < lightsSet->getLightCount(); ++i) {
		LightsSet::Light &light = lightsSet->light(i);
		bool on = light.isOn();
		ImGui::Checkbox(std::string("Light ").append(std::to_string(i)).c_str(), &on);
		light.setOn(on);

		if (light.isOn()) {
			ImGui::SliderFloat(std::string("Intensity ").append(std::to_string(i)).c_str(), &light.getIntensity(), 0, 500);
			ImGui::ColorEdit3(std::string("Color ").append(std::to_string(i)).c_str(), glm::value_ptr(light.getColor()));
			ImGui::SliderFloat3(std::string("Position ").append(std::to_string(i)).c_str(), glm::value_ptr(light.getPosition()), -10, 10);
		}
	}
	ImGui::End();
}

/**
* Le main du programme. Initialise tous les paramètres de la scène, la création des objets et lance la boucle d'affichage principale.
*/
int main() {
	// Creation de la fenetre
	Display::init("ANDRE, CLERC, COZZOLINO - Modele de rendu physiquement realiste en OpenGL 3.3");
	display = Display::getInstance();
	display->setClearColor(0, 0, 0);

	// Creation des framebuffers
	Texture::Params params;
	params.correctGamma = false;
	params.createMips = false;
	params.hdr = true;

	Texture::Options opts;
	opts.magFilter = GL_LINEAR;
	opts.minFilter = GL_LINEAR;

	msFrameBuffer = std::make_shared<FrameBuffer>();
	msFrameBuffer->setTexture(std::make_shared<MSTexture>(display->getWidth(), display->getHeight()), 0);
	msFrameBuffer->setTexture(std::make_shared<MSTexture>(display->getWidth(), display->getHeight()), 1);
	msFrameBuffer->setDepthTexture(std::make_shared<MSDepthTexture>(display->getWidth(), display->getHeight()));
	
	msFrameBuffer->prepare();
	msFrameBuffer->unbind();

	//////////

	resolvedFBTex0 = std::make_shared<FrameBuffer>();
	resolvedFBTex0->setTexture(std::make_shared<Texture>(display->getWidth(), display->getHeight(), params, opts), 0);
	resolvedFBTex0->prepare();
	resolvedFBTex0->unbind();

	resolvedFBTex1 = std::make_shared<FrameBuffer>();
	resolvedFBTex1->setTexture(std::make_shared<Texture>(display->getWidth(), display->getHeight(), params, opts), 0);
	resolvedFBTex1->prepare();
	resolvedFBTex0->unbind();


	bloomFilter = std::make_shared<BloomFilter>(display->getWidth(), display->getHeight());

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Creations des shaders (et du triangle fullscreen)
	mergeShader = std::make_shared<MergeShader>();
	fullScreenTri = std::make_unique<VAO>();
	std::shared_ptr<VBO> trianglePos = std::make_shared<VBO>(
		std::vector<glm::vec3>{
			glm::vec3(-1, -1, 0),
			glm::vec3(3, -1, 0),
			glm::vec3(-1, 3, 0)
	}, MergeShader::A_POSITION);
	fullScreenTri->addVBO(trianglePos);
	fullScreenTri->prepare();

	pbrShader = std::make_shared<PBRShader>();
	flatShader = std::make_shared<FlatShader>();
	camera = std::make_shared<OrbitCamera>();

	// Creations des lumieres
	lightsSet = std::make_shared<LightsSet>(PBRShader::MAX_LIGHT_COUNT);
	const float p = 7 * .2 + 1;
	const float d = 4;
	lightsSet->light(0).setPosition(-1, -1, d);
	lightsSet->light(1).setPosition(p, -1, d);
	lightsSet->light(2).setPosition(-1, p, d);
	lightsSet->light(3).setPosition(p, p, d);
	for(int i = 0; i < lightsSet->getLightCount(); ++i) {
		lightsSet->light(i).setColor(1, 1, 1);
		lightsSet->light(i).setIntensity(60);
	}

	// Creations des divers objets de la scene
	sphere = std::make_shared<Mesh>("meshs/sphere.obj");

	int index = 0;
	for(float x = 0; x < 7; ++x) {
		for(float y = 0; y < 7; ++y) {
			float r = x / 7.;
			if(r < 0.05) r = 0.05;
			float m = y / 7.;

			spheres.push_back(std::shared_ptr<Object>{ new Object{
				"Sphere " + std::to_string(index),
				true,
				sphere,
				std::shared_ptr<Materials::Material>{Materials::customMaterial(glm::vec3{.5, 0, 0}, glm::vec3{.5, .5, 1.}, glm::vec3{r}, glm::vec3{m}, glm::vec3{1})}
			}});

			spheres[index]->setPosition(x * .2, y * .2, 0);
			sceneObjects.push_back(spheres[index]);
			
			index++;
		}
	}

	uvSphere = std::shared_ptr<Object>{ new Object{"UVSphere", false, std::make_shared<Mesh>("meshs/uvsphere.obj"), std::shared_ptr<Materials::Material>{Materials::rusted_iron()}}};
	uvSphere->setPosition(0, 0, -2);
	sceneObjects.push_back(uvSphere);

	cerberus = std::shared_ptr<Object>{ new Object{"Cerberus", false, std::make_shared<Mesh>("meshs/cerberus_LP.obj"), std::shared_ptr<Materials::Material>{Materials::cerberus()}}};
	cerberus->setPosition(-4, 0, 0);
	sceneObjects.push_back(cerberus);

	sword = std::shared_ptr<Object>{ new Object{"Sword", false, std::make_shared<Mesh>("meshs/sword.obj"), std::shared_ptr<Materials::Material>{Materials::sword()}} };
	sword->setPosition(0, 0, 0);
	sceneObjects.push_back(sword);

	statue = std::shared_ptr<Object>{ new Object{"Statue", false, std::make_shared<Mesh>("meshs/statue.obj"), std::shared_ptr<Materials::Material>{Materials::statue()}} };
	statue->setPosition(0, 0, -4);
	sceneObjects.push_back(statue);

	//////////////////////////////////////////////////////
	// Creation de la skybox (le shader et le cube)
	skyboxShader = std::make_shared<SkyboxShader>();
	std::unique_ptr<Parser::Result> result = Parser::loadObj("meshs/invertCube.obj");
	cubeVao = std::make_shared<VAO>();
	std::shared_ptr<VBO> vertexVBO = std::make_shared<VBO>(result->vertex, SkyboxShader::A_POSITION);
	cubeVao->addVBO(vertexVBO); 
	cubeVao->prepare();

	// Créer la carte d'environnement par défaut
	std::shared_ptr<Environment::Result> envMaps = Environment::createIBL(GuiParams::environmentMap.c_str());
	skyboxCM = envMaps->skybox;
	irradianceCM = envMaps->irradiance;
	prefiterCM = envMaps->prefilter;
	brdfLUT = Environment::createBRDFLUT();

	// Carte d'environnement vide
	blackCM = std::make_shared<CubeMapTexture>(1, 1);
	blackCM->createMips();

	//////////////////////////////////////////////////////

	display->onResize(resize);
	display->onDraw(draw);
	display->onDrawImGui(drawUi);
	display->start();

	return 0;
}
