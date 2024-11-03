#version 330 core
out vec4 FragColor;

uniform sampler2D sampler;

uniform sampler2D grassSampler;
uniform sampler2D landSampler;
uniform sampler2D noiseSampler;

uniform float time;
uniform vec3 uColor;

in vec3 color;
in vec3 position;
in vec2 uv;

void main()
{
   //float intensity = (sin(time)+1.0)/2.0;
   //FragColor = vec4(vec3(intensity) + color, 1.0f);
   //FragColor = vec4(color, 1.0f);
   //FragColor = texture(sampler,uv);


   vec4 grassColor = texture(grassSampler,uv);
   vec4 landColor = texture(landSampler,uv);
   vec4 noiseColor = texture(noiseSampler,uv);

   float weight = noiseColor.r;

   //vec4 finalColor = grassColor*(1.0-weight) + landColor*weight;
   //ø… π”√
   vec4 finalColor = mix(grassColor,landColor,weight);

   FragColor = vec4(finalColor.rgb,1.0);

   //FragColor = vec4(color, 1.0f);
   //FragColor = vec4(position, 1.0f);

}