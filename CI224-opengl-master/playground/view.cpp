#include "view.hpp"
int widthV;
int heightV;
bool once = false;

View::View(int widtht, int heightt) {
	widthV = widtht;
	heightV = heightt;
}

View::~View() {

}

void View::draw(GLuint *buffer, int size) {
	glUseProgram(programID);
	// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
	glClear(GL_COLOR_BUFFER_BIT);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangles
	glDrawArrays(GL_TRIANGLES, 0, size * sizeof(glm::vec3));

	glDisableVertexAttribArray(0);	
}

int View::getWidth() {
	return widthV;
}

int View::getHeight() {
	return heightV;
}

