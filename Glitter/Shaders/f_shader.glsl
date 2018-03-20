#version 430

in vec4 color;
in vec2 texCoords;

out vec4 f_color;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;
uniform int hasTexture;
uniform sampler2D tex0;

layout(location = 1) uniform float time;

void main(){
   vec4 nColor = vec4(color.x + sin(time), color.y + cos(time), color.z + sin(time) + cos(time), 1.0);
   vec4 matColor = vec4(material.ambient + material.diffuse + material.specular, 1.0);

   if(hasTexture > 0)
     f_color = texture(tex0, texCoords) * matColor;
   else
     f_color = nColor;

}
