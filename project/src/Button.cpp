#include "Button.h"

	Button::Button()
	{
		x=0;
		y=0;
		label="";
		cube=NULL;
		Program=NULL;
	}

	Button::Button(int pos_x,int pos_y, std::string l,GLuint Program_shader)
	{
		sfMakeRasterFont(); // init font
		cube=LoadModelPlus("model/cube/cubeplus.obj");
		x=pos_x;
		y=pos_y;
		label=l;
		Program=Program_shader;
	}

	Button::~Button()
	{
		x=0;
		y=0;
		label="";
		cube=NULL;
		Program=NULL;
	}

	void Button::WriteLabel()
	{
		sfDrawString(x-15,y, label.c_str());
	}

	void Button::set(std::string l,GLuint Program_shader)
	{
		sfMakeRasterFont(); // init font
		cube=LoadModelPlus("model/cube/cubeplus.obj");
		label=l;
		Program=Program_shader;
	}

	void Button::setPosition(int pos_x,int pos_y)
	{
		x=pos_x;
		y=pos_y;
	}


	/*----------------------------------------------------------------------------------------
	 *	\brief	This function draws the specified button.
	 */
	void Button::Draw()
	{
		glDisable(GL_DEPTH_TEST);

		mat4 mdlMatrix;
		mdlMatrix=IdentityMatrix();
		glUseProgram(Program);
		mdlMatrix=Mult(T(x,y,0),S(60,40,1));
		glUniformMatrix4fv(glGetUniformLocation(Program, "mdlMatrix"), 1, GL_TRUE, mdlMatrix.m);
		DrawModel(cube, Program, "inPosition", NULL, NULL);

		/*
		 *	Calculate the x and y coords for the text string in order to center it.
		 */
		WriteLabel();
		glEnable(GL_DEPTH_TEST);
	}
