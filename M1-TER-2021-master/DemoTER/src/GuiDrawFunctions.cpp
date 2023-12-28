#include "DemoTER/GuiDrawFunctions.hpp"

void drawSettings() {
	ImGui::Begin("Settings");
	ImGui::SliderFloat("Exposition", &GuiParams::exposure, 0, 10);
	ImGui::SliderFloat("Gamma", &GuiParams::gamma, 0, 10);
	ImGui::Checkbox("Show Bloom", &GuiParams::showBloom);
	ImGui::Checkbox("Skybox", &GuiParams::displaySkybox);
	if(ImGui::RadioButton("Default", GuiParams::showCubeMap == 0)) GuiParams::showCubeMap = 0;
	if(ImGui::RadioButton("Irradiance", GuiParams::showCubeMap == 1)) GuiParams::showCubeMap = 1;
	if(ImGui::RadioButton("Prefilter", GuiParams::showCubeMap == 2)) GuiParams::showCubeMap = 2;
	ImGui::End();
}

void drawEnvSelector() {
	ImGui::Begin("Environment Map Selector");
	if(ImGui::RadioButton("Alexs Apartment", GuiParams::environmentMap == "textures/environments/Alexs_Apt.hdr")) {
		GuiParams::environmentMap = "textures/environments/Alexs_Apt.hdr";
		GuiParams::environmentChanged = true;
	}
	if(ImGui::RadioButton("Arches PineTree", GuiParams::environmentMap == "textures/environments/Arches_E_PineTree.hdr")) {
		GuiParams::environmentMap = "textures/environments/Arches_E_PineTree.hdr";
		GuiParams::environmentChanged = true;
	}
	if(ImGui::RadioButton("Frozen Waterfall", GuiParams::environmentMap == "textures/environments/Frozen_Waterfall.hdr")) {
		GuiParams::environmentMap = "textures/environments/Frozen_Waterfall.hdr";
		GuiParams::environmentChanged = true;
	}
	if(ImGui::RadioButton("Ice Lake", GuiParams::environmentMap == "textures/environments/Ice_Lake.hdr")) {
		GuiParams::environmentMap = "textures/environments/Ice_Lake.hdr";
		GuiParams::environmentChanged = true;
	}
	if(ImGui::RadioButton("Walk Of Fame", GuiParams::environmentMap == "textures/environments/Mans_Outside.hdr")) {
		GuiParams::environmentMap = "textures/environments/Mans_Outside.hdr";
		GuiParams::environmentChanged = true;
	}
	if(ImGui::RadioButton("Milkyway", GuiParams::environmentMap == "textures/environments/Milkyway.hdr")) {
		GuiParams::environmentMap = "textures/environments/Milkyway.hdr";
		GuiParams::environmentChanged = true;
	}
	if(ImGui::RadioButton("Winter Forest", GuiParams::environmentMap == "textures/environments/WinterForest.hdr")) {
		GuiParams::environmentMap = "textures/environments/WinterForest.hdr";
		GuiParams::environmentChanged = true;
	}
	ImGui::End();
}

