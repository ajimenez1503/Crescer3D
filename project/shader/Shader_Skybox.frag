#version 150

in vec2 uv;
uniform sampler2D tex;
out vec4 outColor;

void main(void)
{
    float factor = 1.0;
    vec4 surface = texture(tex, uv);
    outColor = vec4(factor * surface.rgb, surface.a);
}