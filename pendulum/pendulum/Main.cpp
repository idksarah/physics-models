#include <iostream>
//#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <Gl/gl.h>
#include <math.h>
#include <windows.h>
#include <vector>


void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
	double SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
	// initialize glfw
	glfwInit();

	// set glfw major minor versions
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	// create window
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pendulum Simulation", NULL, NULL);

	glfwMakeContextCurrent(window);

	//gladLoadGL();

	// set screen size
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(.2f, .3f, .3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		drawCircle(0, 0, 0, .5, 36);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// quit
	glfwTerminate();
	return 0;
}

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides) {
	GLint numberOfVertices = numberOfSides + 2;
	GLfloat doublePi = 2.0f * M_PI;

	std::vector<GLfloat> circleVerticesX(numberOfVertices);
	std::vector<GLfloat> circleVerticesY(numberOfVertices);
	std::vector<GLfloat> circleVerticesZ(numberOfVertices);

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for (int i = 1; i < numberOfVertices; i++) {
		circleVerticesX[i] = x + cos(i * doublePi / numberOfSides);
		circleVerticesY[i] = y + sin(i * doublePi / numberOfSides);
		circleVerticesZ[i] = z;
	}

	std::vector<GLfloat> allCircleVertices(numberOfVertices * 3);

	for (int i = 0; i < numberOfVertices; i++) {
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[i * 3 + 1] = circleVerticesY[i];
		allCircleVertices[i * 3 + 2] = circleVerticesZ[i];
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices.data()); 
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
	glDisableClientState(GL_VERTEX_ARRAY);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}