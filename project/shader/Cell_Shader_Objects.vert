#version 150

in vec3 inPosition;
in vec3 inNormal;
in vec2 inTexCoord;
in vec3 inCamera;

uniform mat4 projMatrix;
uniform mat4 mdlViewMatrix;

out vec3 vertNormal;
out vec2 vertTexCoord;
out vec3 vertCamera;

void main(void)
{
	vertCamera = inCamera;
	vertTexCoord = inTexCoord;
	vertNormal = mat3(mdlViewMatrix)* inNormal;
	gl_Position = projMatrix * mdlViewMatrix * vec4(inPosition, 1.0);
}