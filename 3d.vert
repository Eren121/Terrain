#version 400

in vec3 pos;
out vec3 position;

uniform mat4 modelview;

void main()
{
	gl_Position = modelview * vec4(pos * vec3(1, 0.1, 1), 1.0);
	position = pos;
}
