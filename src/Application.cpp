#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Cube.hpp"
#include "Texture.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

static constexpr int WIDTH = 1920;
static constexpr int HEIGHT = 1080;

struct Vec3
{
    float m_X;
    float m_Y;
    float m_Z;

    Vec3(float x, float y, float z)
    {
        m_X = x;
        m_Y = y;
        m_Z = z;
    }
};

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "Matrices", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "ERROR!" << std::endl;
    }

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Vertices */
    float cubeVertices[] = 
    {
          /* Positions */           /* Normals */       /* Tex Coords */
        -0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f
    };

    float lightVertices[] =
    {
        // Positions
        -0.15f, -0.15f,  0.15f,
         0.15f, -0.15f,  0.15f,
         0.15f,  0.15f,  0.15f,
        -0.15f,  0.15f,  0.15f,
                                     
        -0.15f, -0.15f, -0.15f,
         0.15f, -0.15f, -0.15f,
         0.15f,  0.15f, -0.15f,
        -0.15f,  0.15f, -0.15f,
    };

    unsigned int cubeIndices[] = {
        0,  1,  2,
        2,  1,  3,

        4,  5,  6,
        6,  5,  7,

        8,  9,  10,
        10, 9,  11,

        12, 13, 14,
        14, 13, 15,

        16, 17, 18,
        18, 17, 19,

        20, 21, 22,
        22, 21, 23
    };

    /* Indices */
    unsigned int lightIndices[] = {
        0, 1, 2, // Front
        2, 3, 0,

        0, 4, 7, // Left
        7, 3, 0,

        4, 5, 6, // Back
        6, 7, 4,

        4, 0, 1, // Bottom
        1, 5, 4,

        5, 1, 2, // Right
        2, 6, 5,

        6, 2, 3, // Top
        3, 7, 6
    };

    /* View Matrix */
    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 5.0f));
    glm::mat4 view = camera.GetViewMatrix();

    /* Perspective Matrix */
    glm::mat4 perspective = glm::perspective(glm::radians(45.0f), (float) WIDTH / (float) HEIGHT, 0.1f, 20.f);

    /* Light Color */
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

    /* Model Cube */
    Cube cube(cubeVertices, sizeof(cubeVertices), cubeIndices, sizeof(cubeIndices) / sizeof(unsigned int), glm::vec3(0.0f, 0.0f, -2.0f), "res/shaders/Cube.shader");
    cube.Bind();

    cube.AddLayout(3);
    cube.AddLayout(3);
    cube.AddLayout(2);
    cube.SetLayout();

    cube.SetTexture("res/textures/planks.png", "u_PlankDiffuse", 0);
    cube.SetTexture("res/textures/planksSpec.png", "u_PlankSpecular", 1);

    glm::mat4 rotatedCube = glm::rotate(cube.GetModelMatrix(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    cube.UpdateMVP(perspective, view, rotatedCube);
    cube.GetShader().SetUniformMat4("u_Model", rotatedCube);

    cube.Unbind();

    /* Lighting Cube */
    glm::vec3 lightCubePos(0.0f, 0.0f, 0.0f);
    Cube lightCube(lightVertices, sizeof(lightVertices), lightIndices, sizeof(lightIndices) / sizeof(unsigned int), lightCubePos, "res/shaders/Light.shader");
    lightCube.Bind();

    lightCube.AddLayout(3);
    lightCube.SetLayout();
    lightCube.UpdateMVP(perspective, view, lightCube.GetModelMatrix());
    lightCube.GetShader().SetUniform3f("u_LightColor", lightColor.x, lightColor.y, lightColor.z);

    lightCube.Unbind();

    cube.Bind();
    cube.GetShader().SetUniform3f("light.position", lightCubePos.x, lightCubePos.y, lightCubePos.z);
    cube.GetShader().SetUniform3f("light.ambient", 0.3f, 0.3f, 0.3f);
    cube.GetShader().SetUniform3f("light.diffuse", 0.5f, 0.5f, 0.5f);
    cube.GetShader().SetUniform3f("light.specular", 0.5f, 0.5f, 0.5f);
    cube.GetShader().SetUniform3f("currentPos", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
    cube.Unbind();

    Cube* cubes[] = { &cube, &lightCube };

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, WIDTH/2, HEIGHT/2);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Escape to close */
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }

        /* Process keyboard/mouse inputs for the camera */
        camera.ProcessKeyboardInputs(window);
        camera.ProcessMouseMovements(window);

        /* Render here */
        glClearColor(0.047f, 0.176f, 0.282f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Draw Cubes */
        cube.Bind();
        view = camera.GetViewMatrix();
        cube.UpdateMVP(perspective, view, rotatedCube);
        lightCubePos = glm::vec3(7 * glm::cos(1.5 * glfwGetTime()), lightCubePos.y, 7 * glm::sin(1.5 * glfwGetTime()));
        cube.GetShader().SetUniform3f("light.position", lightCubePos.x, lightCubePos.y, lightCubePos.z);
        cube.GetShader().SetUniform3f("currentPos", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        for (int i = 0; i < cube.GetTextures().size(); i++)
        {
            cube.GetTextures()[i].Bind(i);
        }

        glDrawElements(GL_TRIANGLES, cube.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);

        lightCube.Bind();
        view = camera.GetViewMatrix();
        lightCube.UpdateMVP(perspective, view, glm::translate(lightCube.GetModelMatrix(), lightCubePos));
        glDrawElements(GL_TRIANGLES, lightCube.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
