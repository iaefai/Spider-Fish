
#include "Shader.h"

Shader::Shader() 
{
	shader = 0;
	source = NULL;
	
}

Shader::Shader(const std::string &file, GLenum shaderType) 
{
	shader = glCreateShader(shaderType);
	std::ifstream shaderFile;

	shaderFile.open(file.c_str(), std::ios::binary);
	struct stat st;
	stat(file.c_str(), &st);
	char *str = new char[static_cast<size_t>(st.st_size)+1];

//		source = new std::string(static_cast<size_t>(st.st_size), 0);
	shaderFile.read(str, static_cast<size_t>(st.st_size));
	source = new std::string(str);
	this->shaderType = shaderType;
}
	
bool Shader::compile()
{
	if (source) 
	{
		const char *str = source->c_str();
		shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &str, NULL);
		glCompileShader(shader);
		
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		
		if (status == GL_FALSE) 
		{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			
			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
			
			const char *strShaderType = NULL;
			switch(shaderType)
			{
				case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
				case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
				case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
			}
			
			std::cerr << "Compile failure in " << strShaderType << " shader: " << strInfoLog << std::endl;

			delete[] strInfoLog;

			return false;
		}
	}	
	return true;
}

bool Program::linkShaders(Shader *s, ...) 
{
	va_list ap;
	Shader *shader;
	
	GLuint program = glCreateProgram();
	
	va_start(ap, s);
	
	for (shader = va_arg(ap, Shader*); 
		 shader != NULL; 
		 shader = va_arg(ap, Shader*))
	{
		glAttachShader(program, shader->shader);
	}
	
	glLinkProgram(program);
	
	GLint status;
	
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		
		std::cerr << "Linker failure: " << strInfoLog << std::endl;
		
		delete[] strInfoLog;
		
		return false;
	}
	return true;
}
