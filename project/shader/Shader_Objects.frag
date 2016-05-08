#version 150

in vec3 vertNormal;
in vec3 fragPosition;

uniform sampler2D tex;
uniform mat4 projMatrix;
uniform mat4 mdlViewMatrix;
uniform vec3 cameraPosition;
uniform vec3 lightDirection;
uniform vec3 objectColor;

out vec4 outColor;

void main(void)
{
	vec4 color = vec4(0.0, 0.0, 0.0, 1.0);
	vec3 thisPosition = vec3(mdlViewMatrix * vec4(fragPosition, 1));
	vec3 camPosition = vec3(mdlViewMatrix * vec4(cameraPosition, 1));
	vec3 thisNormal = normalize(mat3(mdlViewMatrix) * vertNormal);

	// light calculation
	vec3 lightVector = normalize(mat3(mdlViewMatrix) * lightDirection);
	float intensity = dot(lightVector, thisNormal);
	if(intensity < 0)
		intensity = 0;

	if (intensity > 0.95)
		color = vec4(objectColor, 1.0);
	else if (intensity > 0.6)
		color = vec4(objectColor * 0.65, 1.0);
	else if (intensity > 0.35)
		color = vec4(objectColor * 0.35, 1.0);
	else
		color = vec4(objectColor * 0.2, 1.0);

	// camera vector calculation
	vec3 cameraVector = normalize(camPosition - thisPosition);
	float outline = dot(cameraVector, thisNormal);
	if(outline < 0)
		outline = 0;

	//if ( outline < 0.5 )
	//	color = vec4(0.1, 0.1, 0.1, 1.0);
	
	outColor = color;
}
