#include "view.hpp"
int widthV;
int heightV;
bool once = false;
std::string lightProj = "projection";
std::string lightView = "view";
std::string lightMod = "model";
vec3 lightPos(1.2f, 1.0f, 2.0f);
std::string lightPoss = "lightPos";


View::View(int widtht, int heightt) {
	widthV = widtht;
	heightV = heightt;
}

View::~View() {

}

void View::draw(GLuint *buffer, int size, GLuint program, bool islight, Camera camera) {
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

	// view/projection transformations
	mat4 projection = perspective(radians(camera.Zoom), (float)widthV / (float)heightV, 0.1f, 100.0f);
	mat4 view = camera.GetViewMatrix();
	mat4 model;
	glUniformMatrix4fv(glGetUniformLocation(program, lightProj.c_str()), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, lightView.c_str()), 1, GL_FALSE, &view[0][0]);

	if (light) {
		model = mat4();
		model = translate(model, lightPos);
		model = scale(model, vec3(0.2f));
	}
	glUniformMatrix4fv(glGetUniformLocation(program, lightMod.c_str()), 1, GL_FALSE, &model[0][0]);


	// Draw the triangles
	glDrawArrays(GL_TRIANGLES, 0, size * sizeof(glm::vec3));

	//Update lighting position	
	glUniform3fv(glGetUniformLocation(light, lightPoss.c_str()), 1, &lightPos[0]);

	glDisableVertexAttribArray(0);	
}

int View::getWidth() {
	return widthV;
}

int View::getHeight() {
	return heightV;
}
