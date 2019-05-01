"// Generates an irradiance cube from an environment map using convolution\n"
"\n"
"#ifndef NUM_PHI_SAMPLES\n"
"#   define NUM_PHI_SAMPLES 64.0\n"
"#endif\n"
"\n"
"#ifndef NUM_THETA_SAMPLES\n"
"#   define NUM_PHI_SAMPLES 32.0\n"
"#endif\n"
"\n"
"TextureCube  g_EnvironmentMap;\n"
"SamplerState g_EnvironmentMap_sampler;\n"
"\n"
"void main(in float4 Pos      : SV_Position,\n"
"          in float3 WorldPos : WORLD_POS,\n"
"          out float4 Color   : SV_Target)\n"
"{\n"
"	float3 N     = normalize(WorldPos);\n"
"	float3 up    = float3(0.0, 1.0, 0.0);\n"
"	float3 right = normalize(cross(up, N));\n"
"	up = cross(N, right);\n"
"\n"
"    const float PI         = 3.14159265;\n"
"	const float TWO_PI     = PI * 2.0;\n"
"	const float HALF_PI    = PI * 0.5;\n"
"	const float deltaPhi   = TWO_PI  / NUM_PHI_SAMPLES;\n"
"	const float deltaTheta = HALF_PI / NUM_THETA_SAMPLES;\n"
"\n"
"	float3 color = float3(0.0, 0.0, 0.0);\n"
"	float sampleCount = 0;\n"
"	for (float phi = 0.0; phi < TWO_PI; phi += deltaPhi)\n"
"    {\n"
"		for (float theta = 0.0; theta < HALF_PI; theta += deltaTheta)\n"
"        {\n"
"			float3 tempVec = cos(phi) * right + sin(phi) * up;\n"
"			float3 sampleDir = cos(theta) * N + sin(theta) * tempVec;\n"
"			color += g_EnvironmentMap.Sample(g_EnvironmentMap_sampler, sampleDir).rgb * cos(theta) * sin(theta);\n"
"			sampleCount++;\n"
"		}\n"
"	}\n"
"	Color = float4(PI * color / sampleCount, 1.0);\n"
"}\n"