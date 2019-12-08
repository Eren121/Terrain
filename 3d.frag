#version 400

in vec3 position;
out vec4 color;

void main()
{
	color = vec4(position.yyy / 700.4, 1.0);
}
