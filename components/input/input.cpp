#include "input.h"

bool Input::isKeyPressed[KEYBOARD_SIZE] = { false };

void Input::readInput(GLFWwindow* window) {
	//256 is not so random, it's 2^8 which is one byte
	for (int i = 0; i < KEYBOARD_SIZE; i++) {
		Input::isKeyPressed[i] = glfwGetKey(window, i) == GLFW_PRESS;
	}
}

bool Input::operator[](int i) {
	
	return Input::isKeyPressed[i];

}