#pragma once
#ifndef __STRUCTURES
#define __STRUCTURES
	
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

#define WIN_HEIGHT 800
#define WIN_WIDTH 800

//Quando saro' al fisso e avro' bisogno di 4, impostarlo da qui sara' piu' semplice
#define OPENGL_VERSION_HINT 4.6

GLFWwindow * createWindow(const char *window_name, int height = WIN_HEIGHT, int width = WIN_WIDTH);


//error checking returns 0 if everything is fine
int checkErrors();

#endif 
