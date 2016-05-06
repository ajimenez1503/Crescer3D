#version 150

in vec3 inPosition;
in vec3 inNormal;

uniform mat4 projMatrix;
uniform mat4 mdlViewMatrix;

out vec3 vertNormal;
out vec3 fragPosition;

void main(void)
{
	vertNormal = inNormal;
	fragPosition = inPosition;
	gl_Position = projMatrix * mdlViewMatrix * vec4(inPosition, 1.0);
}