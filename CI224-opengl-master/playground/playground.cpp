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

#include <vector>
#include <iostream>
#include "model.hpp"
#include "view.hpp"
#include "controller.hpp"

int main( void )
{
	int gameWidth = 1024;
	int gameHeight = 768;
	
	//Initialise MVC	
	View* gameView = new View(gameWidth, gameHeight);
	Model* gameModel = new Model(gameWidth, gameHeight, gameView);
	//View* gameView = new View(gameWidth, gameHeight, gameModel);
	//Model* gameModel = new Model(gameWidth, gameHeight);
	Controller* gameController = new Controller(gameModel, gameView);

	gameModel->initialise();	

	gameController->execute();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

