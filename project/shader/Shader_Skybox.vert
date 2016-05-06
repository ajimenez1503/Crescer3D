#version 150

in vec3 inPosition;
in vec2 inTexCoord;
uniform mat4 projMatrix;
uniform mat4 mdlViewMatrix;
out vec2 uv;

void main(void)
{
	uv = vec2(inTexCoord.x, inTexCoord.y);
	gl_Position = projMatrix * mdlViewMatrix * vec4(inPosition, 1.0);
}