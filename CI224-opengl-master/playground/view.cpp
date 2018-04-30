#include "view.hpp"

View::View(int widtht, int heightt, Model* modelt) {
	width = widtht;
	height = heightt;
}

View::~View() {

}

initialise() {
	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, "Froggur", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	return 0;
}

getWidth() {
	return width;
}

getHeight() {
	return height;
}