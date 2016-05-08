#version 150

in vec3 vertNormal;
in vec3 fragPosition;
in vec2 uv;

uniform sampler2D tex;
uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 worldMatrix;
uniform vec3 cameraPosition;
uniform vec3 objectColor;
uniform vec3 lightPosition;

out vec4 outColor;

void main(void)
{
	mat4 modelToView = viewMatrix * worldMatrix;
	vec4 tc = texture(tex, uv);
	vec4 color = vec4(objectColor, 1.0);
	vec4 black = vec4(0.1, 0.1, 0.1, 1.0);
	vec3 fragPos = vec3(modelToView * vec4(fragPosition, 1.0));
	vec3 lightPos = vec3(viewMatrix * vec4(lightPosition, 1.0));
	vec3 camPos = vec3(viewMatrix * vec4(cameraPosition, 1.0));
	vec3 normalVector = normalize(mat3(modelToView) * vertNormal);
	vec3 cameraVector = normalize(camPos - fragPos);

	vec3 lightVector = normalize(lightPos - fragPos);
	float intensity = dot(lightVector, normalVector);
	if(intensity < 0)
		intensity = 0;

	if (intensity < 0.95 && intensity > 0.94)
		color = black;
	if (intensity < 0.94 && intensity > 0.74)
		color = vec4(objectColor.rgb * 0.65, 1.0);
	if (intensity < 0.74 && intensity > 0.71)
		color = black;
	if (intensity < 0.71)
		color = vec4(objectColor.rgb * 0.35, 1.0);

	
	float outline = dot(cameraVector, normalVector);
	if(outline < 0)
		outline = 0;

	if ( outline < 0.2 )
		color = black;

	outColor = color;
}
