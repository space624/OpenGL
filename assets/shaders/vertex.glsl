#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;

uniform float time;
uniform float speed;

out vec3 color;
out vec3 position;
out vec2 uv;

uniform mat4 transform;

//aPos作为attribute 传入shader 原则上是不允许更改的


void main()
{
    /*{
       float dx = 0.3;
       float offsetX = sin(time*speed)*dx;
       gl_Position = vec4(aPos.x + offsetX, aPos.y, aPos.z, 1.0);
       color = aColor * ((cos(time) + 1.0) / 2.0);
       //color = aColor;
       position = aPos;
       float deltaU = time * 3;
       uv = vec2(aUV.x+deltaU,aUV.y);
       //uv = aUV+time;
   }*/

   /*
   {
       float scale = 1.0 / time;
       vec3 sPos = aPos * scale;
       gl_Position = vec4(sPos,1.0);
       color = aColor;
       uv = aUV;
   }
   */
   vec4 position = vec4(aPos , 1.0);
   position = transform * position;
   gl_Position = position;
   color = aColor;
   uv = aUV;
}