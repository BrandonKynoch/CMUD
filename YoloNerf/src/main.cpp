#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

#include "globals.h"

int main(int argc, const char** argv) {
	GLFWwindow* window;

	if (!glfwInit()) {
		printf("Failed to init GLFW");
		return EXIT_ERROR;
	}

	window = glfwCreateWindow(1024, 1024, "yolo-nerf", NULL, NULL);
	if (!window) {
		printf("Couldn't open GLFW window");
		return EXIT_ERROR;
	}

	unsigned char* pixels = new unsigned char[1024 * 1024 * 3];
	for (int x = 200; x < 500; ++x) {
		for (int y = 300; y < 1000; ++y) {
			pixels[(y * 1024 * 3) + x * 3    ] = 0xff;
			pixels[(y * 1024 * 3) + x * 3 + 1] = 0x00;
			pixels[(y * 1024 * 3) + x * 3 + 2] = 0x00;
		}
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawPixels(1024, 1024, GL_RGB, GL_UNSIGNED_BYTE, pixels);

		glfwSwapBuffers(window);

		glfwWaitEvents();
	}


	return 1;
}


//https://www.youtube.com/watch?v=HFyHIc89z1g