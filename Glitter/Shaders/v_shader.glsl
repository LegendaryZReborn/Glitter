#version 430

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 textureCoords;
layout(location = 2) in vec4 normal;

uniform mat4 model_view;
uniform mat4 perspective;

out vec2 texCoords;
out vec4 color;

void main(){
    color = vec4(vPosition.x + 0.5, 20, vPosition.y + 0.5, 1.0);
    gl_Position = perspective * model_view * vPosition;
    texCoords = textureCoords;
}
