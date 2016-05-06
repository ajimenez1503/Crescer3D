#version 150

in vec3 vertexPosition;
in vec3 inNormal;
in vec3 inPosition;

uniform mat4 projMatrix;
uniform mat4 mdlViewMatrix;

void main()
{
	float unused = inNormal.x;
	gl_Position =  projMatrix * mdlViewMatrix * vec4(inPosition, 1);
}