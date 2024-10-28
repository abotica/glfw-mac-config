#pragma once
#include "../vendor/glm/glm.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>

class Shader
{
public:
	Shader() = delete;
	Shader(const std::string& vertexShader, const std::string& fragmentShader);
	~Shader();

	void Bind() const;
	void UnBind() const;

	void SetUniform4x4(const std::string& name, const glm::mat4& value) const;
	void SetUniformVec3(const std::string& name, const float& x, const float& y, const float& z) const;
	void SetUniformVec3(const std::string& name, const glm::vec3& value) const;
	void SetUniformFloat(const std::string& name, const float& value) const;
	void SetUniformInt(const std::string& name, const int& value) const;

	inline const unsigned int GetID() const { return m_RenderID; }

private:
	void LoadShaders(const std::string& vertexPath, const std::string& fragmentPath);
	void CreateShaders();
	unsigned int CompileShader(int type);

private:
	unsigned int m_RenderID;

	std::string m_VertexSource;
	std::string m_FragmentSource;
};