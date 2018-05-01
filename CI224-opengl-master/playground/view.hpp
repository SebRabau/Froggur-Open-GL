#ifndef VIEW_H
#define VIEW_H

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
#include "gameObject.hpp"
#include "view.hpp"
#include "common/objloader.hpp"
#include "common/shader.hpp"


class View {

private:
	GLuint programID;
	GLuint MatrixID;
	GLuint LightID;
	GLuint CameraID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint VertexArrayID;

	//screen size
	int widthV;
	int heightV;
	bool once;
	glm::vec3 lightPosition;
	glm::vec3 cameraPosition;

public:
	View(int widtht, int heightt);
	~View();
	GLFWwindow* getWindow();
	void draw(GLuint *buffer, int size);
	int initialise();
	int getWidth();
	int getHeight();
	//void update(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, char* text);
	//glm::mat4 getMVPMatrix(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, glm::mat4 ModelMatrix);
};
#endif