#ifndef __CHECKERROR_HPP
#define	__CHECKERROR_HPP

#include "glad/glad.h"
#include <iostream>

/**
* Print tous les messages d'erreur
*/
void dumpGlErrorStack();
/**
* Print seulement la derniere erreur
*/
void dumpLastGlError();

/**
* Macros à placer en dessous d'appels opengl quand tout part en steak
*/
#define GL_ERROR_STACK() {std::cout << __FILE__ << " (" << __LINE__ << ") :" << std::endl; dumpGlErrorStack(); std::cout << std::endl << std::endl;}
#define GL_ERROR() {std::cout << __FILE__ << " (" << __LINE__ << ") : ";  dumpLastGlError(); std::cout << std::endl;}

#endif
