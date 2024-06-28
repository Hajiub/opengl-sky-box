#version 330 core

out vec4 fragColor;

uniform sampler2D grass;

in vec2 TexCoords; 


void main()
{
    fragColor = vec4(1.0f);
}
