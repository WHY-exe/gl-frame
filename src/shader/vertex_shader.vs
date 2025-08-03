#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 aTexCoord;

out vec3 pointColor;
out vec4 posOut;
out vec2 texCoord;
uniform float xOffset;
void main()
{
	gl_Position = vec4(aPos.x + xOffset, aPos.yz, 1.0f);
	posOut		= vec4(aPos, 1.0);
	pointColor 	= aColor;
	texCoord 	= aTexCoord;
}

