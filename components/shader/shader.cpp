#include "shader.h"
std::string readFromFile(const char* path) {
	std::string code;
	std::ifstream shader;
	shader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::stringstream sStream;
	try {
		shader.open(path);
		sStream << shader.rdbuf();
		code = sStream.str();
		//shader.close();
		//std::stringstream().swap(sStream);
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
	}
	shader.close();
	sStream.clear();

	//std::cout << code;
	return code;

}
GLuint Shader::compile(const char* shaderPath, GLenum shaderType) {
	if (shaderPath == nullptr) return 0;
	GLuint toReturn = glCreateShader(shaderType);
	int err = checkErrors();
	if (err < 0) {
		std::cout << "Shader type not reconized" << std::endl;
		return 0;
	}
	std::string source = readFromFile(shaderPath);
	const char* cSource = source.c_str();
	glShaderSource(toReturn,1,&cSource,NULL);
	glCompileShader(toReturn);

	//Directly from doc
	GLint success = 0;
	glGetShaderiv(toReturn, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint logSize = 0;
		glGetShaderiv(toReturn, GL_INFO_LOG_LENGTH, &logSize);
		std::vector<GLchar> errorlog( logSize );
		glGetShaderInfoLog(toReturn, logSize, &logSize, &errorlog[0]);
		printLog(errorlog,shaderType);
		glDeleteShader(toReturn);
		return 0;
	}
	return toReturn;


}

void Shader::printLog(std::vector<GLchar> log,GLenum type) {
	std::string shader;
	shader = type == GL_VERTEX_SHADER ? "VERTEX SHADER" : "FRAGMENT SHADER";
	std::cout << "SHADER COMPILATION ERROR:  " << shader << std::endl;
	for (GLchar c : log)
	{
		std::cout << c;
	}
	std::cout << std::endl;

}
//There is no support for geometry shaders (For now)
Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath) {
	GLuint vertex, fragment, geometry;
	vertex = compile(vertexShaderPath, GL_VERTEX_SHADER);
	fragment = compile(fragmentShaderPath, GL_FRAGMENT_SHADER);
	this->ID = glCreateProgram();
	glAttachShader(this->ID,vertex);
	glAttachShader(this->ID, fragment);
	glLinkProgram(this->ID);
	GLint success = 0;
	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		int loglen = 0;
		glGetProgramiv(this->ID, GL_INFO_LOG_LENGTH, &loglen);
		std::vector<GLchar> errlog(loglen);
		glGetProgramInfoLog(this->ID, loglen, &loglen, &errlog[0]);
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		glDeleteProgram(this->ID);
		throw std::string("Unable to create shader program");
		return;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	this->uniforms = retriveUniforms(this->ID);
}

Shader::Shader() {};

std::unordered_map<std::string, UniformInfo> retriveUniforms(GLint programID) {

	GLint uniformCount = 0;
	std::unordered_map<std::string, UniformInfo> retrived{};
	glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &uniformCount);

	if (uniformCount != 0) {
		
		GLint maxNameLen = 0;
		GLsizei length = 0;
		GLsizei count = 0;
		GLenum type = GL_NONE;
		glGetProgramiv(programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLen);
		auto uniformName = std::make_unique<char[]>(maxNameLen);
		for (GLint i = 0; i < uniformCount; i++) {
		
			glGetActiveUniform(programID, i, maxNameLen, &length, &count, &type, uniformName.get());
			UniformInfo uInfo = {};
			uInfo.location = glGetUniformLocation(programID, uniformName.get());
			uInfo.count = count;
			uInfo.type = type;
			retrived.emplace(std::make_pair(std::string(uniformName.get()), uInfo));
		}

		return retrived;


	
	}
	return retrived;



}

void Shader::u_mat4(glm::mat4& matrix,std::string uniformName,bool transpose) {

	glUniformMatrix4fv(this->uniforms[uniformName].location,1,transpose ? GL_TRUE : GL_FALSE,glm::value_ptr(matrix));

}
void Shader::u_int(int value, std::string uniformName) {
	
	glUniform1i(this->uniforms[uniformName].location, value);

}

void Shader::u_vec3(glm::vec3& value, std::string uniformName) {

	glUniform3fv(this->uniforms[uniformName].location,1,glm::value_ptr(value));
}

void Shader::u_float(float value, std::string uniformName) {

	glUniform1fv(this->uniforms[uniformName].location, 1, &value);
}

void Shader::u_vec4(glm::vec4& value, std::string uniformName) {

	glUniform4fv(this->uniforms[uniformName].location, 1, glm::value_ptr(value));
}

void Shader::u_vec2(glm::vec2& value, std::string uniformName) {

	glUniform2fv(this->uniforms[uniformName].location, 1, glm::value_ptr(value));
}

void Shader::use() {
	
	glUseProgram(this->ID);

}


