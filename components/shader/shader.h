#pragma once
#ifndef __SHADER
#define __SHADER
#include "../context/context.h"
#include "../../libraries/glm/glm.hpp"
#include "../../libraries/glm/gtc/type_ptr.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>

#define MAX_LOG_SHADER_SIZE 2048
//https://github.com/fendevel/Guide-to-Modern-OpenGL-Functions thanks for the inspiration
typedef struct _uniform_info {
	
	GLint location;
	GLsizei count;
	GLenum type;
	GLenum shaderType;

}UniformInfo;

std::unordered_map<std::string, UniformInfo> retriveUniforms(GLint programID);

class Shader {
public:
	//
	GLuint ID;
	std::unordered_map<std::string, UniformInfo> uniforms;


	// returns the ID of the shader
	static GLuint compile(const char *shaderPath,GLenum shaderType);
	Shader(const char * vertexShaderPath,const char * fragmentShaderPath,const char * geometryShaderPath = nullptr);
	
	//Needed because of try-catch in main
	Shader();

	void u_mat4(glm::mat4& matrix, std::string uniformName, bool transpose);
	void u_int(int value, std::string uniformName);
	void u_vec3(glm::vec3&, std::string uniformName);
	void use();
	static void printLog(std::vector<GLchar> log,GLenum type);
};

std::string readFromFile(const char* path);


#endif 