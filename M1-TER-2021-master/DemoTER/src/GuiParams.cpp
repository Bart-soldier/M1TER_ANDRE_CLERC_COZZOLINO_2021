#include "DemoTER/GuiParams.hpp"

int GuiParams::showCubeMap = 0;
bool GuiParams::showBloom = false;

std::string GuiParams::environmentMap = "textures/environments/Arches_E_PineTree.hdr";
bool GuiParams::environmentChanged = false;

int GuiParams::selectedObject = -1;
bool GuiParams::selectedObjectChanged = false;

bool GuiParams::materialChanged = false;
int GuiParams::material = -1;
float GuiParams::customColor[3] = {1,0,0};
float GuiParams::customNormal[3] = {.5,.5,1};
float GuiParams::customRough = 0;
float GuiParams::customMetal = 0;
float GuiParams::customAO = 1;

float GuiParams::exposure = 1;
float GuiParams::gamma = 2.2;

bool GuiParams::displaySkybox = true;

int GuiParams::bloomSelect = 0;