void drawMaterialSelector() {
	ImGui::Begin("Material Selector");
	if(ImGui::RadioButton("Bark", GuiParams::material == Materials::BARK) && GuiParams::selectedObject != -1) {
		GuiParams::material = Materials::BARK;
		GuiParams::materialChanged = true;
	}
	if(ImGui::RadioButton("Bricks", GuiParams::material == Materials::BRICKS) && GuiParams::selectedObject != -1) {
		GuiParams::material = Materials::BRICKS;
		GuiParams::materialChanged = true;
	}
	if(ImGui::RadioButton("Cerberus", GuiParams::material == Materials::CERBERUS) && GuiParams::selectedObject != -1) {
		GuiParams::material = Materials::CERBERUS;
		GuiParams::materialChanged = true;
	}
	if(ImGui::RadioButton("Ground Gravel", GuiParams::material == Materials::GROUND_GRAVEL) && GuiParams::selectedObject != -1) {
		GuiParams::material = Materials::GROUND_GRAVEL;
		GuiParams::materialChanged = true;
	}
	if(ImGui::RadioButton("Ground Ice", GuiParams::material == Materials::GROUND_ICE) && GuiParams::selectedObject != -1) {
		GuiParams::material = Materials::GROUND_ICE;
		GuiParams::materialChanged = true;
	}
	if(ImGui::RadioButton("Metal", GuiParams::material == Materials::METAL) && GuiParams::selectedObject != -1) {
		GuiParams::material = Materials::METAL;
		GuiParams::materialChanged = true;
	}
	if(ImGui::RadioButton("Metal Panel", GuiParams::material == Materials::METAL_PANEL) && GuiParams::selectedObject != -1) {
		GuiParams::material = Materials::METAL_PANEL;
		GuiParams::materialChanged = true;
	}
	if(ImGui::RadioButton("Rock Moss", GuiParams::material == Materials::ROCK_MOSS) && GuiParams::selectedObject != -1) {
		GuiParams::material = Materials::ROCK_MOSS;
		GuiParams::materialChanged = true;
	}
	if(ImGui::RadioButton("Rusted Iron", GuiParams::material == Materials::RUSTED_IRON) && GuiParams::selectedObject != -1) {
		GuiParams::material = Materials::RUSTED_IRON;
		GuiParams::materialChanged = true;
	}
	if (ImGui::RadioButton("Statue", GuiParams::material == Materials::STATUE) && GuiParams::selectedObject != -1) {
		GuiParams::material = Materials::STATUE;
		GuiParams::materialChanged = true;
	}
	if (ImGui::RadioButton("Sword", GuiParams::material == Materials::SWORD) && GuiParams::selectedObject != -1) {
		GuiParams::material = Materials::SWORD;
		GuiParams::materialChanged = true;
	}
	if(ImGui::RadioButton("Textiles Craft", GuiParams::material == Materials::TEXTILES_CRAFT) && GuiParams::selectedObject != -1) {
		GuiParams::material = Materials::TEXTILES_CRAFT;
		GuiParams::materialChanged = true;
	}
	if(ImGui::RadioButton("Wood Varnish Rough", GuiParams::material == Materials::WOOD_VARNISH_ROUGH) && GuiParams::selectedObject != -1) {
		GuiParams::material = Materials::WOOD_VARNISH_ROUGH;
		GuiParams::materialChanged = true;
	}
	if(ImGui::RadioButton("Custom", GuiParams::material == Materials::CUSTOM) && GuiParams::selectedObject != -1) {
		GuiParams::material = Materials::CUSTOM;
		GuiParams::materialChanged = true;
	}

	if(GuiParams::material == Materials::CUSTOM) {
		if(ImGui::ColorEdit3("Color", GuiParams::customColor)) {
			GuiParams::materialChanged = true;
		}
		if(ImGui::ColorEdit3("Normals", GuiParams::customNormal)) {
			GuiParams::materialChanged = true;
		}
		if(ImGui::SliderFloat("Roughness", &GuiParams::customRough, 0, 1)) {
			GuiParams::materialChanged = true;
		}
		if(ImGui::SliderFloat("Metalness", &GuiParams::customMetal, 0, 1)) {
			GuiParams::materialChanged = true;
		}
		if(ImGui::SliderFloat("Ambiant Occlusion", &GuiParams::customAO, 0, 1)) {
			GuiParams::materialChanged = true;
		}

		ImGui::Separator();

		if (ImGui::Button("Plastic") && GuiParams::selectedObject != -1) {
			GuiParams::material = Materials::CUSTOM;
			GuiParams::materialChanged = true;

			GuiParams::customColor[0] = .5;
			GuiParams::customColor[1] = .5;
			GuiParams::customColor[2] = .5;

			GuiParams::customNormal[0] = .5;
			GuiParams::customNormal[1] = .5;
			GuiParams::customNormal[2] = 1;

			GuiParams::customRough = .24;
			GuiParams::customMetal = 0;
			GuiParams::customAO = 1;
		}

		if (ImGui::Button("Iron") && GuiParams::selectedObject != -1) {
			GuiParams::material = Materials::CUSTOM;
			GuiParams::materialChanged = true;

			GuiParams::customColor[0] = .56;
			GuiParams::customColor[1] = .57;
			GuiParams::customColor[2] = .58;

			GuiParams::customNormal[0] = .5;
			GuiParams::customNormal[1] = .5;
			GuiParams::customNormal[2] = 1;

			GuiParams::customRough = .3;
			GuiParams::customMetal = 1;
			GuiParams::customAO = 1;
		}

		if (ImGui::Button("Copper") && GuiParams::selectedObject != -1) {
			GuiParams::material = Materials::CUSTOM;
			GuiParams::materialChanged = true;

			GuiParams::customColor[0] = .95;
			GuiParams::customColor[1] = .64;
			GuiParams::customColor[2] = .54;

			GuiParams::customNormal[0] = .5;
			GuiParams::customNormal[1] = .5;
			GuiParams::customNormal[2] = 1;

			GuiParams::customRough = .4;
			GuiParams::customMetal = 1;
			GuiParams::customAO = 1;
		}

		if (ImGui::Button("Silver") && GuiParams::selectedObject != -1) {
			GuiParams::material = Materials::CUSTOM;
			GuiParams::materialChanged = true;

			GuiParams::customColor[0] = .95;
			GuiParams::customColor[1] = .93;
			GuiParams::customColor[2] = .88;

			GuiParams::customNormal[0] = .5;
			GuiParams::customNormal[1] = .5;
			GuiParams::customNormal[2] = 1;

			GuiParams::customRough = .1;
			GuiParams::customMetal = 1;
			GuiParams::customAO = 1;
		}

		if (ImGui::Button("Gold") && GuiParams::selectedObject != -1) {
			GuiParams::material = Materials::CUSTOM;
			GuiParams::materialChanged = true;

			GuiParams::customColor[0] = 1;
			GuiParams::customColor[1] = .71;
			GuiParams::customColor[2] = .29;

			GuiParams::customNormal[0] = .5;
			GuiParams::customNormal[1] = .5;
			GuiParams::customNormal[2] = 1;

			GuiParams::customRough = .25;
			GuiParams::customMetal = 1;
			GuiParams::customAO = 1;
		}
	}

	ImGui::End();
}
