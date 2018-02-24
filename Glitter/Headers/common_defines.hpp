//
// Created by legen on 2/22/2018.
//

#ifndef GLITTER_COMMON_DEFINES_H
#define GLITTER_COMMON_DEFINES_H
#pragma once
#include<glitter.hpp>
#include<iostream>

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
#   define ASSERT(condition, message) do { } while (false)
#endif

#ifndef DISABLE_GLCALL
#   define glCall(x) clearErrors();\
        x;\
        ASSERT(glLog())
#else
#   define glCall(x) do { } while (false)
#endif

static void clearErrors()
{
    while(glGetError());
}

/*Will call the macro assert to interrupt compiler if
there is an error*/
static bool glLog(){

    if(GLenum err  = glGetError() != GL_NO_ERROR) {
        std::cerr << "ERROR::OPENGL[" << err << "] - ";
        return false;
    }

   return true;
}
#endif //GLITTER_COMMON_DEFINES_H
