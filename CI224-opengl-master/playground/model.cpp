#include "model.hpp"

int heightM;
int widthM;
View* view;
GLFWwindow* window;
GLuint vertexbuffer;
GLuint programID;
GLuint programID2;
GLuint light;

/*void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);*/

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

// camera
Camera camera(vec3(0.0f, 0.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;


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

	glewExperimental = GL_TRUE;

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
	// Read our .obj file

	//Floor
	std::vector<glm::vec3> floorV;
	std::vector<glm::vec2> floorUV;
	std::vector<glm::vec3> floorLN; 

	//Player
	std::vector<glm::vec3> playerV;
	std::vector<glm::vec2> playerUV; 
	std::vector<glm::vec3> playerLN; 

	//LeftWall
	std::vector<glm::vec3> leftWV;
	std::vector<glm::vec2> leftWUV; 
	std::vector<glm::vec3> leftWLN; 

	//RightWall
	std::vector<glm::vec3> rightWV;
	std::vector<glm::vec2> rightWUV; 
	std::vector<glm::vec3> rightWLN; 

	//MovingObject
	std::vector<glm::vec3> movingV;
	std::vector<glm::vec2> movingUV; 
	std::vector<glm::vec3> movingLN; 
		
	//Barriers

	//1
	std::vector<glm::vec3> b1V;
	std::vector<glm::vec2> b1UV;
	std::vector<glm::vec3> b1LN;

	//2
	std::vector<glm::vec3> b2V;
	std::vector<glm::vec2> b2UV;
	std::vector<glm::vec3> b2LN;

	//3
	std::vector<glm::vec3> b3V;
	std::vector<glm::vec2> b3UV;
	std::vector<glm::vec3> b3LN;

	//4
	std::vector<glm::vec3> b4V;
	std::vector<glm::vec2> b4UV;
	std::vector<glm::vec3> b4LN;

	//5
	std::vector<glm::vec3> b5V;
	std::vector<glm::vec2> b5UV;
	std::vector<glm::vec3> b5LN;

	//6
	std::vector<glm::vec3> b6V;
	std::vector<glm::vec2> b6UV;
	std::vector<glm::vec3> b6LN;

	//7
	std::vector<glm::vec3> b7V;
	std::vector<glm::vec2> b7UV;
	std::vector<glm::vec3> b7LN;


	//Models
	bool floor = loadOBJ("floor.obj", floorV, floorUV, floorLN);
	bool player = loadOBJ("player.obj", playerV, playerUV, playerLN);
	bool leftwall = loadOBJ("leftWall.obj", leftWV, leftWUV, leftWLN);
	bool rightwall = loadOBJ("rightWall.obj", rightWV, rightWUV, rightWLN);
	bool movingObj = loadOBJ("movingObject.obj", movingV, movingUV, movingLN);
	
	bool barrier1 = loadOBJ("barrier1.obj", b1V, b1UV, b1LN);
	bool barrier2 = loadOBJ("barrier2.obj", b2V, b2UV, b2LN);
	bool barrier3 = loadOBJ("barrier3.obj", b3V, b3UV, b3LN);
	bool barrier4 = loadOBJ("barrier4.obj", b4V, b4UV, b4LN);
	bool barrier5 = loadOBJ("barrier5.obj", b5V, b5UV, b5LN);
	bool barrier6 = loadOBJ("barrier6.obj", b6V, b6UV, b6LN);
	bool barrier7 = loadOBJ("barrier7.obj", b7V, b7UV, b7LN);
	

	//Floor
	GLuint floorVB;
	glGenBuffers(1, &floorVB);
	glBindBuffer(GL_ARRAY_BUFFER, floorVB);
	glBufferData(GL_ARRAY_BUFFER, floorV.size() * sizeof(glm::vec3), &floorV[0], GL_STATIC_DRAW);

	GLuint floorCB;
	glGenBuffers(1, &floorCB);
	glBindBuffer(GL_ARRAY_BUFFER, floorCB);
	glBufferData(GL_ARRAY_BUFFER, floorUV.size() * sizeof(glm::vec3), &floorUV[0], GL_STATIC_DRAW);

	GLuint floorNB;
	glGenBuffers(1, &floorNB);
	glBindBuffer(GL_ARRAY_BUFFER, floorNB);
	glBufferData(GL_ARRAY_BUFFER, floorLN.size() * sizeof(glm::vec3), &floorLN[0], GL_STATIC_DRAW);

	//Player
	GLuint playerVB;
	glGenBuffers(1, &playerVB);
	glBindBuffer(GL_ARRAY_BUFFER, playerVB);
	glBufferData(GL_ARRAY_BUFFER, playerV.size() * sizeof(glm::vec3), &playerV[0], GL_STATIC_DRAW);

	GLuint playerCB;
	glGenBuffers(1, &playerCB);
	glBindBuffer(GL_ARRAY_BUFFER, playerCB);
	glBufferData(GL_ARRAY_BUFFER, playerUV.size() * sizeof(glm::vec3), &playerUV[0], GL_STATIC_DRAW);

	GLuint playerNB;
	glGenBuffers(1, &playerNB);
	glBindBuffer(GL_ARRAY_BUFFER, playerNB);
	glBufferData(GL_ARRAY_BUFFER, playerLN.size() * sizeof(glm::vec3), &playerLN[0], GL_STATIC_DRAW); 


	//leftWall
	GLuint leftWVB;
	glGenBuffers(1, &leftWVB);
	glBindBuffer(GL_ARRAY_BUFFER, leftWVB);
	glBufferData(GL_ARRAY_BUFFER, leftWV.size() * sizeof(glm::vec3), &leftWV[0], GL_STATIC_DRAW);

	GLuint leftWCB;
	glGenBuffers(1, &leftWCB);
	glBindBuffer(GL_ARRAY_BUFFER, leftWCB);
	glBufferData(GL_ARRAY_BUFFER, leftWUV.size() * sizeof(glm::vec3), &leftWUV[0], GL_STATIC_DRAW);

	GLuint leftWNB;
	glGenBuffers(1, &leftWNB);
	glBindBuffer(GL_ARRAY_BUFFER, leftWNB);
	glBufferData(GL_ARRAY_BUFFER, leftWLN.size() * sizeof(glm::vec3), &leftWLN[0], GL_STATIC_DRAW);


	//RightWall
	GLuint rightWVB;
	glGenBuffers(1, &rightWVB);
	glBindBuffer(GL_ARRAY_BUFFER, rightWVB);
	glBufferData(GL_ARRAY_BUFFER, rightWV.size() * sizeof(glm::vec3), &rightWV[0], GL_STATIC_DRAW);

	GLuint rightWCB;
	glGenBuffers(1, &rightWCB);
	glBindBuffer(GL_ARRAY_BUFFER, rightWCB);
	glBufferData(GL_ARRAY_BUFFER, rightWUV.size() * sizeof(glm::vec3), &rightWUV[0], GL_STATIC_DRAW);

	GLuint rightWNB;
	glGenBuffers(1, &rightWNB);
	glBindBuffer(GL_ARRAY_BUFFER, rightWNB);
	glBufferData(GL_ARRAY_BUFFER, rightWLN.size() * sizeof(glm::vec3), &rightWLN[0], GL_STATIC_DRAW);

	//movingObj
	GLuint  movingVB;
	glGenBuffers(1, &movingVB);
	glBindBuffer(GL_ARRAY_BUFFER, movingVB);
	glBufferData(GL_ARRAY_BUFFER, movingV.size() * sizeof(glm::vec3), &movingV[0], GL_STATIC_DRAW);

	GLuint movingCB;
	glGenBuffers(1, &movingCB);
	glBindBuffer(GL_ARRAY_BUFFER, movingCB);
	glBufferData(GL_ARRAY_BUFFER, movingUV.size() * sizeof(glm::vec3), &movingUV[0], GL_STATIC_DRAW);

	GLuint movingNB;
	glGenBuffers(1, &movingNB);
	glBindBuffer(GL_ARRAY_BUFFER, movingNB);
	glBufferData(GL_ARRAY_BUFFER, movingLN.size() * sizeof(glm::vec3), &movingLN[0], GL_STATIC_DRAW);

	//Barriers//

	//Barrier1
	GLuint barrier1VB;
	glGenBuffers(1, &barrier1VB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier1VB);
	glBufferData(GL_ARRAY_BUFFER, b1V.size() * sizeof(glm::vec3), &b1V[0], GL_STATIC_DRAW);

	GLuint barrier1CB;
	glGenBuffers(1, &barrier1CB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier1CB);
	glBufferData(GL_ARRAY_BUFFER, b1UV.size() * sizeof(glm::vec3), &b1UV[0], GL_STATIC_DRAW);

	GLuint barrier1NB;
	glGenBuffers(1, &barrier1NB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier1NB);
	glBufferData(GL_ARRAY_BUFFER, b1LN.size() * sizeof(glm::vec3), &b1LN[0], GL_STATIC_DRAW);

	//Barrier2
	GLuint barrier2VB;
	glGenBuffers(1, &barrier2VB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier2VB);
	glBufferData(GL_ARRAY_BUFFER, b2V.size() * sizeof(glm::vec3), &b2V[0], GL_STATIC_DRAW);

	GLuint barrier2CB;
	glGenBuffers(1, &barrier2CB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier2CB);
	glBufferData(GL_ARRAY_BUFFER, b2UV.size() * sizeof(glm::vec3), &b2UV[0], GL_STATIC_DRAW);

	GLuint barrier2NB;
	glGenBuffers(1, &barrier2NB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier2NB);
	glBufferData(GL_ARRAY_BUFFER, b2LN.size() * sizeof(glm::vec3), &b2LN[0], GL_STATIC_DRAW);

	//barrier3
	GLuint barrier3VB;
	glGenBuffers(1, &barrier3VB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier3VB);
	glBufferData(GL_ARRAY_BUFFER, b3V.size() * sizeof(glm::vec3), &b3V[0], GL_STATIC_DRAW);

	GLuint barrier3CB;
	glGenBuffers(1, &barrier3CB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier3CB);
	glBufferData(GL_ARRAY_BUFFER, b3UV.size() * sizeof(glm::vec3), &b3UV[0], GL_STATIC_DRAW);

	GLuint barrier3NB;
	glGenBuffers(1, &barrier3NB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier3NB);
	glBufferData(GL_ARRAY_BUFFER, b3LN.size() * sizeof(glm::vec3), &b3LN[0], GL_STATIC_DRAW);


	//barrier4
	GLuint barrier4VB;
	glGenBuffers(1, &barrier4VB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier4VB);
	glBufferData(GL_ARRAY_BUFFER, b4V.size() * sizeof(glm::vec3), &b4V[0], GL_STATIC_DRAW);

	GLuint barrier4CB;
	glGenBuffers(1, &barrier4CB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier4CB);
	glBufferData(GL_ARRAY_BUFFER, b4UV.size() * sizeof(glm::vec3), &b4UV[0], GL_STATIC_DRAW);

	GLuint barrier4NB;
	glGenBuffers(1, &barrier4NB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier4NB);
	glBufferData(GL_ARRAY_BUFFER, b4LN.size() * sizeof(glm::vec3), &b4LN[0], GL_STATIC_DRAW);

	//Barrier5
	GLuint barrier5VB;
	glGenBuffers(1, &barrier5VB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier5VB);
	glBufferData(GL_ARRAY_BUFFER, b5V.size() * sizeof(glm::vec3), &b5V[0], GL_STATIC_DRAW);

	GLuint barrier5CB;
	glGenBuffers(1, &barrier5CB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier5CB);
	glBufferData(GL_ARRAY_BUFFER, b5UV.size() * sizeof(glm::vec3), &b5UV[0], GL_STATIC_DRAW);

	GLuint barrier5NB;
	glGenBuffers(1, &barrier5NB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier5NB);
	glBufferData(GL_ARRAY_BUFFER, b5LN.size() * sizeof(glm::vec3), &b5LN[0], GL_STATIC_DRAW);

	//barrier6
	GLuint barrier6VB;
	glGenBuffers(1, &barrier6VB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier6VB);
	glBufferData(GL_ARRAY_BUFFER, b6V.size() * sizeof(glm::vec3), &b6V[0], GL_STATIC_DRAW);

	GLuint barrier6CB;
	glGenBuffers(1, &barrier6CB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier6CB);
	glBufferData(GL_ARRAY_BUFFER, b6UV.size() * sizeof(glm::vec3), &b6UV[0], GL_STATIC_DRAW);

	GLuint barrier6NB;
	glGenBuffers(1, &barrier6NB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier6NB);
	glBufferData(GL_ARRAY_BUFFER, b6LN.size() * sizeof(glm::vec3), &b6LN[0], GL_STATIC_DRAW);

	//barrier7
	GLuint barrier7VB;
	glGenBuffers(1, &barrier7VB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier7VB);
	glBufferData(GL_ARRAY_BUFFER, b7V.size() * sizeof(glm::vec3), &b7V[0], GL_STATIC_DRAW);

	GLuint barrier7CB;
	glGenBuffers(1, &barrier7CB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier7CB);
	glBufferData(GL_ARRAY_BUFFER, b7UV.size() * sizeof(glm::vec3), &b7UV[0], GL_STATIC_DRAW);

	GLuint barrier7NB;
	glGenBuffers(1, &barrier7NB);
	glBindBuffer(GL_ARRAY_BUFFER, barrier7NB);
	glBufferData(GL_ARRAY_BUFFER, b7LN.size() * sizeof(glm::vec3), &b7LN[0], GL_STATIC_DRAW);

	
	//Programs
	programID = LoadShaders("SimpleVertexShader.hlsl", "SimpleFragmentShader.hlsl");
	programID2 = LoadShaders("GreenVertexShader.hlsl", "GreenFragmentShader.hlsl");
	light = LoadShaders("LightingVertexShader.hlsl", "LightingFragmentShader.hlsl");

	do {
		//Enable depth test
		glEnable(GL_DEPTH_TEST);
		//Accept fragment if it is closer to the camera
		glDepthFunc(GL_LESS);

		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//view->draw(&vertexbuffer, vertices.size(), &colorbuffer, &normalbuffer, programID2, true, camera);
		//view->draw(&vertexbuffer2, vertices2.size(), &colorbuffer2, &normalbuffer2, light, true, camera);
		//view->draw(&LightingVB, LightingV.size(), &LightingCB, &LightingNB, light, true, camera);
		view->draw(&floorVB, floorV.size(), &floorCB, &floorNB, light, true, camera);
		view->draw(&leftWVB, leftWV.size(), &leftWCB, &leftWNB, light, true, camera);
		view->draw(&rightWVB, rightWV.size(), &rightWCB, &rightWNB, light, true, camera);
		view->draw(&movingVB, movingV.size(), &movingCB, &movingNB, light, true, camera);
		view->draw(&playerVB, playerV.size(), &playerCB, &playerNB, light, true, camera);

		//barriers
		view->draw(&barrier1VB, b1V.size(), &barrier1CB, &barrier1NB, light, true, camera);
		view->draw(&barrier2VB, b2V.size(), &barrier2CB, &barrier2NB, light, true, camera);
		view->draw(&barrier3VB, b3V.size(), &barrier3CB, &barrier3NB, light, true, camera);
		view->draw(&barrier4VB, b4V.size(), &barrier4CB, &barrier4NB, light, true, camera);
		view->draw(&barrier5VB, b5V.size(), &barrier5CB, &barrier5NB, light, true, camera);
		view->draw(&barrier6VB, b6V.size(), &barrier6CB, &barrier6NB, light, true, camera);
		view->draw(&barrier7VB, b7V.size(), &barrier7CB, &barrier7NB, light, true, camera);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();


	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	glDeleteProgram(programID);
	glDeleteProgram(light);
	glDeleteProgram(programID2);


	glDeleteBuffers(1, &floorVB);
	glDeleteBuffers(1, &leftWVB);
	glDeleteBuffers(1, &rightWVB);
	glDeleteBuffers(1, &movingVB);
	glDeleteBuffers(1, &playerVB);


	glDeleteBuffers(1, &barrier1VB);
	glDeleteBuffers(1, &barrier2VB);
	glDeleteBuffers(1, &barrier3VB);
	glDeleteBuffers(1, &barrier4VB);
	glDeleteBuffers(1, &barrier5VB);
	glDeleteBuffers(1, &barrier6VB);
	glDeleteBuffers(1, &barrier7VB);


	//glDeleteVertexArrays(1, &VertexArrayID);
}

GLFWwindow* Model::getGameWindow() {
	return window;
}

/*void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}*/