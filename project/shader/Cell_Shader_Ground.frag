#version 150

in vec3 exNormal; // Phong
in vec3 exSurface; // Phong (specular)

out vec4 outColor;
in vec2 texCoord;
uniform sampler2D tex;

void main(void)
{

	float diffuse, specular, shade;
	const vec3 light = vec3(0.58, 0.58, 0.58);


	// Diffuse
	diffuse = dot(normalize(exNormal), light);
	diffuse = max(0.0, diffuse); // No negative light

	// Specular
	vec3 r = reflect(-light, normalize(exNormal));
	vec3 v = normalize(-exSurface); // View direction
	specular = dot(r, v);
	if (specular > 0.0)
		specular = 1.0 * pow(specular, 150.0);
	specular = max(specular, 0.0);
	shade = 0.7*diffuse + 1.0*specular;
	vec4 outColorLight= vec4(shade, shade, shade, 1.0);

	vec4 outColorTexture = texture(tex, texCoord);

	outColor=outColorTexture;
}
