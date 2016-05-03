#include "Ground.h"

namespace Crescer3D {
Ground::Ground()
{

}
void Ground::init(){
	LoadTGATextureSimple("model/cube/grass.tga", &tex0);
	cube=LoadModelPlus("model/cube/cubeplus.obj");
}


void Ground::draw(mat4 viewMatrix, GLuint program){
	mat4 mdlViewMatrix;
	glUseProgram(program);
	mdlViewMatrix=Mult(viewMatrix,S(100000,1,100000));
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlViewMatrix"), 1, GL_TRUE, mdlViewMatrix.m);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex0);		// Bind Our Texture tex1
	glUniform1i(glGetUniformLocation(program, "tex"), 1); // Texture unit 0
	// draw ground
	DrawModel(cube, program, "inPosition", "inNormal", "inTexCoord");
}

}