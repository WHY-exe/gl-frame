#version 330 core
out vec4 FragColor;
in vec3 pointColor;
in vec4 posOut;
in vec2 texCoord;

uniform sampler2D texture1;
void main()
{
	FragColor = texture(texture1, texCoord) * vec4(pointColor, 1.0f);
}

