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

void Cube::init(int x, GLuint shader)
{
	id = x;
	m_Model = LoadModelPlus("model/cube/cubeplus.obj");
	m_Shader = shader;
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

void Cube::draw(mat4 viewMatrix, vec3 cameraPos) {
	glUseProgram(m_Shader);
	mat4 mdlViewMatrix = Mult(viewMatrix, Mult(T(positionx,positiony,positionz),S(size,size,size)));
	glUniformMatrix4fv(glGetUniformLocation(m_Shader, "mdlViewMatrix"), 1, GL_TRUE, mdlViewMatrix.m);
	glUniform3fv(glGetUniformLocation(m_Shader, "cameraPosition"), 1, &cameraPos.x);
	DrawModel(m_Model, m_Shader, "inPosition", "inNormal", "inTexCoord");
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