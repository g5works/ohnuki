#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "gl.h"
#include "renderer.h"

int main(void)
{

    GLRenderer rndr(PLATFORM_MAC);

    Vertex vertices[4] = {
       {{ -0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f }},
       {{  0.5f,  0.5f, 0.0f }, { 0.5f, 0.5f, 0.5f }},
       {{ -0.5f, -0.5f, 0.0f }, { 0.5f, 0.5f, 0.5f }},
       {{  0.5f, -0.5f, 0.0f }, { 0.2f, 0.2f, 0.2f }},
    };

    IndexTri indices[2] = {
        {0,1,2},
        {1,3,2}
    };

    Vertex vertices2[3] = {
       {{ -0.5f,  0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f }},
       {{  0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }},
       {{ -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }},
    };


    GLVertexObject* vo = new GLVertexObject(vertices, 4);
    GLVertexObject* vo2 = new GLVertexObject(vertices2, 3);

    GLIndices* i = new GLIndices(indices, 2);

    // OpenGL now knows what we want to draw, but not how it should draw it. For that, we need shaders! (or not, kek)
    GLShaders s("shaders/vertex.glsl", "shaders/fragment.glsl");
    GLShaders s2("shaders/vertex.glsl", "shaders/fragment2.glsl");


    rndr.setShader(s);
    rndr.set(vo, i);

    unsigned int x = 0;
    unsigned int y = 0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(rndr.win))
    {
        glHClearErrors();
        x++;

        rndr.draw();
        glfwPollEvents();
    } 

    delete vo;
    delete vo2;
    delete i;

    glfwTerminate();
    return 0;
}




