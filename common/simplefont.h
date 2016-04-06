#ifndef _SIMPLEFONT_
#define _SIMPLEFONT_

#include "../project/src/Platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __LINUX__
	#include <GL/gl.h>
	#include "../../common/Linux/MicroGlut.h"
#endif
#ifdef __OSX__
	#include <OpenGL/gl3.h>
	#include "../../common/mac/MicroGlut.h"
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
