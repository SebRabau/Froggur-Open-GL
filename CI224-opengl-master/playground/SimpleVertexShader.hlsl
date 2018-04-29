#version 330 core

// Input vertex data

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

void main() {

	// Output position of the vertex
	gl_Position.xyz = vertexPosition_modelspace;

	// UV of the vertex. 
	UV = vertexUV;
}