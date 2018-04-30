#ifndef VIEW_H
#define VIEW_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;
#include "model.hpp";

class View {

private:
	Model* model;
	GLFWwindow* window;

	GLuint programID;
	GLuint MatrixID;
	GLuint LightID;
	GLuint CameraID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint VertexArrayID;

	//screen size
	int width;
	int height;
	glm::vec3 lightPosition;
	glm::vec3 cameraPosition;

public:
	View(int widtht, int heightt, Model* modelt);
	~View();
	GLFWwindow* getWindow();
	int initialise();
	int getWidth();
	int getHeight();
	//void update(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, char* text);
	//glm::mat4 getMVPMatrix(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, glm::mat4 ModelMatrix);
};
#endif