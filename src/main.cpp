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

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 3D transformations
glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

// glm::mat4 projection = glm::ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT, 0.1f, 100.0f);
// glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)};

int main()
{
    Window window("Vjezba3", SCR_WIDTH, SCR_HEIGHT);

    Model model("res/models/rectangle.obj");
    Shader shader("res/shaders/vShader.glsl", "res/shaders/fShader.glsl");
    Texture tex("res/textures/of9ktyw8s2ac1.jpeg");

    Renderer render;

    float horizontalOffset = 0.0f;
    float verticalOffset = 0.0f;

    glm::vec3 color(1.0f, 1.0f, 1.0f);

    // 3D transformations
    // mat_model = glm::rotate(mat_model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    while (!window.isClosed())
    {
        window.ProcessInput();
        render.Clear();

        shader.Bind();
        shader.SetUniformVec3("offset", horizontalOffset, verticalOffset, 0.0f);
        shader.SetUniformVec3("color", color);


         for (unsigned int i = 0; i < 3; i++)
        {
            glm::mat4 mat_model = glm::mat4(1.0f);
            mat_model = glm::translate(mat_model, cubePositions[i]);
            float angle = 20.0f * i;
            mat_model = glm::rotate(mat_model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.SetUniform4x4("model", mat_model);
            shader.SetUniform4x4("view", view);
            shader.SetUniform4x4("projection", projection);
            

            // glDrawArrays(GL_TRIANGLES, 0, 36);
            model.Draw(shader, tex);
        }


        window.SwapAndPoll();
    }

    window.CloseWindow();

    return 0;
}