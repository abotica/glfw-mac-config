#include "../../include/glad/glad.h"

#include "Shader.h"

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader) 
{
	LoadShaders(vertexShader, fragmentShader);
	CreateShaders();
}

Shader::~Shader()
{
	glDeleteProgram(m_RenderID);
}

void Shader::Bind() const
{
	glUseProgram(m_RenderID);
}

void Shader::UnBind() const
{
	glUseProgram(0);
}

void Shader::SetUniform4x4(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_RenderID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetUniformVec3(const std::string& name, const float& x, const float& y, const float& z) const
{
	glUniform3f(glGetUniformLocation(m_RenderID, name.c_str()), x, y, z);
}

void Shader::SetUniformVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(m_RenderID, name.c_str()), 1, &value[0]);
}

void Shader::SetUniformFloat(const std::string& name, const float& value) const
{
	glUniform1f(glGetUniformLocation(m_RenderID, name.c_str()), value);
}

void Shader::SetUniformInt(const std::string& name, const int& value) const
{
	glUniform1i(glGetUniformLocation(m_RenderID, name.c_str()), value);
}

void Shader::LoadShaders(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::ifstream vertexShaderFile(vertexPath);
	assert(vertexShaderFile);
	std::ifstream fragmentShaderFile(fragmentPath);
	assert(fragmentShaderFile);
	
	std::stringstream vertexStream;
	std::stringstream fragmentStream;

	std::string readVertex;
	std::string readFragment;

	while (std::getline(vertexShaderFile, readVertex))
	{
		vertexStream << readVertex << "\n";
	}

	while (std::getline(fragmentShaderFile, readFragment))
	{
		fragmentStream << readFragment << "\n";
	}

	vertexShaderFile.close();
	fragmentShaderFile.close();

	m_VertexSource = vertexStream.str();
	m_FragmentSource = fragmentStream.str();
}


void Shader::CreateShaders()
{
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER);
	
	m_RenderID = glCreateProgram();
	glAttachShader(m_RenderID, vertexShader);
	glAttachShader(m_RenderID, fragmentShader);
	glLinkProgram(m_RenderID);
	glValidateProgram(m_RenderID);

	int success;
	glGetProgramiv(m_RenderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(m_RenderID, 512, nullptr, infoLog);
		std::cerr << "PROGRAM ERROR: " << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

unsigned int Shader::CompileShader(int type)
{
	unsigned int id = glCreateShader(type);
	std::string name;
	
	switch (type)
	{
		case GL_VERTEX_SHADER:
		{
			const char* vertexSource = m_VertexSource.c_str();
			glShaderSource(id, 1, &vertexSource, nullptr);
			glCompileShader(id);
			name = "VERTEX";
			break;
		}
		case GL_FRAGMENT_SHADER:
		{
			const char* fragmentSource = m_FragmentSource.c_str();
			glShaderSource(id, 1, &fragmentSource, nullptr);
			glCompileShader(id);
			name = "FRAGMENT";
			break;
		}

		default:
			std::cerr << "WRONG SHADER TYPE" << std::endl;
	}

	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(id, 512, nullptr, infoLog);
		std::cerr << "SHADER ERROR: "<< name << " ----------- " << infoLog << std::endl;
	}

	return id;
}