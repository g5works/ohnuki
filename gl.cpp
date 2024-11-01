#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "gl.h"


// OpenGL VertexBuffer/VertexArray Abstractions
GLVertexObject::GLVertexObject(Vertex vertices[], unsigned int vs) {

    cnt = vs;

    //create our hotswappable vertex array
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //generate our buffer and bind it to opengl as a vertex buffer
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //put the data into the vertex buffer
    //the second is the acc size of the buffer in bytes, while the third is just the straight buffer data
    //GL_STATIC_DRAW tells opengl that we're using this to draw on the screen, and that the buffer won't change rapidly.
    glBufferData(GL_ARRAY_BUFFER, vs * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    //define our 2 vertex attributes
    //ID, Number of terms, Type, Normalization Desired?, Vertex Size, Stride in bytes to this point
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vertex::position)));

    //turn em on
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    bind();


};    

void GLVertexObject::bind() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void GLVertexObject::bindArray() {
    glBindVertexArray(vao);
}

void GLVertexObject::bindBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 
}


// OpenGL IndexBuffer Abstractions
GLIndices::GLIndices(IndexTri indices[], unsigned int tricnt) {

    cnt = tricnt;

    //create that buffer
    glGenBuffers(1, &ibo);
    //make it index
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    //pour data in
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tricnt*sizeof(IndexTri), indices, GL_STATIC_DRAW);
    bind();

}

void GLIndices::bind() {

    //what do you THINK this does, dumbass
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

}
    

//OpenGL Shader Abstractions
GLShaders::GLShaders(std::string v, std::string f) {

     //make an id for the program returned by opengl
    unsigned int program = glCreateProgram();
   
   //compile these shaders with some custom gl helper functions i wrote!
    unsigned int vshader = compile(readshaderfile(v), GL_VERTEX_SHADER);
    unsigned int fshader = compile(readshaderfile(f), GL_FRAGMENT_SHADER);

    //attach the shaders to the program we create for the gpu
    glAttachShader(program, vshader);
    glAttachShader(program, fshader);

    //link the program to opengl
    glLinkProgram(program);



    glValidateProgram(program);

    frag = fshader;
    vert = vshader;

    glDeleteShader(vshader);
    glDeleteShader(fshader);
    
    //delete these intermediary functions as we have linked up the program


    //get the program validation state
    int params;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &params);

    if (params == GL_TRUE) {
        std::cout << "The program was able to link and validate successfully!!" << std::endl;
    }
 
    else {
        std::cout << "The program did not validate properly with error:" << std::endl;

        int len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

        char* log = (char*)alloca(len*sizeof(char));
        glGetProgramInfoLog(program, len, &len, log);
        std::cout << log << std::endl;

        exit(-1);

    }

    prog = program;

}

void GLShaders::use() {
    glUseProgram(prog);
}

std::string GLShaders::readshaderfile(std::string shaderPath) {

    std::ifstream stream(shaderPath);
    std::stringstream shader;

    std::string line;

    while (getline(stream, line)) {

        shader << line << "\n";

    }

    return shader.str();

}


unsigned int GLShaders::compile(const std::string &shadersource, unsigned int shadertype) {

    //this creates the opengl shader and returns a shader id, just like when we created the buffer.
    unsigned int shader;
    shader = glCreateShader(shadertype);

    //this just converts the string we pump in to a c char array, which is just a system of bytes.
    const char *source = shadersource.c_str();

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int param;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &param);

    if (param == GL_FALSE) {


        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        char* message = (char*) alloca(length * sizeof(char));

        glGetShaderInfoLog(shader, length, &length, message);

        std::cout << "The " << (shadertype == GL_FRAGMENT_SHADER ? "fragment" : "vertex") << " shader failed to compile successfully with the following error:" << std::endl;
        std::cout << message << std::endl;
        exit(-1);

    }
    else {
        std::cout << "The " << (shadertype == GL_FRAGMENT_SHADER ? "fragment" : "vertex") << " shader compiled successfully!" << std::endl;
    }

    return shader;

}
