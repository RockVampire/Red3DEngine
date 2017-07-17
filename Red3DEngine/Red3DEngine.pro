TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

win32
{

}

unix:!macx
{
    LIBS += -lglfw
    LIBS += -lGLEW
    LIBS += -lGL
    LIBS += -lSOIL
}

unix:macx
{
    LIBS+= -framework opengl
    LIBS+= -framework Cocoa -framework IOKit -framework CoreVideo

    LIBS+= -L/usr/local/lib -lglfw3
    LIBS+= -L/usr/local/lib -lGLEW
    LIBS+= -L/usr/local/lib -lSOIL
}

INCLUDEPATH+=/usr/local/include

SOURCES += main.cpp \
    GL/GLProgram.cpp \
    GL/GLShader.cpp \
    GL/GLTexture.cpp \
    GL/GLVAO.cpp \
    GL/TextFile.cpp \

HEADERS += \
    GL/File.hpp \
    GL/RedGL.hpp \