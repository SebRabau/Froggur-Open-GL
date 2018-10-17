#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

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

#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class BoundingBox {
private:
	std::vector<glm::vec3> verticesBB;
	vec3 boundingBoxMin;
	vec3 boundingBoxMax;

	

public:
	vec3 btl;
	vec3 btr;
	vec3 ftl;
	vec3 ftr;
	vec3 fbl;
	vec3 fbr;
	vec3 bbl;
	vec3 bbr;
	
	BoundingBox(std::vector<glm::vec3> _vertices);
	void initialise();
	void update(vec3 dir);
	vec3 getMin();
	vec3 getMax();
};
#endif