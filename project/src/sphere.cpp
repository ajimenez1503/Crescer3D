#include "sphere.h"

void Sphere::moveForward () {
	positionz-=velocity;
}
void Sphere::moveBack(){
	positionz+=velocity;
}
void Sphere::moveLeft(){
	positionx-=velocity;
}
void Sphere::moveRight () {
	positionx+=velocity;
}
float Sphere::getRadius(){
	 return radius;
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

void Sphere::incrementRadius(){ 
	radius+=0.5;
}
void Sphere::decrementRadius(){ 
	radius-=0.5;
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

Sphere::Sphere(){
	positionx=0.0f;
	positiony=1.0f;
	positionz=0.0f;
	velocity = 0.5;
	radius=1.0;
}

void Sphere::init(int x){
	id=x;
	LoadTGATextureSimple("model/sphere/conc.tga", &tex1);
	model=LoadModelPlus("model/sphere/groundsphere.obj");
	//position=SetVector(0.0f, 1.0f, 0.0f);
}


void Sphere::draw(mat4 total,GLuint program){
	mat4 mdlMatrix;
	glUseProgram(program);
	mdlMatrix=Mult(total,Mult(T(positionx,positiony,positionz),S(radius,radius,radius)));
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, mdlMatrix.m);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex1);		// Bind Our Texture tex1
	glUniform1i(glGetUniformLocation(program, "tex"), 1); // Texture unit 0
	// draw ground	
	DrawModel(model, program, "inPosition", "inNormal", "inTexCoord");
}
void Sphere::setPosition(float x, float y,float z){
	setPositionX(x);
	setPositionY(y);
	setPositionZ(z);
}
bool Sphere::collision(Sphere other){
	// Calculate the sum of the radii, then square it
	float sumradiusSquared = getRadius() + other.getRadius();
	sumradiusSquared *= sumradiusSquared;

	double deltaXSquared = getX() - other.getX(); // calc. delta X
	deltaXSquared *= deltaXSquared; // square delta X
	double deltaYSquared = getY() - other.getY(); // calc. delta Y
	deltaYSquared *= deltaYSquared; // square delta Y
	double deltaZSquared = getZ() - other.getZ(); // calc. delta Y
	deltaZSquared *= deltaZSquared; // square delta Y
	if(deltaXSquared + deltaYSquared +deltaZSquared <= sumradiusSquared){
		return true;
	}
	return false;
}
