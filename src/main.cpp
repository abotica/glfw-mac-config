#include <iostream>
#include <string>

#include "./window/Window.h"
#include "./renderer/Renderer.h"
#include "./model/Model.h"
#include "./shader/Shader.h"
#include "./texture/Texture.h"

#include "./vendor/glm/glm.hpp"

// glm includes
#include "./vendor/glm/gtc/matrix_transform.hpp"
#include "./vendor/glm/gtc/type_ptr.hpp"
#include "./vendor/glm/glm.hpp"

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;

// 3D transformations
// glm::mat4 projection = glm::ortho(-5.0f, 5.0f, -7.0f, 7.0f, 0.1f, 100.0f);
// glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));

glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

glm::vec3 cubePositions[] = {
    glm::vec3(-1.0f, 0.0f, -5.0f),
    glm::vec3(0.0f, 0.0f, -5.0f),
    glm::vec3(1.0f, 0.0f, -5.0f)
};

const float radius = 10.0f;
glm::vec3 cameraTarget(cubePositions[1]);
float cameraRoll = sin(glm::radians(45.0f));;
glm::vec3 cameraPosition(0.0f, 1.0f, cameraRoll);
glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, glm::vec3(0.0, 0.0, -1.0));

glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

glm::vec3 objectColor[] = {
    glm::vec3(1.0f, 0.5f, 0.31f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 1.0f)
};

float specularStrength[] = {
    0.5f,
    0.3f,
    0.9f
};




int main()
{
    Window window("Vjezba4", SCR_WIDTH, SCR_HEIGHT);

     glEnable(GL_DEPTH_TEST);

    Model model("res/models/kocka.obj");
    Model lightModel("res/models/kocka.obj");
    Shader shader("res/shaders/vShader.glsl", "res/shaders/fShader.glsl");
    Texture tex("res/textures/of9ktyw8s2ac1.jpeg");

    Renderer render;

    unsigned int model_VBO, light_VBO;

    glGenBuffers(1, &model_VBO);
    glGenBuffers(1, &light_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, model_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, light_VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(model), &model, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lightModel), &lightModel, GL_STATIC_DRAW);



    while (!window.isClosed())
    {
        window.ProcessInput();
        render.Clear();

        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        // glm::vec3 cameraPosition(camX, cameraRoll, camZ);
        // glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, glm::vec3(0.0, 1.0, 0.0));

        glm::vec3 lightPos(camX, 1.0f, camZ);

        shader.Bind();
        shader.SetUniform4x4("projection", projection);
        shader.SetUniform4x4("view", view);

        
        glm::mat4 mat_lightModel = glm::mat4(1.0f);
        mat_lightModel = glm::translate(mat_lightModel, lightPos);
        mat_lightModel = glm::scale(mat_lightModel, glm::vec3(0.2f));

        shader.SetUniform4x4("model", mat_lightModel);
        shader.SetUniformVec3("lightColor", lightColor);
        shader.SetUniformVec3("lightPos", lightPos);
        shader.SetUniformVec3("viewPos", cameraPosition);
        
        lightModel.Draw(shader, tex);

        for (unsigned int i = 0; i < 3; i++)
        {
            glm::mat4 mat_model = glm::mat4(1.0f);
            mat_model = glm::translate(mat_model, cubePositions[i]);
            mat_model = glm::scale(mat_model, glm::vec3(0.5f));
            float angle = 90.0f * i;
            shader.SetUniform4x4("model", mat_model);
            shader.SetUniformVec3("objectColor", objectColor[i]);
            shader.SetUniformFloat("specularStrength", specularStrength[i]);
           

            model.Draw(shader, tex);
        }

        
        window.SwapAndPoll();
    }
    
    window.CloseWindow();

    return 0;
}
