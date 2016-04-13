#version 150

in  vec3 inPosition;
in  vec3 inNormal;
in vec2 inTexCoord;
out vec2 texCoord;

// NY
uniform mat4 projMatrix;
uniform mat4 mdlMatrix;

out vec3 exSurface; // Phong (specular)
out vec3 exNormal; // Phong

void main(void)
{
	texCoord = inTexCoord;
	exNormal = mat3(mdlMatrix)* inNormal;
	exSurface = vec3(mdlMatrix* vec4(inPosition, 1.0)); // Don't include projection here - we only want to 	go to view coordinates
	
	gl_Position = projMatrix * mdlMatrix * vec4(inPosition, 1.0);
}
