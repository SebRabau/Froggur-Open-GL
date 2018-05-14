#include "model.hpp"

int heightM;
int widthM;
View* view;
GLFWwindow* window;
GLuint vertexbuffer;
GLuint playerShader;
GLuint greenShader;
GLuint wallShader;
GLuint floorShader;
vec3 playerTrans;

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// camera
Camera camera(vec3(-0.1f, -0.2f, 5.0f));
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

	//MovingObject1
	std::vector<glm::vec3> moving1V;
	std::vector<glm::vec2> moving1UV;
	std::vector<glm::vec3> moving1LN;

	//MovingObjectR
	std::vector<glm::vec3> movingRV;
	std::vector<glm::vec2> movingRUV;
	std::vector<glm::vec3> movingRLN;

	//MovingObjectR1
	std::vector<glm::vec3> moving1RV;
	std::vector<glm::vec2> moving1RUV;
	std::vector<glm::vec3> moving1RLN;

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
	bool movingObjR = loadOBJ("movingObjectR.obj", movingRV, movingRUV, movingRLN);
	bool movingObj1 = loadOBJ("movingObject1.obj", moving1V, moving1UV, moving1LN);
	bool movingObj1R = loadOBJ("movingObject1R.obj", moving1RV, moving1RUV, moving1RLN);

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

	//movingObj1
	GLuint  moving1VB;
	glGenBuffers(1, &moving1VB);
	glBindBuffer(GL_ARRAY_BUFFER, moving1VB);
	glBufferData(GL_ARRAY_BUFFER, moving1V.size() * sizeof(glm::vec3), &moving1V[0], GL_STATIC_DRAW);

	GLuint moving1CB;
	glGenBuffers(1, &moving1CB);
	glBindBuffer(GL_ARRAY_BUFFER, moving1CB);
	glBufferData(GL_ARRAY_BUFFER, moving1UV.size() * sizeof(glm::vec3), &moving1UV[0], GL_STATIC_DRAW);

	GLuint moving1NB;
	glGenBuffers(1, &moving1NB);
	glBindBuffer(GL_ARRAY_BUFFER, moving1NB);
	glBufferData(GL_ARRAY_BUFFER, moving1LN.size() * sizeof(glm::vec3), &moving1LN[0], GL_STATIC_DRAW);

	//movingObj
	GLuint  movingRVB;
	glGenBuffers(1, &movingRVB);
	glBindBuffer(GL_ARRAY_BUFFER, movingRVB);
	glBufferData(GL_ARRAY_BUFFER, movingRV.size() * sizeof(glm::vec3), &movingRV[0], GL_STATIC_DRAW);

	GLuint movingRCB;
	glGenBuffers(1, &movingRCB);
	glBindBuffer(GL_ARRAY_BUFFER, movingRCB);
	glBufferData(GL_ARRAY_BUFFER, movingRUV.size() * sizeof(glm::vec3), &movingRUV[0], GL_STATIC_DRAW);

	GLuint movingRNB;
	glGenBuffers(1, &movingRNB);
	glBindBuffer(GL_ARRAY_BUFFER, movingRNB);
	glBufferData(GL_ARRAY_BUFFER, movingRLN.size() * sizeof(glm::vec3), &movingRLN[0], GL_STATIC_DRAW);

	//movingObj1R
	GLuint  moving1RVB;
	glGenBuffers(1, &moving1RVB);
	glBindBuffer(GL_ARRAY_BUFFER, moving1RVB);
	glBufferData(GL_ARRAY_BUFFER, moving1RV.size() * sizeof(glm::vec3), &moving1RV[0], GL_STATIC_DRAW);

	GLuint moving1RCB;
	glGenBuffers(1, &moving1RCB);
	glBindBuffer(GL_ARRAY_BUFFER, moving1RCB);
	glBufferData(GL_ARRAY_BUFFER, moving1RUV.size() * sizeof(glm::vec3), &moving1RUV[0], GL_STATIC_DRAW);

	GLuint moving1RNB;
	glGenBuffers(1, &moving1RNB);
	glBindBuffer(GL_ARRAY_BUFFER, moving1RNB);
	glBufferData(GL_ARRAY_BUFFER, moving1RLN.size() * sizeof(glm::vec3), &moving1RLN[0], GL_STATIC_DRAW);

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
	
	//bounding boxes
	BoundingBox* playerBB = new BoundingBox(playerV);

	BoundingBox* leftWBB = new BoundingBox(leftWV);
	leftWBB->initialise();

	BoundingBox* rightWBB = new BoundingBox(rightWV);
	rightWBB->initialise();

	BoundingBox* b1BB = new BoundingBox(b1V);
	b1BB->initialise();

	BoundingBox* b2BB = new BoundingBox(b2V);
	b2BB->initialise();

	BoundingBox* b3BB = new BoundingBox(b3V);
	b3BB->initialise();

	BoundingBox* b4BB = new BoundingBox(b4V);
	b4BB->initialise();

	BoundingBox* b5BB = new BoundingBox(b5V);
	b5BB->initialise();

	BoundingBox* b6BB = new BoundingBox(b6V);
	b6BB->initialise();

	BoundingBox* b7BB = new BoundingBox(b7V);
	b7BB->initialise();

	BoundingBox* c1BB = new BoundingBox(movingV);
	c1BB->initialise();

	BoundingBox* c2BB = new BoundingBox(moving1V);
	c2BB->initialise();
	
	//Programs
	playerShader = LoadShaders("Shaders/PlayerVertexShader.hlsl", "Shaders/PlayerFragmentShader.hlsl");
	greenShader = LoadShaders("Shaders/GreenVertexShader.hlsl", "Shaders/GreenFragmentShader.hlsl");
	wallShader = LoadShaders("Shaders/WallVertexShader.hlsl", "Shaders/WallFragmentShader.hlsl");
	floorShader = LoadShaders("Shaders/FloorVertexShader.hlsl", "Shaders/FloorFragmentShader.hlsl");	

	//Left vector Movement
	vec3 movingObjsL1;
	vec3 movingObjsL2;
	vec3 movingObjsL3;
	vec3 movingObjsL4;
	vec3 movingObjsL5;
	vec3 movingObjsL6;
	vec3 movingObjsL7;
	vec3 movingObjsL8;
	vec3 movingObjsL9;
	
	vec3 movingObjsLF1;
	vec3 movingObjsLF2;
	vec3 movingObjsLF3;
	vec3 movingObjsLF4;
	vec3 movingObjsLF5;
	vec3 movingObjsLF6;


	//Right Vector Movement
	vec3 movingObjsR1;
	vec3 movingObjsR2;
	vec3 movingObjsR3;
	vec3 movingObjsR4;
	vec3 movingObjsR5;
	vec3 movingObjsR6;
	vec3 movingObjsR7;
	vec3 movingObjsR8;
	vec3 movingObjsR9;

	vec3 movingObjsRF1;
	vec3 movingObjsRF2;
	vec3 movingObjsRF3;



	do {
		playerBB->initialise();
		//Enable depth test
		glEnable(GL_DEPTH_TEST);
		//Accept fragment if it is closer to the camera
		glDepthFunc(GL_LESS);

		playerTrans = playerInput(playerTrans, playerBB);

		c1BB->update(movingObjsL1);
		c1BB->update(movingObjsL2);
		c1BB->update(movingObjsL3);
		c1BB->update(movingObjsL4);
		c1BB->update(movingObjsL5);
		c1BB->update(movingObjsL6);
		c1BB->update(movingObjsL7);
		c1BB->update(movingObjsL8);
		c1BB->update(movingObjsL9);
		c1BB->update(movingObjsLF1);
		c1BB->update(movingObjsLF2);
		c1BB->update(movingObjsLF3);
		c1BB->update(movingObjsLF4);
		c1BB->update(movingObjsLF5);
		c1BB->update(movingObjsLF6);

		c2BB->update(movingObjsR1);
		c2BB->update(movingObjsR2);
		c2BB->update(movingObjsR3);
		c2BB->update(movingObjsR4);
		c2BB->update(movingObjsR5);
		c2BB->update(movingObjsR6);
		c2BB->update(movingObjsR7);
		c2BB->update(movingObjsR8);
		c2BB->update(movingObjsR9);
		c2BB->update(movingObjsRF1);
		c2BB->update(movingObjsRF2);
		c2BB->update(movingObjsRF3);

		handleCollision(playerBB, leftWBB);
		handleCollision(playerBB, rightWBB);
		handleCollision(playerBB, b1BB);
		handleCollision(playerBB, b2BB);
		handleCollision(playerBB, b3BB);
		handleCollision(playerBB, b4BB);
		handleCollision(playerBB, b5BB);
		handleCollision(playerBB, b6BB);
		handleCollision(playerBB, b7BB);
		handleCollision(playerBB, c1BB);
		handleCollision(playerBB, c2BB);

		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		view->draw(&floorVB, floorV.size(), &floorCB, &floorNB, floorShader, false, false, camera, vec3(0.0, 0.0, 0.0));
		view->draw(&leftWVB, leftWV.size(), &leftWCB, &leftWNB, wallShader, false, false, camera, vec3(0.0, 0.0, 0.0));
		view->draw(&rightWVB, rightWV.size(), &rightWCB, &rightWNB, wallShader, false, false, camera, vec3(0.0, 0.0, 0.0));

		///moving objs speed
		movingObjsL1 = movingObjsL1 + vec3(-0.002, 0.0, 0.0);
		movingObjsL2 = movingObjsL2 + vec3(-0.002, 0.0, 0.0);

		movingObjsL4 = movingObjsL4 + vec3(-0.002, 0.0, 0.0);
		movingObjsL5 = movingObjsL5 + vec3(-0.002, 0.0, 0.0);

		movingObjsL7 = movingObjsL7 + vec3(-0.002, 0.0, 0.0);
		movingObjsL8 = movingObjsL8 + vec3(-0.002, 0.0, 0.0);


		movingObjsLF1 = movingObjsLF1 + vec3(-0.004, 0.0, 0.0);
		movingObjsLF2 = movingObjsLF2 + vec3(-0.004, 0.0, 0.0);
		movingObjsLF4 = movingObjsLF4 + vec3(-0.004, 0.0, 0.0);
		movingObjsLF5 = movingObjsLF5 + vec3(-0.004, 0.0, 0.0);
				
		movingObjsR1 = movingObjsR1 + vec3(0.002, 0.0, 0.0);
		movingObjsR2 = movingObjsR2 + vec3(0.002, 0.0, 0.0);
		movingObjsR4 = movingObjsR4 + vec3(0.002, 0.0, 0.0);
		movingObjsR5 = movingObjsR5 + vec3(0.002, 0.0, 0.0);
		movingObjsR7 = movingObjsR7 + vec3(0.002, 0.0, 0.0);
		movingObjsR8 = movingObjsR8 + vec3(0.002, 0.0, 0.0);

		movingObjsRF1 = movingObjsRF1 + vec3(0.004, 0.0, 0.0);
		movingObjsRF2 = movingObjsRF2 + vec3(0.004, 0.0, 0.0);


		
		//Row 1 Right To left - Car 1
	      view->draw(&movingVB, movingV.size(), &movingCB, &movingNB, playerShader, false, true, camera, movingObjsL1 + vec3(3.0, -8.3, 0.3));
			  	  if (movingObjsL1[0] < -10) {
				  movingObjsL1[0] = 4.0f;
			  }
		//Car2
   		  view->draw(&moving1VB, moving1V.size(), &moving1CB, &moving1NB, playerShader, false, true, camera, movingObjsL2 + vec3(6.0, -8.3, 0.3));
		  		  if (movingObjsL2[0] < -13) {
				 movingObjsL2[0] = 4.0f;
		  }


		//Row 2 - left to right - Car 1
		view->draw(&moving1RVB, moving1RV.size(), &moving1RCB, &moving1RNB, wallShader, false, true, camera, movingObjsR1 + vec3(-12.0, -6.8, 0.3));
		if (movingObjsR1[0] > 17.5) {
			movingObjsR1[0] = -5;
		}
		    view->draw(&movingRVB, movingRV.size(), &movingRCB, &movingRNB, wallShader, false, true, camera, movingObjsR2 + vec3(-9.0, -6.8, 0.3));
			if (movingObjsR2[0] > 15.5 ) {			
				movingObjsR2[0] = -5;
			}


		//Row 3 - Right to Left - Car 1
		    view->draw(&movingVB, movingV.size(), &movingCB, &movingNB, wallShader, false, true, camera, movingObjsL4 + vec3(6.0, -5.3, 0.3));
			if (movingObjsL4[0] < -13) {
				movingObjsL4[0] = 4.0;
			}
		view->draw(&moving1VB, moving1V.size(), &moving1CB, &moving1NB, wallShader, false, true, camera, movingObjsL5 + vec3(9.0, -5.3, 0.3));
		if (movingObjsL5[0] < -16) {
			movingObjsL5[0] = 4.0;
		}

		//Row 4 - L to R -Car 1
		    view->draw(&movingRVB, movingRV.size(), &movingRCB, &movingRNB, playerShader, false, true, camera, movingObjsR4 + vec3(-15.0, -3.8, 0.3));
			if (movingObjsR4[0] > 20) {
				movingObjsR4[0] = -5;
			}
		view->draw(&moving1RVB, moving1RV.size(), &moving1RCB, &moving1RNB, playerShader, false, true, camera, movingObjsR5 + vec3(-12.0, -3.8, 0.3));
		if (movingObjsR5[0] > 18.5) {
			movingObjsR5[0] = -2;
		}

		//Row 5 R to L - Car 1
			  view->draw(&movingVB, movingV.size(), &movingCB, &movingNB, playerShader, false, true, camera, movingObjsL7 + vec3(3.0, -1.3, 0.3));
			  if (movingObjsL7[0] < -10) {
				  movingObjsL7[0] = 4.0f;
			  }
			  //Car 2
			  view->draw(&moving1VB, moving1V.size(), &moving1CB, &moving1NB, playerShader, false, true, camera, movingObjsL8 + vec3(6.0, -1.3, 0.3));
			  if (movingObjsL8[0] < -13) {
				  movingObjsL8[0] = 4.0f;
			  }


		//row6
		view->draw(&moving1RVB, moving1RV.size(), &moving1RCB, &moving1RNB, wallShader, false, true, camera, movingObjsR7 + vec3(-9.0, 0.2, 0.3));
		if (movingObjsR2[0] > 15.5) {
			movingObjsR2[0] = -5;
		}
		    view->draw(&movingRVB, movingRV.size(), &movingRCB, &movingRNB, wallShader, false, true, camera, movingObjsR8 + vec3(-6.0, 0.2, 0.3));
			if (movingObjsR2[0] > 12.5) {
				movingObjsR2[0] = -5;
			}

		//Row 7 Right to left Fast
		    view->draw(&movingVB, movingV.size(), &movingCB, &movingNB, wallShader, false, true, camera, movingObjsLF1 + vec3(4.0, 3.0, 0.3));
			if (movingObjsLF1[0] < -9) {
				movingObjsLF1[0] = 4.0f;
			}
		view->draw(&moving1VB, moving1V.size(), &moving1CB, &moving1NB, wallShader, false, true, camera, movingObjsLF2 + vec3(7.0, 3.0, 0.3));
		if (movingObjsLF2[0] < -12) {
			movingObjsLF2[0] = 4.0f;
		}

		//row8
		view->draw(&moving1RVB, moving1RV.size(), &moving1RCB, &moving1RNB, wallShader, false, true, camera, movingObjsRF1 + vec3(-15.0, 5.0, 0.3));
		if (movingObjsRF1[0] > 20) {
			movingObjsRF1[0] = -5;
		}
			view->draw(&movingRVB, movingRV.size(), &movingRCB, &movingRNB, wallShader, false, true, camera, movingObjsRF2 + vec3(-12.0, 5.0, 0.3));
			if (movingObjsRF2[0] > 18.5) {
				movingObjsRF2[0] = -5;
			}


		//row9 right to left fast
		     view->draw(&movingVB, movingV.size(), &movingCB, &movingNB, wallShader, false, true, camera, movingObjsLF4 + vec3(4.0, 7.0, 0.3));
			 if (movingObjsLF4[0] < -10) {
				 movingObjsLF4[0] = 4.0f;
			 }
		view->draw(&moving1VB, moving1V.size(), &moving1CB, &moving1NB, wallShader, false, true, camera, movingObjsLF5 + vec3(7.0, 7.0, 0.3));
		if (movingObjsLF5[0] < -13) {
			movingObjsLF5[0] = 4.0f;
		}



		//player movement
		view->draw(&playerVB, playerV.size(), &playerCB, &playerNB, playerShader, true, false, camera, playerTrans);

		//barriers
		view->draw(&barrier1VB, b1V.size(), &barrier1CB, &barrier1NB, floorShader, false, false, camera, vec3(0.0, 0.0, 0.0));
		view->draw(&barrier2VB, b2V.size(), &barrier2CB, &barrier2NB, floorShader, false, false, camera, vec3(0.0, 0.0, 0.0));
		view->draw(&barrier3VB, b3V.size(), &barrier3CB, &barrier3NB, floorShader, false, false, camera, vec3(0.0, 0.0, 0.0));
		view->draw(&barrier4VB, b4V.size(), &barrier4CB, &barrier4NB, floorShader, false, false, camera, vec3(0.0, 0.0, 0.0));
		view->draw(&barrier5VB, b5V.size(), &barrier5CB, &barrier5NB, floorShader, false, false, camera, vec3(0.0, 0.0, 0.0));
		view->draw(&barrier6VB, b6V.size(), &barrier6CB, &barrier6NB, floorShader, false, false, camera, vec3(0.0, 0.0, 0.0));
		view->draw(&barrier7VB, b7V.size(), &barrier7CB, &barrier7NB, floorShader, false, false, camera, vec3(0.0, 0.0, 0.0));

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();


	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	glDeleteProgram(playerShader);
	glDeleteProgram(greenShader);
	glDeleteProgram(wallShader);
	glDeleteProgram(floorShader);


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


vec3 Model::playerInput(vec3 playerTrans, BoundingBox* _playerBB) {
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		//std::cout << "Up Pressed" << std::endl;
		//std::cout << playerTrans.y << std::endl;
		playerTrans = playerTrans + vec3(0.0f, 0.01f, 0.0f);
		_playerBB->update(playerTrans);
		glfwGetKey(window, GLFW_KEY_UP);

	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		//std::cout << "Down Pressed" << std::endl;
		//std::cout << playerTrans.y << std::endl;
		playerTrans = playerTrans + vec3(0.0f, -0.01f, 0.0f);
		_playerBB->update(playerTrans);
		glfwGetKey(window, GLFW_KEY_DOWN);

	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		//std::cout << "Left Pressed" << std::endl;
		//std::cout << playerTrans.x << std::endl;
		playerTrans = playerTrans + vec3(-0.01f, 0.0f, 0.0f);
		_playerBB->update(playerTrans);
		glfwGetKey(window, GLFW_KEY_LEFT);

	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		//std::cout << "Right Pressed" << std::endl;
		//std::cout << playerTrans.x << std::endl;
		playerTrans = playerTrans + vec3(0.01f, 0.0f, 0.0f);
		_playerBB->update(playerTrans);
		glfwGetKey(window, GLFW_KEY_RIGHT);

	}
	return playerTrans;
}

void Model::handleCollision(BoundingBox* player, BoundingBox* object) {
	if (player->btl.x <= object->getMax().x && player->btr.x >= object->getMax().x && player->btr.y <= object->getMax().y && player->btr.y >= object->getMin().y) { //hit left
		playerTrans += vec3(0.5, 0.0, 0.0);
	} else if (player->btr.x >= object->getMin().x && player->btl.x <= object->getMin().x && player->btr.y <= object->getMax().y && player->btr.y >= object->getMin().y) { //hit right
		playerTrans += vec3(-0.5, 0.0, 0.0);
	} else if (player->btl.y >= object->getMin().y && player->bbl.y <= object->getMin().y && player->btl.x > object->getMin().x - 0.6 && player->btr.x < object->getMax().x + 0.6) { //hit top
		playerTrans += vec3(0.0, -0.5, 0.0);
	} else if (player->bbl.y <= object->getMax().y && player->btl.y >= object->getMax().y && player->bbl.x > object->getMin().x - 0.6 && player->btr.x < object->getMax().x + 0.6) { //hit bottom
		playerTrans += vec3(0.0, 0.5, 0.0);
	}
}
