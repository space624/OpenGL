#version 330 core
out vec4 FragColor;

uniform float time;
uniform vec3 uColor;

in vec3 color;
in vec3 position;

void main()
{
   //float intensity = (sin(time)+1.0)/2.0;
   //FragColor = vec4(vec3(intensity) + color, 1.0f);
   FragColor = vec4(color, 1.0f);
   //FragColor = vec4(color, 1.0f);
   //FragColor = vec4(position, 1.0f);

}