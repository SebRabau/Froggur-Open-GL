#ifndef MODEL_H
#define MODEL_H

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
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Model {

private:
	GameObject* board;
	GameObject* player;
	std::vector<GameObject*> collectables;
	GLFWwindow* window;
	View* view;

	GLuint programID;
	GLuint MatrixID;
	GLuint LightID;
	GLuint CameraID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint VertexArrayID;

	int collectables_size;
	int collected;
	bool isPause;

	//Screen size
	int heightM;
	int widthM;

public:
	Model(int width, int height, View* viewt);
	~Model();
	int initialise();
	void play();
	void createGameObjects();
	std::vector<GameObject*>  getCollectables();
	GameObject* getBoard();
	GameObject* getPlayer();
	void setCollected(int collected);
	int getCollected();
	int getCollectablesSize();
	bool hasPlayerCollidedwithObstacles();
	void deleteFromCollectables(GameObject* go);

	GLFWwindow* getGameWindow();

	void setPause(bool pauset);
	bool getPause();
};
#endif