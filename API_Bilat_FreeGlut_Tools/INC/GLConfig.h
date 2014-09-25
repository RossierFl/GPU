#ifndef GL_CONFIG_H
#define GL_CONFIG_H

#ifdef _WIN32
    #include <windows.h>
    #include <glew.h>
    #include <glut.h>
    #include "freeglut_ext.h"
#else
    #include <GL/glew.h>
    #include <GL/freeglut.h>
    #include <GL/freeglut_ext.h>
#endif

#endif
