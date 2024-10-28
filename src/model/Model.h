#pragma once

#include <string>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#include "../vendor/glm/glm.hpp"

#include "../shader/Shader.h"
#include "../texture/Texture.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCordinates;

    Vertex(glm::vec3 pos, glm::vec3 norm = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2 texCor = glm::vec3(0.0f, 0.0f, 0.0f));
};

class Mesh
{
public:
    Mesh() = delete;
    Mesh(const std::string& meshPath);
    ~Mesh();

    void Draw(const Shader& shader, const Texture& texture) const;

private:
    void LoadMesh(const std::string& meshPath);
    void SetupMesh();

private:
    unsigned int m_RenderID;
    unsigned int m_VBO, m_EBO;

    std::vector<Vertex> m_Mesh;
    std::vector<int> m_Indices;
};

class Model
{
public:
    Model() = delete;
    Model(const std::string& meshPath);
    ~Model();

    void Draw(const Shader& shader, const Texture& texture) const;
private:
    std::unique_ptr<Mesh> m_Mesh;
};