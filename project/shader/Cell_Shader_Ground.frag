#version 150

in vec3 vertNormal;
in vec2 vertTexCoord;
in vec3 fragVert;

uniform sampler2D tex;
uniform mat4 projMatrix;
uniform mat4 mdlViewMatrix;
uniform vec3 cameraPosition;

out vec4 outColor;

void main(void)
{
	// setup
	vec2 null = vertTexCoord; 
	vec4 color = vec4(0.0, 0.0, 0.0, 1.0);
	vec3 fragPosition = vec3(mdlViewMatrix * vec4(fragVert, 1));

	// light calculation
	vec3 lightPosition = vec3(mdlViewMatrix * vec4(0, 2, 2, 1));
	vec3 lightVector = lightPosition - fragPosition;
	float intensity = dot(normalize(lightVector), normalize(vertNormal));
	if(intensity < 0)
		intensity = 0;

	if (intensity > 0.8)
		color = vec4(0.65,1.0,0.65,1.0);
	else if (intensity > 0.3)
		color = vec4(0.4,1.0,0.4,1.0);
	else
		color = vec4(0.2,0.4,0.2,1.0);

	// camera vector calculation
	vec3 cameraVector = cameraPosition - fragPosition;
	float outline = dot(normalize(cameraVector), normalize(vertNormal));
	if(outline < 0)
		outline = 0;

	//if ( outline < 0.35 )
	//	color = vec4(0.1, 0.1, 0.1, 1.0);
	
	outColor = color;
}