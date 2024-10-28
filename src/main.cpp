#include <iostream>
#include <string>

#include "./window/Window.h"
#include "./renderer/Renderer.h"
#include "./model/Model.h"
#include "./shader/Shader.h"
#include "./texture/Texture.h"

#include "./vendor/glm/glm.hpp"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Window window("Vjezba3", SCR_WIDTH, SCR_HEIGHT);
  
    Model model("res/models/rectangle.obj");
    Shader shader("res/shaders/vShader.glsl", "res/shaders/fShader.glsl");
    Texture tex("res/textures/of9ktyw8s2ac1.jpeg");

    Renderer render;

    float horizontalOffset = 0.9f;
    float verticalOffset = 0.2f;

    glm::vec3 color(1.0f, 0.0f, 0.0f);

    while (!window.isClosed())
    {
        window.ProcessInput();
        render.Clear();
        
        shader.Bind();
        shader.SetUniformVec3("offset", horizontalOffset, verticalOffset, 0.0f);
        shader.SetUniformVec3("color", color);

        model.Draw(shader, tex);

        window.SwapAndPoll();
    }

    window.CloseWindow();

    return 0;
}