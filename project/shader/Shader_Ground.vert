#version 150

in vec3 inPosition;
in vec3 inNormal;
in vec2 inTexCoord;

uniform mat4 normalProjMatrix;
uniform mat4 depthProjMatrix;
uniform mat4 normalViewMatrix;
uniform mat4 depthViewMatrix;
uniform mat4 worldMatrix;

out vec2 uv;
out vec4 worldPos;
out vec4 depthPosition;

void main(void)
{
	float scale = 1000;
	float unused = inNormal.x;
	uv = vec2( inTexCoord.x * scale, inTexCoord.y * scale );
	gl_Position = normalProjMatrix * normalViewMatrix * worldMatrix * vec4(inPosition, 1.0);
	worldPos = worldMatrix * vec4(inPosition, 1.0);
	depthPosition = depthProjMatrix * depthViewMatrix * worldMatrix * vec4(inPosition, 1.0);
}
