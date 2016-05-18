#ifndef _SPHERE_H
#define _SPHERE_H

#if defined (__LINUX__) || (__CENTOS__)
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
#include "../../common/LoadTGA.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
//#include "Game.h"
#include "Cube.h"
#include "Light.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
namespace Crescer3D
{

class Sphere {
	
	private:
		float positionx,positiony,positionz;
		GLuint m_Shader;
		static Model *m_Model;
		vec3 color;
		int id;
		float velocity;
		float m_way_went;
		float m_total_way_went;
		float radius;//the radious can be incrmeent and decrement. By deafult it is 1.
		float SquaredDistPointAABB( float pn, float bmin, float bmax);
		bool m_is_init;
		int m_weight;
		
		

	public:
		Sphere();
		static GLuint m_Texture;
		void init(int x, GLuint shader);
		void draw(mat4 total, vec3 cameraPos, GLuint shader = 666);

		void moveForward ();
		void moveBack () ;
		void moveLeft ();
		void moveRight ();
		void moveAngle(float angle);

		void incrementRadius();
		void decrementRadius();
		void setRadius(float in_radius);
		float getRadius();
		void setVelocity(float in_velocity);
		float getVelocity();

		void setPositionX(float x);
		void setPositionY(float y);
		void setPositionZ(float z);
		void setPosition(float x, float y,float z);
		void setRndPosition(int x_max,int x_min,int ymax,int ymin);
		float getX();
		float getY();
		float getZ();
		vec3 getPosition();
		
		float getWayWent();
		void increaseWayWent();
		void setWayWent(float way_went);

		int getWeight();
		void setWeight(int weight);
		void eat(int weight_eaten);

		int getID();
		bool isInit();
		bool collision(Sphere* other);
		bool collisionAABB(Cube* AABB);
};

}
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

#endif // _SPHERE_H
