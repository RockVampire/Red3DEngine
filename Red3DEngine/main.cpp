/*
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GL/RedGL.hpp"
#include "GL/File.hpp"
#include "SHADER/Shader.hpp"

GLFWwindow* window;

int width = 500;
int height = 600;

int main( void )
{
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow( 640, 480, "RedVideo", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLShader * v_shader = new GLShader(GL_VERTEX_SHADER,SKY_VERTEX);
    GLShader * f_shader = new GLShader(GL_FRAGMENT_SHADER,SKY_FRAGMENT);

    GLProgram * program = new GLProgram();
    program->AddShader(v_shader);
    program->AddShader(f_shader);
    program->LinkProgram();

    GLfloat vertices[] = {
        1.0f, 1.0, 0.0f,   // 右上角
        1.0f, -1.0f, 0.0f,  // 右下角
        -1.0f, -1.0f, 0.0f, // 左下角
        -1.0f, 1.0f, 0.0f   // 左上角
    };

    GLuint indices[] = { // 注意索引从0开始!
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    GLfloat txtcoor[] = {
        1.0f, 1.0, 0.0f,   // 右上角
        1.0f, 0.0f, 0.0f,  // 右下角
        0.0f, 0.0f, 0.0f, // 左下角
        0.0f, 1.0f, 0.0f   // 左上角
    };

    GLVAO * vao = new GLVAO();

    printf("Size:%d\n",sizeof(indices));
    vao->AddVBO(vertices,sizeof(vertices),0,3);
    vao->AddVBO(txtcoor,sizeof(txtcoor),1,3);
    vao->SetEBO(indices,sizeof(indices));


    GLTexture * y = new GLTexture();
    GLTexture * u = new GLTexture();
    GLTexture * v = new GLTexture();

    printf("\n\nwidth:%d\n",width);
    printf("height:%d\n",height);

    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 )
    {
        glClear( GL_COLOR_BUFFER_BIT );

        glUseProgram(program->ProgramId);

        vao->DrawVAO();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //glDeleteBuffers(1, &vertexbuffer);
    //glDeleteVertexArrays(1, &VertexArrayID);
    //glDeleteProgram(programID);

    delete v_shader;
    delete f_shader;
    delete program;
    delete vao;

    glfwTerminate();

    return 0;
}
*/


#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "GL/File.hpp"

#include "Engine/Engine.hpp"
#include "Engine/RedGame.hpp"


GLFWwindow* window;

int width = 2560;
int height = 1600;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow * window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main( void )
{
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    //Mac上不能加这句
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    //glfwWindowHint(GLFW_DECORATED, GL_FALSE);
    //glfwWindowHint(GLFW_DECORATED, GL_FALSE);

    window = glfwCreateWindow(width, height, "Red3DEngine", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwWindowHint(GLFW_DECORATED, GL_FALSE);

    // Set the required callback functions
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //隐藏鼠标
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    int scrWidth, scrHeight;
    glfwGetFramebufferSize(window, &scrWidth, &scrHeight);

    Screen * screen = Screen::getInstance();
    screen->setWidthAndHeight(scrWidth,scrHeight);

    RedGame * redgame = new RedGame();
    redgame->Start();


    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 )
    {
        redgame->Update();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    redgame->End();
    delete redgame;

    glfwTerminate();

    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Screen * screen = Screen::getInstance();
    screen->setWidthAndHeight(width,height);
}

void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
    Input * input = Input::getInstance();
    input->setMousePoint((float)xpos, (float)ypos);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    Input * input = Input::getInstance();
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS){
            input->keys[key] = true;
        }
        else if (action == GLFW_RELEASE){
            input->keys[key] = false;
        }
    }
}
