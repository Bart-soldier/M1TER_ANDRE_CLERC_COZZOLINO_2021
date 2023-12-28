#include "DemoTER/glwrapper/Display.hpp"

#include "DemoTER/utils/Mouse.hpp"
#include <stdexcept>

void emptyCallback() {}
void emptyCallback2(float, float) {}

Display *Display::instance = nullptr;

Display::Display(const char *title): drawCallback{emptyCallback}, drawImGuiCallback{emptyCallback}, resizeCallback{emptyCallback2}, width{600}, height{600} {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if(window == NULL) {
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeLimits(window, 128, 64, GLFW_DONT_CARE, GLFW_DONT_CARE);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}

	glfwSwapInterval(1);

	///////////////////
	// ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();
	///////////////////

	enable(GL_BLEND);
	enable(GL_DEPTH_TEST);
	enable(GL_CULL_FACE);
	enable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
}

Display::~Display() {}

void Display::init(const char *title) {
	if(instance == nullptr) instance = new Display{title};

	Mouse::init();
}

Display *Display::getInstance() {
	return instance;
}

int Display::getWidth() {
	return width;
}

int Display::getHeight() {
	return height;
}

void Display::start() {
	glfwSetWindowSizeCallback(window, resizeHandle);
	//glfwSetFramebufferSizeCallback(window, resizeCallBack);
	glfwSetMouseButtonCallback(window, mouseButtonHandle);
	glfwSetCursorPosCallback(window, cursorPosHandle);
	glfwSetScrollCallback(window, scrollHandle);

	while(!glfwWindowShouldClose(window)) {
		drawCallback();
		bindDefaultFrameBuffer();

		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);

		///////////////////
		// ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		drawImGuiCallback();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		///////////////////

		Mouse::update();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
}

void Display::onDraw(void(*callback)(void)) {
	drawCallback = callback;
}

void Display::onDrawImGui(void(*callback)(void)) {
	drawImGuiCallback = callback;
}

void Display::resizeHandle(GLFWwindow *window, int width, int height) {
	if(width < 1) width = 1;
	if(height < 1) height = 1;

	Display::getInstance()->width = width;
	Display::getInstance()->height = height;

	instance->resizeCallback(width, height);
}

void Display::mouseButtonHandle(GLFWwindow *window, int button, int action, int mods) {
	if(!ImGui::GetIO().WantCaptureMouse) Mouse::buttonEvent(button, action, mods);
}

void Display::cursorPosHandle(GLFWwindow *window, double x, double y) {
	if(!ImGui::GetIO().WantCaptureMouse) Mouse::moveEvent(x, y);
}

void Display::scrollHandle(GLFWwindow *window, double xoffset, double yoffset) {
	if(!ImGui::GetIO().WantCaptureMouse) Mouse::scrollEvent(xoffset, yoffset);
}

void Display::onResize(void(*callback)(float, float)) {
	resizeCallback = callback;
}

void Display::enable(GLenum e) {
	glEnable(e);
}

void Display::disable(GLenum e) {
	glDisable(e);
}

void Display::setClearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

void Display::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::depthFunc(GLenum e) {
	glDepthFunc(e);
}

void Display::bindDefaultFrameBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, width, height);
}

void Display::blenFunc(GLenum sfactor, GLenum dfactor) {
	glBlendFunc(sfactor, dfactor);
}
