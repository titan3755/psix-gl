#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 vertexColor;
uniform float positionModifier;
void main() 
{
	gl_Position = vec4(aPos.x + positionModifier, aPos.y, aPos.z, 1.0);	
	vertexColor = vec3(positionModifier, aPos.x, aPos.y);
}
