#include "gameObject.hpp"

std::vector<unsigned short> indices;
std::vector<glm::vec3> vertices;
std::vector<glm::vec3> colors;
std::vector<glm::vec2> uvs;
std::vector<glm::vec3> normals;

GameObject::GameObject() {

}

GameObject::~GameObject() {

}

void GameObject::loadObject(char *filename) {
	bool res = loadOBJ(filename, vertices, uvs, normals);
}

std::vector<unsigned short> getIndices() {
	return indices;
}

std::vector<glm::vec3> getVertices() {
	return vertices;
}

std::vector<glm::vec3> getColors() {
	return colors;
}

std::vector<glm::vec2> getUVs() {
	return uvs;
}

std::vector<glm::vec3> getNormals() {
	return normals;
}