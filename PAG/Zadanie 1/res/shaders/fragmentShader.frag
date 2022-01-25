#version 330 core
out vec4 FragColor;
  
//in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec4 myColor; 

void main()
{
    FragColor = myColor;
	//FragColor = texture(ourTexture, TexCoord) * myColor;  
}