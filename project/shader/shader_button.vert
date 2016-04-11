#version 150

in  vec3 inPosition;

// NY
uniform mat4 projMatrix;
uniform mat4 mdlMatrix;


void main(void)
{
	gl_Position = projMatrix * mdlMatrix * vec4(inPosition, 1.0);
}
