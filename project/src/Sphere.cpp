#include "Sphere.h"

namespace Crescer3D
{

	// Forward Declaration of Static Stuff
	Model* Sphere::m_Model;
	GLuint Sphere::m_Texture = 0;

void Sphere::moveForward () {
	positionz-=velocity;
	increaseWayWent();
}
void Sphere::moveBack(){
	positionz+=velocity;
	increaseWayWent();
}
void Sphere::moveLeft(){
	positionx-=velocity;
	increaseWayWent();
}
void Sphere::moveRight () {
	positionx+=velocity;
	increaseWayWent();
}

void Sphere::moveAngle(float angle){
	positionx+=cos(angle*M_PI/180)*velocity;
	positionz+=sin(angle*M_PI/180)*velocity;

	increaseWayWent();
}

float Sphere::getX(){
	return positionx;
}
float Sphere::getY(){
	return positiony;
}
float Sphere::getZ(){
	return positionz;
}
vec3 Sphere::getPosition() {
	return vec3(positionx, positiony, positionz);
}

void Sphere::incrementRadius(){
	radius+=0.5;
}
void Sphere::decrementRadius(){
	radius-=0.5;
}

void Sphere::setRadius(float in_radius){	
	radius=in_radius;
	this->setVelocity(1.0/radius);
}

float Sphere::getRadius(){
	 return radius;
}

void Sphere::setVelocity(float in_velocity)
{
	velocity=in_velocity;
}
float Sphere::getVelocity()
{
	return velocity;
}


void Sphere::setPositionX(float x){
	positionx=x;
}
void Sphere::setPositionY(float y){
	positiony=y;
}
void Sphere::setPositionZ(float z){
	positionz=z;
}
void Sphere::setPosition(float x, float y,float z)
{
	setPositionX(x);
	setPositionY(y);
	setPositionZ(z);
}
void Sphere::setRndPosition(int x_max,int x_min,int y_max,int y_min)
{
	setPositionX((float)(std::rand() % (x_max-x_min) + x_min));
	setPositionZ((float)(std::rand() % (y_max-y_min) + y_min));
	setPositionY(radius);
}

float Sphere::getWayWent()
{
	return m_way_went;
}

void Sphere::increaseWayWent()
{
	m_way_went+=velocity;
}

void Sphere::setWayWent(float way_went)
{
	m_way_went=way_went;
}


int Sphere::getID()
{
	return id;
}

Sphere::Sphere()
{
	
	positionx=0.0f;
	positiony=1.0f;
	positionz=0.0f;
	velocity = 0.5;
	radius=1.0;
	
	m_is_init=false;
	color = vec3( (((double) std::rand() / (double) RAND_MAX) / 2.0 + 0.5),
				  (((double) std::rand() / (double) RAND_MAX) / 2.0 + 0.5),
				  (((double) std::rand() / (double) RAND_MAX) / 2.0 + 0.5) );
}

void Sphere::init(int x, GLuint shader)
{
	id=x;
	m_Shader = shader;
	if(m_Model == NULL)
		m_Model=LoadModelPlus("model/sphere/groundsphere.obj");
	if(m_Texture == 0) {
		glUseProgram(m_Shader);
		glActiveTexture(GL_TEXTURE3);
		LoadTGATextureSimple("model/cube/wall3.tga", &m_Texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	m_is_init=true;
}

bool Sphere::isInit()
{
	return m_is_init;
}

void Sphere::draw(mat4 viewMatrix, vec3 cameraPos, GLuint shader) {
	if(shader == 666)
		shader = m_Shader;
	vec3 lightPos = Light::GetLightPosition();
	glUseProgram(shader);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glUniform1i(glGetUniformLocation(shader, "tex"), 3);
	mat4 worldMatrix = Mult(T(positionx,positiony,positionz),S(radius,radius,radius));
	glUniformMatrix4fv(glGetUniformLocation(shader, "viewMatrix"), 1, GL_TRUE, viewMatrix.m);
	glUniformMatrix4fv(glGetUniformLocation(shader, "worldMatrix"), 1, GL_TRUE, worldMatrix.m);
	glUniform3fv(glGetUniformLocation(shader, "cameraPosition"), 1, &cameraPos.x);
	glUniform3fv(glGetUniformLocation(shader, "lightPosition"), 1, &lightPos.x);
	glUniform3fv(glGetUniformLocation(shader, "objectColor"), 1, &color.x);
	DrawModel(m_Model, shader, "inPosition", "inNormal", "inTexCoord");
}

bool Sphere::collision(Sphere* other)
{
	// Calculate the sum of the radii, then square it
	float sumradiusSquared = getRadius() + other->getRadius();
	sumradiusSquared *= sumradiusSquared;

	double deltaXSquared = getX() - other->getX(); // calc. delta X
	deltaXSquared *= deltaXSquared; // square delta X
	double deltaYSquared = getY() - other->getY(); // calc. delta Y
	deltaYSquared *= deltaYSquared; // square delta Y
	double deltaZSquared = getZ() - other->getZ(); // calc. delta Y
	deltaZSquared *= deltaZSquared; // square delta Y
	if(deltaXSquared + deltaYSquared +deltaZSquared <= sumradiusSquared){
		return true;
	}
	return false;
}


float Sphere::SquaredDistPointAABB( float pn, float bmin, float bmax  )
{
        float out = 0;
        float v = pn;
        if ( v < bmin )
        {
            double val = (bmin - v);
            out += val * val;
        }

        if ( v > bmax )
        {
            double val = (v - bmax);
            out += val * val;
        }
        return out;
}

// True if the Sphere and AABB intersects
bool Sphere::collisionAABB(Cube* AABB)
{
	// Squared distance
    double squaredDistance = 0.0;
	vec3 BMax=AABB->getMaxBox();
	vec3 BMin=AABB->getMinBox();
    squaredDistance += SquaredDistPointAABB( positionx, BMin.x, BMax.x );
    squaredDistance += SquaredDistPointAABB( positiony, BMin.y, BMax.y );
    squaredDistance += SquaredDistPointAABB( positionz, BMin.z, BMax.z );
    // Intersection if the distance from center is larger than the radius
    // of the sphere.

    return squaredDistance <= (getRadius() *getRadius());
}

}
