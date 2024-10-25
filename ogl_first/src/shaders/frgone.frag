#version 330 core
in vec3 vertexColor;
out vec4 FragColor;
uniform vec3 ofstclr;

void main()
{
	FragColor = vec4(vertexColor + ofstclr, 1.0);
}