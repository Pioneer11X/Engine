#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

uniform mat4 transform;
uniform mat4 view; // For the Camera
uniform mat4 projection;

uniform vec3 lightPos1;

out vec3 ourColour;

void main()
{
    gl_Position = projection * view * transform * vec4(position, 1.0f);
	
	vec3 objectColour = vec3(0.9f, 0.2f, 0.2f);
	float ambientStrength = 0.2;

	vec3 norm = normalize(normal);
	vec3 FragPos = vec3(transform * vec4(position, 1.0f));
	vec3 lightDir = normalize(lightPos1 - FragPos);

	float diff = dot(norm, lightDir);
	// float diff = 0.2;

	ourColour = (ambientStrength + diff) * objectColour;
    
}
