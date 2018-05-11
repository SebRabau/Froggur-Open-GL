#include "view.hpp"
int widthV;
int heightV;
bool once = false;
vec3 lightPos(1.2f, 1.0f, 2.0f);
std::string lightPoss = "lightPos";
std::string lightProj = "projection";
std::string lightView = "view";

View::View(int widtht, int heightt) {
	widthV = widtht;
	heightV = heightt;
}

View::~View() {

}

void View::draw(GLuint *buffer, int size, GLuint program, GLuint light, Camera camera) {
	glUseProgram(program);	

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

	// update the uniform color
	float timeValue = glfwGetTime();
	float greenValue = sin(timeValue) / 2.0f + 0.5f;
	int vertexColorLocation = glGetUniformLocation(program, "ourColor");
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);	

	//Update lighting position	
	glUniform3fv(glGetUniformLocation(light, lightPoss.c_str()), 1, &lightPos[0]);

	// view/projection transformations
	mat4 projection = perspective(radians(camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
	mat4 view = camera.GetViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(light, lightProj.c_str()), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(light, lightView.c_str()), 1, GL_FALSE, &view[0][0]);

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
