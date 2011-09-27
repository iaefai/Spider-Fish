#ifndef Shader_H
#define Shader_H

#include <iostream>
#include <fstream>
#include <iterator>
#include <sys/stat.h>
#include <stdarg.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>

class Program;

class Shader {

private:
	GLuint shader;
	std::string *source;	
	GLenum shaderType;

public:
	Shader();
	~Shader() {
		delete source;
		glDeleteShader(shader);
	}
	
	Shader(const std::string &file, GLenum shaderType);
	bool compile();
	
	friend class Program;
};

class Program {
private:
	GLuint program;
	
public:
	Program() : program(0) {};
	~Program() {
		if (program != 0)
		{
			glDeleteProgram(program);
		}
	}
	
	bool linkShaders(Shader *s, ...);
	void bind() { glUseProgram(program); }
	void unbind() { glUseProgram(0); }
};

#endif