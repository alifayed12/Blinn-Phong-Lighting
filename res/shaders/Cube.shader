#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoords;

uniform mat4 u_MVP;
uniform mat4 u_Model;

out vec2 v_TexCoords;
out vec3 v_Normals;
out vec3 v_FragPos;

void main()
{
	/* put the vertex position in clip space for the clipping stage */
	gl_Position = u_MVP * position;

	/* send fragment position to the fragment shader. This gets linearly interpolated */
	v_FragPos = vec3(u_Model * position);

	/* send texture coordinates to the fragment shader. This gets linearly interpolated */
	v_TexCoords = texCoords;

	/*
	* send normals to fragment shader. Need to transpose and inverse to make sure normals are in the correct places
	* when switching between coordinate systems (also after non uniform scaling)
	*/
	v_Normals = mat3(transpose(inverse(u_Model))) * normals; 
}

#shader fragment
#version 330 core

out vec4 color; // output to the framebuffer

in vec2 v_TexCoords;
in vec3 v_FragPos;
in vec3 v_Normals;

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform sampler2D u_PlankDiffuse;
uniform sampler2D u_PlankSpecular;

uniform Light light;
uniform vec3 currentPos;

vec3 computeAmbient();
vec3 computeDiffuse();
vec3 computeSpecular();

void main()
{
	vec3 computedLight = computeAmbient() + computeDiffuse() + computeSpecular();
	color = vec4(computedLight, 1.0f);
}

vec3 computeAmbient()
{
	return light.ambient * texture(u_PlankDiffuse, v_TexCoords).xyz;
}

vec3 computeDiffuse()
{
	vec3 normal = normalize(v_Normals);
	vec3 lightDirection = normalize(light.position - v_FragPos);
	float diffuse = max(dot(normal, lightDirection), 0);
	
	return light.diffuse * diffuse * texture(u_PlankDiffuse, v_TexCoords).xyz;
}

vec3 computeSpecular()
{
	vec3 lightDirection = normalize(light.position - v_FragPos);
	vec3 viewDirection = normalize(currentPos - v_FragPos);
	vec3 reflectDirection = reflect(-lightDirection, normalize(v_Normals));
	float specular = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);

	return light.specular * specular * texture(u_PlankSpecular, v_TexCoords).xyz;
}