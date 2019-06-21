#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UTranformData
{
    mat4 MVP;
} TranformData;

layout(push_constant) uniform UTimeData 
{
    float Time;
} TimeData;

layout(location = 0) out vec4 outColor;
layout(location = 0) in vec3 fragColour;

void main()
{
	//vec2 uv = gl_FragCoord.xy / vec2(1280.0f, 720.0f);
	//vec3 col = 0.5 + 0.5 * cos(TimeData.Time + uv.xyx + vec3(0,2,4));	

	vec3 col = vec3(1, 0, 0) * vec3(sin(TimeData.Time));
    outColor = vec4(col, 1.0);
}