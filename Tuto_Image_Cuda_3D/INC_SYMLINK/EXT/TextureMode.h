#ifndef TEXTUREMODE_H_
#define TEXTUREMODE_H_

#include <GL/glew.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

enum TextureMode
    {
    MODE_REPEAT = GL_REPEAT,
    MODE_MIRROR = GL_MIRRORED_REPEAT,
    MODE_CLAMP = GL_CLAMP
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
