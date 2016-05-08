#version 150

in vec2 inTexCoord;
in vec3 inPosition;
in vec3 inNormal;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 worldMatrix;

out vec3 vertNormal;
out vec3 fragPosition;
out vec2 uv;

void main(void)
{
	vertNormal = inNormal;
	fragPosition = inPosition;
	uv = inTexCoord;
	gl_Position = projMatrix * viewMatrix * worldMatrix * vec4(inPosition, 1.0);
}