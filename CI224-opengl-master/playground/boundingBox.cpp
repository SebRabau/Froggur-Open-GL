#include "boundingBox.hpp"

std::vector<glm::vec3> verticesBB;

vec3 boundingBoxMin;
vec3 boundingBoxMax;

//eight points of bounding box
vec3 btl;
vec3 btr;
vec3 ftl;
vec3 ftr;
vec3 fbl;
vec3 fbr;
vec3 bbl;
vec3 bbr;

BoundingBox::BoundingBox(std::vector<glm::vec3> _vertices) {
	verticesBB = _vertices;
}

void BoundingBox::initialise() {
	//std::cout << "BB1= " << verticesBB[0].x << std::endl;
	boundingBoxMin.x = boundingBoxMax.x = verticesBB[0].x;
	boundingBoxMin.y = boundingBoxMax.y = verticesBB[0].y;
	boundingBoxMin.z = boundingBoxMax.z = verticesBB[0].z;
	for (int i = 0; i < verticesBB.size(); i++) {
		if (verticesBB[i].x < boundingBoxMin.x)
			boundingBoxMin.x = verticesBB[i].x;
		if (verticesBB[i].x > boundingBoxMax.x)
			boundingBoxMax.x = verticesBB[i].x;
		if (verticesBB[i].y < boundingBoxMin.y)
			boundingBoxMin.y = verticesBB[i].y;
		if (verticesBB[i].y > boundingBoxMax.y)
			boundingBoxMax.y = verticesBB[i].y;
		if (verticesBB[i].z < boundingBoxMin.z)
			boundingBoxMin.z = verticesBB[i].z;
		if (verticesBB[i].z > boundingBoxMax.z)
			boundingBoxMax.z = verticesBB[i].z;
	}

	btl = vec3(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMin.z);
	btr = vec3(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMin.z);
	ftl = vec3(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMax.z);
	ftr = vec3(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMax.z);
	fbl = vec3(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z);
	fbr = vec3(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMax.z);
	bbl = vec3(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z);
	bbr = vec3(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z);

}

void BoundingBox::update(vec3 playerTrans) {
	/*for (int i = 0; verticesBB.size(); i++) {
		verticesBB[i] = verticesBB[i] + playerTrans;
	}*/

	boundingBoxMin.x = boundingBoxMax.x = verticesBB[0].x;
	boundingBoxMin.y = boundingBoxMax.y = verticesBB[0].y;
	boundingBoxMin.z = boundingBoxMax.z = verticesBB[0].z;
	for (int i = 0; i < verticesBB.size(); i++) {
		if (verticesBB[i].x < boundingBoxMin.x)
			boundingBoxMin.x = verticesBB[i].x;
		if (verticesBB[i].x > boundingBoxMax.x)
			boundingBoxMax.x = verticesBB[i].x;
		if (verticesBB[i].y < boundingBoxMin.y)
			boundingBoxMin.y = verticesBB[i].y;
		if (verticesBB[i].y > boundingBoxMax.y)
			boundingBoxMax.y = verticesBB[i].y;
		if (verticesBB[i].z < boundingBoxMin.z)
			boundingBoxMin.z = verticesBB[i].z;
		if (verticesBB[i].z > boundingBoxMax.z)
			boundingBoxMax.z = verticesBB[i].z;
	}

	btl += playerTrans;
	btr += playerTrans;
	ftl += playerTrans;
	ftr += playerTrans;
	fbl += playerTrans;
	fbr += playerTrans;
	bbl += playerTrans;
	bbr += playerTrans;
}

vec3 BoundingBox::getMin() {
	return boundingBoxMin;
}

vec3 BoundingBox::getMax() {
	return boundingBoxMax;
}