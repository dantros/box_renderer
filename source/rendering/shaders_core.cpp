
#include "shaders_core.h"
#include <glad/glad.h>

namespace BoxRenderer{

namespace
{
GLuint compileShader(GLenum type, std::string const& sourceCode)
{
	auto shaderCodeChars = sourceCode.c_str();

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderCodeChars, NULL);
	glCompileShader(shader);

	// check for shader compile errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::SHADER_SOURCE_CODE: " << std::endl;
        std::cout << sourceCode << std::endl;
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;

		throw;
	}

	return shader;
}

GPUID createShaderProgramCore(std::vector<ShaderCode> const& shaderCodes)
{
	GPUID shaderProgram = glCreateProgram();

	std::vector<GPUID> shaders;

	for (auto shaderCode : shaderCodes)
	{
		GPUID shader = compileShader(static_cast<GLenum>(shaderCode.type), shaderCode.sourceCode);
		glAttachShader(shaderProgram, shader);
		shaders.push_back(shader);
	}

	glLinkProgram(shaderProgram);

	GLint success;
	GLchar infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		throw;
	}

	for (auto shader : shaders)
	{
		glDeleteShader(shader);
	}

    return shaderProgram;
}
} // namespace

GPUID createShaderProgramFromCode(std::initializer_list<ShaderCode> shaderCodes)
{
    std::vector<ShaderCode> shaderCodesVec;

    for (auto const shaderCode : shaderCodes)
	{
        shaderCodesVec.push_back(shaderCode);
	}

	return createShaderProgramCore(shaderCodesVec);
}

} // namespace BoxRenderer