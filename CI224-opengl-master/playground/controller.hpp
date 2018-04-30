#ifndef CONTROLLER_H
#define CONTROLLER_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include "model.hpp"
#include "view.hpp"

class Controller {

private:

	Model* model;   // Model of game
	View*  view;    // View of game
	double deltaTime;
	double currentFrame;
	double lastFrame;
	double speed;

public:
	Controller(Model* model, View *view);
	~Controller();

	void loop();
	double getDeltaTime();
};
#endif