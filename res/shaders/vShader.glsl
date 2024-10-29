#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCord;

out vec3 normal;
out vec2 TexCord;

uniform vec3 offset;
void main()
{ 
	gl_Position=vec4(aPos + offset,1.0f);
	normal=aNorm;
	TexCord=aTexCord;
}