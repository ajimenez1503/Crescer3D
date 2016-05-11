#version 150

in vec2 uv;
in vec4 worldPos;
in vec4 depthPosition;
uniform vec3 worldMin;
uniform vec3 worldMax;
uniform sampler2D tex;
uniform sampler2D depthTex;
out vec4 outColor;

void main(void)
{
	vec4 textureColor = texture(tex, uv);
	vec3 projPosition = depthPosition.xyz / depthPosition.w;
	projPosition = projPosition * 0.5 + 0.5;
	float closestDepth = texture(depthTex, projPosition.xy).r; 	
	if(closestDepth < 1.0)
		textureColor = textureColor * 0.35;
	else if(worldPos.x < (worldMin.x-1) || worldPos.x > (worldMax.x+1)
			|| worldPos.z < (worldMin.z-1) || worldPos.z > (worldMax.z+1))
		textureColor = textureColor * 0.35;
	outColor = textureColor;
}
