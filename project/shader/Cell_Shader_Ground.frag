#version 150

in vec3 vertNormal;
in vec2 vertTexCoord;
in vec3 vertCamera;

uniform sampler2D tex;
uniform vec3 lightDirection;

out vec4 outColor;

void main(void)
{
	vec2 null = vertTexCoord; // disable warning
	vec4 color;
	float intensity = dot(normalize(lightDirection), normalize(vertNormal));

	if (intensity > 0.95)
		color = vec4(0.5,1.0,0.5,1.0);
	else if (intensity > 0.5)
		color = vec4(0.3,0.6,0.3,1.0);
	else if (intensity > 0.25)
		color = vec4(0.2,0.4,0.2,1.0);
	else
		color = vec4(0.1,0.2,0.1,1.0);

	outColor = color;
}