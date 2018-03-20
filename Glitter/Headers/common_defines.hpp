//
// Created by legen on 2/22/2018.
//

#ifndef GLITTER_COMMON_DEFINES_H
#define GLITTER_COMMON_DEFINES_H
#pragma once
#include<glitter.hpp>
#include<iostream>

//#define NDEBUG

//StackOverflow: https://stackoverflow.com/questions/3767869/adding-message-to-assert
#ifndef NDEBUG
#   define ASSERT(condition) \
    do { \
        if (! (condition)) { \
            std::cerr << __FILE__ \
                      << " line " << __LINE__  << std::endl; \
                system("pause");\
            std::exit(1); \
        } \
    } while (false)
#else
#   define ASSERT(condition) do { } while (false)
#endif

#ifndef DISABLE_GLCALL
#   define glCall(x) clearErrors();\
        x;\
        ASSERT(glLog())
#else
#   define glCall(x) x
#endif

static void clearErrors()
{
    while(glGetError());
}

static bool glLog(){

    GLenum err;
    if((err  = glGetError()) != GL_NO_ERROR) {
        std::cerr << "ERROR::OPENGL[" << err << "] - ";
        return false;
    }

   return true;
}

#define EXPAND_MACRO(x) EXPAND_MACRO2(x)
#define EXPAND_MACRO2(y) #y

#endif //GLITTER_COMMON_DEFINES_H

