#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 bColor;

void main() {
   gl_Position = projection * view * model * vec4(aPos, 1.0f);
   bColor = aColor;
}

#shader fragment
#version 330 core

in vec3 bColor;
out vec4 FragColor;

void main() {
   FragColor = vec4(bColor, 1.0f);
}