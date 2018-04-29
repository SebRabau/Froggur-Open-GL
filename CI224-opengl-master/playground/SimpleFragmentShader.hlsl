#version 330 core



// Ouput data

out vec3 color;



void main() {



	// Output color = color specified in the vertex shader,

	// interpolated between all 3 surrounding vertices

	color = vec3(1.0, 0.0, 0.0);



}