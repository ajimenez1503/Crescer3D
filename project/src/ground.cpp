#include "ground.h"

 Ground::Ground(){
}
void Ground::init(){
	LoadTGATextureSimple("model/cube/grass.tga", &tex0);
	cube=LoadModelPlus("model/cube/cubeplus.obj");
}


void Ground::draw(mat4 total,GLuint program){
	mat4 mdlMatrix;
	glUseProgram(program);
	mdlMatrix=Mult(total,S(100000,1,100000));
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, mdlMatrix.m);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex0);		// Bind Our Texture tex1
	glUniform1i(glGetUniformLocation(program, "tex"), 0); // Texture unit 0
	// draw ground	
	DrawModel(cube, program, "inPosition", "inNormal", "inTexCoord");
}
