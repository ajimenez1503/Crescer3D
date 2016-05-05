#ifndef _SIMPLEFONT_
#define _SIMPLEFONT_

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__LINUX__) || (__CENTOS__)
	#include <GL/gl.h>
	#include "Linux/MicroGlut.h"
#endif
#ifdef __OSX__
	#include <OpenGL/gl3.h>
	#include "mac/MicroGlut.h"
#endif

#include <stdlib.h>
#include <string.h>

void sfMakeRasterFont(void);
void sfDrawString(int h, int v,const char *s);
void sfSetRasterSize(int h, int v);

#ifdef __cplusplus
}
#endif

#endif
