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



GLRenderer::GLRenderer(unsigned int platform) {

    GLFWwindow* window; 
    {
        /* Initialize the library */
        if (!glfwInit())
            exit(-1);
        
        //this is some mac specific bs
        if (platform == PLATFORM_MAC) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        }


        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 640, "opengl", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            exit(-1);
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        if (glewInit() != GLEW_OK)
            std::cout << "GLEW INIT ERROR!!" << "\n";

        std::cout << glGetString(GL_VERSION) << std::endl;
    }

    win = window;

}

void GLRenderer::setShader(GLShaders shader) {
    shader.use();
}

void GLRenderer::set(GLVertexObject *vertices) {
    drawmode = VERTEX_DRAW;
    vx = vertices;

    vertices->bind();
}

void GLRenderer::set(GLVertexObject *vertices, GLIndices *indices) {
    drawmode = INDEX_DRAW;

    vx = vertices;
    ix = indices;

    vertices->bind();
    indices->bind();
}

void GLRenderer::draw() {
  
    glClear(GL_COLOR_BUFFER_BIT);

    if (drawmode == VERTEX_DRAW) {

        unsigned int vc = vx->cnt;
        
        if ((vc%3) == 0) {
            glHCheckingCall(glDrawArrays(GL_TRIANGLES, 0, vx->cnt));
        }

        else {
            std::cout << "Vertices can only be rendered in tris. Did you mean to use an Index Buffer?" << std::endl;
            ASSERT(false);
            exit(-1);
        }
        
    }

    else if (drawmode == INDEX_DRAW) {

        glDrawElements(GL_TRIANGLES, (ix->cnt)*3, GL_UNSIGNED_INT, nullptr);
    }

    else {
        std::cout << "Invalid draw mode" << std::endl;
        ASSERT(false);
        exit(-1);
    }

    glfwSwapBuffers(win);

}
