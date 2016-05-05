#version 150

in vec2 uv;
uniform sampler2D tex;
out vec4 outColor;

void main(void)
{
	vec4 textureColor = texture(tex, uv);
	outColor = clamp(textureColor, 0, 0.75);
}
