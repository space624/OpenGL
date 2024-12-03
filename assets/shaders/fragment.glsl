#version 330 core
out vec4 FragColor;

uniform sampler2D sampler;

uniform sampler2D grassSampler;
uniform sampler2D landSampler;
uniform sampler2D noiseSampler;

uniform float width;
uniform float height;

uniform float time;
uniform vec3 uColor;

in vec3 color;
in vec3 position;
in vec2 uv;

void main()
{
    /*{
       //float intensity = (sin(time)+1.0)/2.0;
       //FragColor = vec4(vec3(intensity) + color, 1.0f);
       //FragColor = vec4(color, 1.0f);
       //FragColor = texture(sampler,uv);


       vec4 grassColor = texture(grassSampler,uv);
       vec4 landColor = texture(landSampler,uv);
       vec4 noiseColor = texture(noiseSampler,uv);

       float weight = noiseColor.r;

       //vec4 finalColor = grassColor*(1.0-weight) + landColor*weight;
       //可使用
       vec4 finalColor = mix(grassColor,landColor,weight);

       FragColor = vec4(finalColor.rgb,1.0);

       //FragColor = vec4(color, 1.0f);
       //FragColor = vec4(position, 1.0f);
   }*/
   //获取当前像素对应的纹理上的文素具体位置
   vec2 location = uv * vec2(width,height);

   //计算当前像素对应文素具体位置在xy方向上的变化量
   vec2 dx = dFdx(location);
   vec2 dy = dFdy(location);

   //选择最大的delta,求log2(delta)
   float maxDelta = sqrt(max(dot(dx,dx) , dot(dy,dy)));
   float L = log2(maxDelta);

   //计算出mipmap的采样级别
   int level = max(int(L+0.5) , 0);
   FragColor = textureLod(sampler,uv,level);
}