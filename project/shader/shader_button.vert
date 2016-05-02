#version 150

in vec3 inPosition;
in vec2 inTexCoord;

// NY
uniform mat4 projMatrix;
uniform mat4 mdlViewMatrix;


void main(void)
{
	gl_Position = projMatrix * mdlViewMatrix * vec4(inPosition, 1.0);
}
