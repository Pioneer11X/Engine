#version 330 core
in vec3 ourColour;

out vec4 color;

void main()
{
	color = vec4(ourColour, 1.0f);
    // color = vec4(1.0f, 0.0f, 0.2f, 1.0f);
}
