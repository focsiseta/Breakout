#pragma once
#ifndef __INPUT
#define __INPUT

#include <glfw/glfw3.h>

#define KEYBOARD_SIZE 256

//It will have mouse support one day

class Input {
private:
	static bool isKeyPressed[KEYBOARD_SIZE];
public:
	bool operator[](int i);
	static void readInput(GLFWwindow*);



};



#endif