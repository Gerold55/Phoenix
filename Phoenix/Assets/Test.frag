#version 330 core

in vec2 pass_UV;

uniform sampler2D u_Tex;

out vec4 out_FragColor;

void main()
{
	out_FragColor = texture(u_Tex, vec2(pass_UV.x, 1.f - pass_UV.y));
}
