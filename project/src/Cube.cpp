#include "Cube.h"

namespace Crescer3D
{

	// Forward Declaration of Static Stuff
	Model* Cube::m_Model;
	GLuint Cube::m_Texture = 0;

Cube::Cube()
{

	positionx=0.0f;
	positiony=2.0f;
	positionz=0.0f;
	velocity = 0.5;
	size=0.5;

	m_is_init=false;
	color = vec3( (((double) std::rand() / (double) RAND_MAX) / 2.0 + 0.5),
				  (((double) std::rand() / (double) RAND_MAX) / 2.0 + 0.5),
				  (((double) std::rand() / (double) RAND_MAX) / 2.0 + 0.5) );
}

void Cube::init(int x, GLuint shader)
{
	id = x;
	if(m_Model == NULL)
		m_Model = LoadModelPlus("model/cube/cubeplus.obj");
	m_Shader = shader;
	if(m_Texture == 0) {
		glUseProgram(m_Shader);
		glActiveTexture(GL_TEXTURE3);
		LoadTGATextureSimple("model/cube/wall3.tga", &m_Texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	m_is_init=true;
}

bool Cube::isInit()
{
	return m_is_init;
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

void Cube::setRndPosition(int x_max,int x_min,int y_max,int y_min)
{
	float new_x=(float)(std::rand() % (x_max-x_min) + x_min);
	float new_z=(float)(std::rand() % (y_max-y_min) + y_min);

	setPositionX(new_x);
	setPositionZ(new_z);
	setPositionY(2.0);

	if(new_x<20.0&&new_z<20.0)
	{
		this->setRndPosition(x_max,x_min,y_max,y_min);
	}
}

int Cube::getID()
{
	return id;
}

void Cube::draw(mat4 viewMatrix, vec3 cameraPos, GLuint shader) {
	if(shader == 666)
		shader = m_Shader;
	vec3 lightPos = Light::GetLightPosition();
	glUseProgram(shader);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glUniform1i(glGetUniformLocation(shader, "tex"), 3);
	mat4 worldMatrix = Mult(T(positionx,positiony,positionz),S(size,size,size));
	glUniformMatrix4fv(glGetUniformLocation(shader, "viewMatrix"), 1, GL_TRUE, viewMatrix.m);
	glUniformMatrix4fv(glGetUniformLocation(shader, "worldMatrix"), 1, GL_TRUE, worldMatrix.m);
	glUniform3fv(glGetUniformLocation(shader, "cameraPosition"), 1, &cameraPos.x);
	glUniform3fv(glGetUniformLocation(shader, "lightPosition"), 1, &lightPos.x);
	glUniform3fv(glGetUniformLocation(shader, "objectColor"), 1, &color.x);
	DrawModel(m_Model, shader, "inPosition", "inNormal", "inTexCoord");
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
