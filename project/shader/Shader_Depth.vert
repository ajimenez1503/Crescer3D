#version 150

in vec3 vertexPosition;
in vec3 inNormal;
in vec3 inPosition;
in vec2 inTexCoord;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 worldMatrix;

void main()
{
	float unused1 = inNormal.x;
	float unused2 = inTexCoord.x;
	gl_Position =  projMatrix * viewMatrix * worldMatrix * vec4(inPosition, 1);
}