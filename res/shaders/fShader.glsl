#version 330 core

in vec3 normals;
in vec2 TexCord;

out vec4 fColor;

uniform vec3 color;

uniform sampler2D tex;

void main()
{

	//color with texture
	vec4 texColor = texture(tex, TexCord);
	fColor= texColor * vec4(color, 1.0);
}