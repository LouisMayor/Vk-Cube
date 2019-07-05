#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UTranformData
{
    mat4 MVP;
	mat4 World;
} TranformData;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColour;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColour;
layout(location = 1) out vec2 fragTexCoord;

void main() 
{
    gl_Position = TranformData.MVP * vec4(inPosition, 1.0);
    fragColour = vec3(inColour);
	fragTexCoord = inTexCoord;
}