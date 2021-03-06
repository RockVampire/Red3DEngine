#pragma once

#include "GL/File.hpp"
#include "GLFW/glfw3.h"
#include "Engine/Engine.hpp"
#include "SHADER/Shader.hpp"
#include "UI/UI.hpp"

#include "IMAGE/stb_image.h"

#include <ft2build.h>
#include FT_FREETYPE_H



glm::vec3 cameraPos;
glm::vec3 cameraFront;
glm::vec3 cameraUp;

GLfloat yaw   = -90.0f;
GLfloat pitch = 0.0f;
GLfloat lastX = 0.0f;
GLfloat lastY = 0.0f;
bool firstMouse = true;

//void do_movement();

class RedScript
{
public:
    GLProgram * program;
    GLProgram * sky_program;

    Model * m;
    Camera * mainCamera;

    //四个点光源
    PBRLight * light0;
    PBRLight * light1;
    PBRLight * light2;
    PBRLight * light3;

    GLTexture * albedoMap;
    GLTexture * metallicMap;
    GLTexture * roughnessMap;
    GLTexture * normalMap;
    GLTexture * aoMap;

    PBRMaterial * pbrMaterial;

    GLVAO * sky_vao;

    SkyBox * skybox;

    UIText * t;


    GLProgram * backgroundShader;

    void Start(){

        albedoMap = new GLTexture();
        albedoMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/coat/export3dcoat_lambert3SG_color.png");
        metallicMap = new GLTexture();
        metallicMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/coat/export3dcoat_lambert3SG_metalness.png");
        roughnessMap = new GLTexture();
        roughnessMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/coat/export3dcoat_lambert3SG_gloss.png");
        normalMap = new GLTexture();
        normalMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/coat/export3dcoat_lambert3SG_nmap.png");
        aoMap = new GLTexture();
        aoMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/coat/materialball_ao.png");

        /*
        albedoMap = new GLTexture();
        albedoMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Cerberus_by_Andrew_Maximov/T/Cerberus_A.png");
        //albedoMap->LoadImage("/Users/redknot/Desktop/wx10.jpg");
        metallicMap = new GLTexture();
        metallicMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Cerberus_by_Andrew_Maximov/T/Cerberus_M.png");
        roughnessMap = new GLTexture();
        roughnessMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Cerberus_by_Andrew_Maximov/T/Cerberus_N.png");
        normalMap = new GLTexture();
        normalMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Cerberus_by_Andrew_Maximov/T/Cerberus_R.png");
        aoMap = new GLTexture();
        aoMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Cerberus_by_Andrew_Maximov/T/Cerberus_AO.png");
        */

        /*
        albedoMap = new GLTexture();
        albedoMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Tea/tea_DefaultMaterial_BaseColor.png");
        metallicMap = new GLTexture();
        metallicMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Tea/tea_DefaultMaterial_Metallic.png");
        roughnessMap = new GLTexture();
        roughnessMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Tea/tea_DefaultMaterial_Roughness.png");
        normalMap = new GLTexture();
        normalMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Tea/tea_DefaultMaterial_Normal.png");
        aoMap = new GLTexture();
        aoMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Tea/tea_DefaultMaterial_Height.png");
        */


        /*
        albedoMap = new GLTexture();
        albedoMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Tea/rustediron/rustediron2_basecolor.png");
        metallicMap = new GLTexture();
        metallicMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Tea/rustediron/rustediron2_metallic.png");
        roughnessMap = new GLTexture();
        roughnessMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Tea/rustediron/rustediron2_roughness.png");
        normalMap = new GLTexture();
        normalMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Tea/rustediron/rustediron2_normal.png");
        aoMap = new GLTexture();
        //aoMap->LoadImage("/Users/redknot/Red3DEngine/3dModel/Tea/rustediron/rustediron2_metallic.png");
        */


        pbrMaterial = new PBRMaterial();
        pbrMaterial->setAlbedoMap(albedoMap);
        pbrMaterial->setMetallicMap(metallicMap);
        pbrMaterial->setNormalMap(normalMap);
        pbrMaterial->setRoughnessMap(roughnessMap);
        pbrMaterial->setAoMap(aoMap);



        GLShader * backgroundShader_V = new GLShader(GL_VERTEX_SHADER,Background_VERTEX);
        GLShader * backgroundShader_F = new GLShader(GL_FRAGMENT_SHADER,Background_FRAGMENT);

        backgroundShader = new GLProgram();
        backgroundShader->AddShader(backgroundShader_V);
        backgroundShader->AddShader(backgroundShader_F);
        backgroundShader->LinkProgram();


        GLShader * sky_v_shader = new GLShader(GL_VERTEX_SHADER,SKY_VERTEX);
        GLShader * sky_f_shader = new GLShader(GL_FRAGMENT_SHADER,SKY_FRAGMENT);

        sky_program = new GLProgram();
        sky_program->AddShader(sky_v_shader);
        sky_program->AddShader(sky_f_shader);
        sky_program->LinkProgram();



        GLShader * v_shader = new GLShader(GL_VERTEX_SHADER,PBR_VERTEX);
        GLShader * f_shader = new GLShader(GL_FRAGMENT_SHADER,PBR_FRAGMENT);

        program = new GLProgram();
        program->AddShader(v_shader);
        program->AddShader(f_shader);
        program->LinkProgram();

#ifdef __ANDROID__
        std::string path = "/storage/emulated/0/3D/nano";
        //std::string path = "/data/data/com.redknot.red3dengineandroid/cache/nano";
#else
        std::string path = "/Users/redknot/Red3DEngine/3dModel/coat/Model";
        //std::string path = "/Users/redknot/Red3DEngine/3dModel/Tea/model";
        //std::string path = "/Users/redknot/Red3DEngine/3dModel/Cerberus_by_Andrew_Maximov/Cerberus_LP";
        //std::string path = "/Users/redknot/Red3DEngine/3dModel/qiu";
#endif

        m = new Model(path);

        //light
        light0 = new PBRLight();
        light0->setColor(300.0f,300.0f,300.0f);
        light0->setPosition(-10.0f,  10.0f, 10.0f);

        light1 = new PBRLight();
        light1->setColor(300.0f,300.0f,300.0f);
        light1->setPosition(10.0f,  10.0f, 10.0f);

        light2 = new PBRLight();
        light2->setColor(300.0f,300.0f,300.0f);
        light2->setPosition(-10.0f, -10.0f, 10.0);

        light3 = new PBRLight();
        light3->setColor(300.0f,300.0f,300.0f);
        light3->setPosition(10.0f, -10.0f, 10.0f);


        //Camera
        int width = 1280;
        int height = 720;

        cameraPos.x = 0.0f;
        cameraPos.y = 0.0f;
        cameraPos.z = 30.0f;

        cameraFront.x = 0.0f;
        cameraFront.y = 0.0f;
        cameraFront.z = -1.0f;

        cameraUp.x = 0.0f;
        cameraUp.y = 1.0f;
        cameraUp.z = 0.0f;

        mainCamera = new Camera(30.0f,width * 1.0f,height * 1.0f,0.1f,1000.0f);

        //绘制天空盒子
        vector<std::string> faces =
        {
            "/Users/redknot/Red3DEngine/Texture/SkyBox/right.jpg",
            "/Users/redknot/Red3DEngine/Texture/SkyBox/left.jpg",
            "/Users/redknot/Red3DEngine/Texture/SkyBox/top.jpg",
            "/Users/redknot/Red3DEngine/Texture/SkyBox/bottom.jpg",
            "/Users/redknot/Red3DEngine/Texture/SkyBox/back.jpg",
            "/Users/redknot/Red3DEngine/Texture/SkyBox/front.jpg"
        };
        skybox = new SkyBox();
        skybox->loadTexture(&faces);

        t = new UIText("Redknot Miaoyuqiao",250,-1.0f,1.0f);
        t->setText("miaowumiaowu");

        Screen * screen = Screen::getInstance();

        lastX = screen->getWidth()  / 2.0;
        lastY = screen->getHeight() / 2.0;
        //glViewport(0, 0, screen->getWidth(), screen->getHeight());

    }

