#ifndef _BUTTON_H
#define _BUTTON_H

#ifdef __LINUX__
	extern "C"
	{
		#define GL_GLEXT_PROTOTYPES
		#include "../../common/Linux/MicroGlut.h"
	}
#endif
#ifdef __CENTOS__
	extern "C"
	{
		#define GL_GLEXT_PROTOTYPES
		#include "../../common/Linux/MicroGlut.h"
	}
#endif
#ifdef __OSX__
	extern "C"
	{
		#include <OpenGL/gl3.h>
		#include "../../common/mac/MicroGlut.h"
	}
#endif

#include "../../common/GL_utilities.h"
#include "../../common/loadobj.h"
#include "../../common/VectorUtils3.h"
#include <string>
#include "../../common/simplefont.h"
#include "Window.h"


namespace Crescer3D
{
	class Button
	{
	public:
		Button();
		Button(int pos_x,int pos_y, std::string l,GLuint Program_shader);
		~Button();
		void Draw();
		void set(std::string l,GLuint Program_shader);
		void setPositionSize(int pos_x,int pos_y,int w,int h);
		bool isClick();
		void ClickFalse();
		void ClickTest(int x_pos,int y_pos);

	private:
		 Model *cube;
		 int   x;							/* top left x coord of the button */
		 int   y;							/* top left y coord of the button */
		 int   width;							/* the width of the button */
		 int   height;							/* the height of the button */
		 bool click;
		 GLuint Program;
		 std::string label;				/* the text label of the button */
		 void WriteLabel();
	};
}

#endif // _BUTTON_H
