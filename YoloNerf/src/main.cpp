#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <GLFW/glfw3.h>

#include "globals.h"
#include "networking.h"

using namespace YoloNerf;

int main(int argc, const char** argv) {
	NetworkHandler* networkHandler = new NetworkHandler();


	//     GLFW      ///////////////////////////////////////////////////////////////////////
	GLFWwindow* window;

	if (!glfwInit()) {
		printf("Failed to init GLFW");
		return EXIT_ERROR;
	}

	window = glfwCreateWindow(FRAME_WIDTH, FRAME_HEIGHT, "yolo-nerf", NULL, NULL);
	if (!window) {
		printf("Couldn't open GLFW window");
		return EXIT_ERROR;
	}

	GLubyte* pixels = new GLubyte[FRAME_WIDTH * FRAME_HEIGHT * 3];

	int cx = 0;
	int cy = 0;
	int ax, ay;

	//GLubyte* pixels_out = new GLubyte[FRAME_WIDTH * FRAME_HEIGHT * 3];

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	int i = 0;
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




		cx++;
		cy+= 2;
		if (cx + 20 >= FRAME_WIDTH) {
			cx = 0;
		}
		if (cy + 10 >= FRAME_HEIGHT) {
			cy = 0;
		}

		for (int x = 0; x < 20; ++x) {
			for (int y = 0; y < 10; ++y) {
				ax = cx + x;
				ay = cy + y;

				pixels[(ay * FRAME_WIDTH * 3) + ax * 3    ] = 0xff;
				pixels[(ay * FRAME_WIDTH * 3) + ax * 3 + 1] = 0x00;
				pixels[(ay * FRAME_WIDTH * 3) + ax * 3 + 2] = 0x00;
			}
		}




		glDrawPixels(FRAME_WIDTH, FRAME_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels);

		glfwSwapBuffers(window);

		glfwWaitEvents();

		networkHandler->SendFrame();

		/*
		if (i >= 10) {
			glReadPixels(0, 0, FRAME_WIDTH, FRAME_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels_out);

			//std::ofstream::write ("c:\\demos\\CPlusPlusSampleFile.txt", std::ofstream::out);
			std::ofstream fw("C:\\Brandon\\CurrentProjects\\CMUD\\YoloNerf\\output\\framedump.txt", std::ofstream::out);
			if (fw.is_open()) {
				for (int x = 0; x < FRAME_WIDTH; ++x) {
					for (int y = 0; y < FRAME_HEIGHT; ++y) {
						fw << pixels_out[(y * FRAME_WIDTH * 3) + x * 3];
						fw << pixels_out[(y * FRAME_WIDTH * 3) + x * 3 + 1];
						fw << pixels_out[(y * FRAME_WIDTH * 3) + x * 3 + 2];
					}
				}

				fw.close();
			}
			else {
				printf("Failed to open file for writing");
			}

			break;
		}
		i++;
		*/
	}


	return 1;
}


//https://www.youtube.com/watch?v=HFyHIc89z1g