#include "view.hpp"
int widthV;
int heightV;
std::string lightProj = "projection";
std::string lightView = "view";
std::string lightMod = "model";
vec3 lightPos(-4, 8, 0);
std::string lightPoss = "lightPos"; 
//std::string lightPoss = "LightPosition_worldspace";

View::View(int widtht, int heightt) {
	widthV = widtht;
	heightV = heightt;
}

View::~View() {

}

void View::draw(GLuint *vbuffer, int vsize, GLuint *cbuffer, GLuint *nbuffer, GLuint program, bool isPlayer, bool isObj, Camera camera, vec3 playerTrans) {
	glUseProgram(program);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, *vbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,					// stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, *cbuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, *nbuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
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

	model = mat4();
	//model = translate(model, vec3(0.0, 0.0, 0.0));
	model = scale(model, vec3(0.2f)); 	
	model = rotate(model, (float)0.5, vec3(-45.0f, 0.0f, 0.0f));
	//model = rotate(model, (float)glfwGetTime(), vec3(0.0f, 1.0f, 1.0f));

	if (isPlayer == true) {
		model = translate(model, playerTrans);
				//model = scale(model, vec3(0.2f));
				//model = rotate(model, (float)glfwGetTime(), vec3(0.0f, 1.0f, 1.0f));
			
	}

	if (isObj == true) {
		model = translate(model, playerTrans);
		
	}



	//Update lighting position	
	glUniform3fv(glGetUniformLocation(program, lightPoss.c_str()), 1, &lightPos[0]);

	glUniformMatrix4fv(glGetUniformLocation(program, lightMod.c_str()), 1, GL_FALSE, &model[0][0]);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Draw the triangles
	glDrawArrays(GL_TRIANGLES, 0, vsize);

	glDisableVertexAttribArray(0);	
}

int View::getWidth() {
	return widthV;
}

int View::getHeight() {
	return heightV;
}
