#include "Cube.h"

namespace Crescer3D
{

Cube::Cube()
{
	positionx=0.0f;
	positiony=2.0f;
	positionz=0.0f;
	velocity = 0.5;
	size=0.5;
}

void Cube::init(int x)
{
	id=x;
	LoadTGATextureSimple("model/cube/grass.tga", &tex1);
	model=LoadModelPlus("model/cube/cubeplus.obj");
}


void Cube::moveForward () {
	positionz-=velocity;
}
void Cube::moveBack(){
	positionz+=velocity;
}
void Cube::moveLeft(){
	positionx-=velocity;
}
void Cube::moveRight () {
	positionx+=velocity;
}
void Cube::moveUp(){

	positiony+=velocity;
	printf("%f\n",positiony );
}
void Cube::moveDown () {

	positiony-=velocity;
	printf("%f\n",positiony );
}
float Cube::getSize(){
	 return size;
}
float Cube::getX(){
	return positionx;
}
float Cube::getY(){
	return positiony;
}
float Cube::getZ(){
	return positionz;
}

void Cube::incrementSize(){
	size+=0.5;
}
void Cube::decrementSize(){
	size-=0.5;
}
void Cube::setPositionX(float x){
	positionx=x;
}
void Cube::setPositionY(float y){
	positiony=y;
}
void Cube::setPositionZ(float z){
	positionz=z;
}
void Cube::setPosition(float x, float y,float z){
	setPositionX(x);
	setPositionY(y);
	setPositionZ(z);
}

void Cube::draw(mat4 viewMatrix, GLuint program){
	mat4 mdlViewMatrix;
	glUseProgram(program);
	mdlViewMatrix = Mult(viewMatrix, Mult(T(positionx,positiony,positionz),S(size,size,size)));
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlViewMatrix"), 1, GL_TRUE, mdlViewMatrix.m);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, tex1);		// Bind Our Texture tex1
	glUniform1i(glGetUniformLocation(program, "tex"), 2); // Texture unit 0
	// draw cube
	DrawModel(model, program, "inPosition", "inNormal", "inTexCoord");
}

vec3  Cube::getMinBox()
{
	vec3 MinB(positionx-size,positiony-size,positionz-size);
	return MinB;
}
vec3  Cube::getMaxBox()
{
	vec3 MaxB(positionx+size,positiony+size,positionz+size);
	return MaxB;
}

}