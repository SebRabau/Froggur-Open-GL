#include "model.hpp"

int heightM;
int widthM;
View* view;
GLFWwindow* window;
GLuint vertexbuffer;
GLuint programID;

Model::Model(int widtht, int heightt, View* viewt) {
	heightM = heightt;
	widthM = widtht;
	view = viewt;
}

int Model::initialise() {
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(widthM, heightM, "Froggur", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Setup Vertex Array
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	return 0;
}

void Model::play() {
	// Read our .obj files

	//First object
	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	bool res = loadAssImp("test.obj", indices, indexed_vertices, indexed_uvs, indexed_normals);
	
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	//std::cout << vertices.size() << std::endl;

	//Second object
	std::vector<unsigned short> indices1;
	std::vector<glm::vec3> vertices1;
	std::vector<glm::vec2> uvs1;
	std::vector<glm::vec3> normals1;
	//std::vector<unsigned int> list_vertices1;
	//bool res1 = loadAssImpMeshes("sphere.obj", indices1, vertices1, uvs1, normals1, list_vertices1);
	bool res1 = loadAssImp("test1.obj", indices1, vertices1, uvs1, normals1);

	GLuint vertexbuffer1;
	glGenBuffers(1, &vertexbuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
	glBufferData(GL_ARRAY_BUFFER, vertices1.size() * sizeof(glm::vec3), &vertices1[0], GL_STATIC_DRAW);

	programID = LoadShaders("SimpleVertexShader.hlsl", "SimpleFragmentShader.hlsl");
	do {
		view->draw(&vertexbuffer, indexed_vertices.size(), programID);
		view->draw(&vertexbuffer1, vertices1.size(), programID);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);
	//glDeleteVertexArrays(1, &VertexArrayID);
}

GLFWwindow* Model::getGameWindow() {
	return window;
}