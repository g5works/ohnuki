//opengl
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

//print and stringops
#include <stdio.h>
#include <iostream>
#include <string>

//read shader files
#include <fstream>
#include <sstream>

//custom render classes
#include "rendering/basetypes/gl.h"
#include "rendering/renderlib/renderer.h"

//math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(void)
{

    GLRenderer rndr(PLATFORM_MAC, 640, 640);

    Vertex vertices[36] = {
        {{ -0.5f, -0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f }},
        {{  0.5f, -0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f }},
        {{  0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }},
        {{  0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }},
        {{ -0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }},
        {{ -0.5f, -0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f }},

        {{ -0.5f, -0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f }},
        {{  0.5f, -0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f }},
        {{  0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }},
        {{  0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }},
        {{ -0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }},
        {{ -0.5f, -0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f }},

        {{ -0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f }},
        {{ -0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }},
        {{ -0.5f, -0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }},
        {{ -0.5f, -0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }},
        {{ -0.5f, -0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f }},
        {{ -0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f }},

        {{  0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f }},
        {{  0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }},
        {{  0.5f, -0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }},
        {{  0.5f, -0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }},
        {{  0.5f, -0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f }},
        {{  0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f }},

        {{ -0.5f, -0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }},
        {{  0.5f, -0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }},
        {{  0.5f, -0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f }},
        {{  0.5f, -0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f }},
        {{ -0.5f, -0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f }},
        {{ -0.5f, -0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }},

        {{ -0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }},
        {{  0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }},
        {{  0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f }},
        {{  0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f }},
        {{ -0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f }},
        {{ -0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }}
    };



    GLVertexObject* vo = new GLVertexObject(vertices, 36);


    // OpenGL now knows what we want to draw, but not how it should draw it. For that, we need shaders! (or not, kek)
    GLShaders s("shaders/vertex.glsl", "shaders/fragment.glsl");

    GLTexture t("resources/textures/yippee.gif", 0);
    GLTexture t2("resources/textures/kikuri.png", 1);

    rndr.set(vo);
    rndr.setShader(s);

    t.bind("copper", s);
    t2.bind("blitter", s);

    unsigned int transition = glGetUniformLocation(s.prog, "magnitude");
    unsigned int transuniform = glGetUniformLocation(s.prog, "transform");


    unsigned int b[4] = {1,2,3,4};

    

    unsigned int x = 0;

    while (!glfwWindowShouldClose(rndr.win))
    {
        glHClearErrors();
  

        glm::mat4 trans = glm::mat4(1.0f);

        //these operations are best left on the cpu as the cpu can handle them faster than the cpu due to simd instructions
        trans = glm::rotate(trans, (float)glm::radians(x+0.1), glm::vec3(1.0, 1.0, 1.0));
        trans = glm::scale(trans, glm::vec3(1.0f, 1.0f, 1.0f));


        //set uniform values
        glUniformMatrix4fv(transuniform, 1, GL_FALSE, glm::value_ptr(trans));
        glUniform1f(transition, (0.5+(0.5*sin(((float)x)/50))));


        rndr.draw();


        glfwPollEvents();
        x++;
    } 

    delete vo;

    glfwTerminate();
    return 0;
}