    float w = 0.0f;

    void Update(){

        t->Draw();



        do_movement();


        Input * input = Input::getInstance();
        mouse_callback(input->getMousePoint().x,input->getMousePoint().y);


        //do_movement();
        Screen * screen = Screen::getInstance();
        mainCamera->setCameraWidthHeight(screen->getWidth(),screen->getHeight());
        mainCamera->setCameraPos(cameraPos.x,cameraPos.y,cameraPos.z);
        mainCamera->setCameraFront(cameraFront.x,cameraFront.y,cameraFront.z);
        mainCamera->setCameraUp(cameraUp.x,cameraUp.y,cameraUp.z);

        sky_program->UseProgram();
        skybox->UseSkyBox(sky_program, mainCamera);


        program->UseProgram();
        pbrMaterial->UseMaterial(program);

        //更新相机位置
        mainCamera->UseCamera(program);

        //更新灯光
        light0->UseLight(program,0);
        light1->UseLight(program,1);
        light2->UseLight(program,2);
        light3->UseLight(program,3);

        //更新模型位置
        int nrRows    = 10;
        int nrColumns = 10;
        float spacing = 1.5;

        pbrMaterial->UseMaterial(program);

/*
        glm::mat4 model;
        for (unsigned int row = 0; row < nrRows; ++row)
        {
            glUniform1f(program->GetUniformLocation("out_metallic"),(float)row / (float)nrRows);
            for (unsigned int col = 0; col < nrColumns; ++col)
            {
                glUniform1f(program->GetUniformLocation("out_roughness"),glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f));
                model = glm::mat4();
                model = glm::translate(model, glm::vec3(
                    (float)(col - (nrColumns / 2.0f)) * spacing,
                    (float)(row - (nrRows / 2.0f)) * spacing,
                    0.0f
                ));
                glUniformMatrix4fv(program->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
                m->Draw(program);
            }
        }

*/

        glm::mat4 model;
        model = glm::scale(model,glm::vec3(0.5f));
        model = glm::rotate(model,glm::radians(-90.0f),glm::vec3(1.0f,0.0f,0.0f));
        model = glm::rotate(model,glm::radians(-w),glm::vec3(0.0f,0.0f,1.0f));
        w = w + 0.1f;


        glUniformMatrix4fv(program->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));

        m->Draw(program);


        //t->setText("miaowumiaowu");
        //t->Draw();
    }

    void End()
    {
        delete program;
        delete sky_program;
        delete mainCamera;
        delete m;

        delete light0;
        delete light1;
        delete light2;
        delete light3;
    }

    void mouse_callback(double xpos, double ypos)
    {
        if(firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        GLfloat xoffset = xpos - lastX;
        GLfloat yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        GLfloat sensitivity = 0.2f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);
    }

    void do_movement()
    {
        Input * input = Input::getInstance();

        GLfloat cameraSpeed = 0.07f;
        if (input->keys[GLFW_KEY_W])
            cameraPos += cameraSpeed * cameraFront;
        if (input->keys[GLFW_KEY_S])
            cameraPos -= cameraSpeed * cameraFront;
        if (input->keys[GLFW_KEY_A])
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (input->keys[GLFW_KEY_D])
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
};







