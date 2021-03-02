#begin vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec2 v2f_texCoord;
out vec3 v2f_worldPos;
out vec3 v2f_normal;
out mat3 v2f_TBN;

uniform mat4 mat_VP;
uniform mat4 mat_model;
uniform mat4 mat_view;
uniform mat4 mat_projection;

void main()
{
    v2f_normal = mat3(transpose(inverse(mat_model))) * aNormal; // TODO: Move transpose calculation to CPU and pass via uniform
    v2f_normal = normalize(v2f_normal);
    v2f_texCoord = aTexCoord;
    v2f_worldPos = (mat_model * vec4(aPos, 1.0)).xyz;

    mat3 normalMatrix = transpose(inverse(mat3(mat_model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 B = normalize(normalMatrix * aBitangent);
    // re-orthogonalize T with respect to N
    //T = normalize(T - dot(T, N) * N);
    vec3 N = cross(T, B);

    v2f_TBN = mat3(T, B, N);

    gl_Position = mat_VP * vec4(v2f_worldPos, 1.0);
}
#end vertex

#begin fragment
#version 330 core

in vec2 v2f_texCoord;
in vec3 v2f_worldPos;
in vec3 v2f_normal;
in mat3 v2f_TBN;

out vec4 FragColor;

uniform bool useNormalMap;
uniform bool useGamma;
uniform vec3 cameraWorldPos;

uniform struct {
    sampler2D albedo;
    sampler2D normal;
    sampler2D metallic;
    sampler2D roughness;
    sampler2D ao;
} material;

struct PointLight {
    vec3 color;
    float power;
    vec3 position;
};

#define MAX_POINT_LIGHTS 32
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int nPointLights = 0;

const float PI = 3.14159265359;

void main()
{
    vec3 albedo = texture(material.albedo, v2f_texCoord).rgb;
    
    vec3 normal;
    if (useNormalMap) {
        normal = texture(material.normal, v2f_texCoord).rgb; // TODO: convert with tangent space matrix
        normal = normal * 2.0 - 1.0;
        normal = normalize(v2f_TBN * normal);
    } else {
        normal = normalize(v2f_normal);
    }
    
    
    
    vec3 metallic = texture(material.metallic, v2f_texCoord).rgb;
    vec3 roughness = texture(material.roughness, v2f_texCoord).rgb;
    vec3 ao = texture(material.ao, v2f_texCoord).rgb;

    //    vec3 normal = normalize(v2f_normal);
    vec3 viewDir = normalize(cameraWorldPos - v2f_worldPos);

    vec3 baseRefl = vec3(0.04);
    // baseRefl = mix(baseRefl, albedo, metallic); // TODO: Calculate 'metallic'
    
    vec3 diffuse;
    // reflectance equation
    vec3 reflectance = vec3(0.0);
    for(int i = 0; i < nPointLights; i++) 
    {
        // per-light radiance
        vec3 lightDir = normalize(pointLights[i].position - v2f_worldPos);
        vec3 halfway = normalize(lightDir + viewDir);
        float distToLight = length(pointLights[i].position - v2f_worldPos);
        float attenuation = 1.0 / (distToLight * distToLight);
        vec3 radiance = pointLights[i].color * pointLights[i].power * attenuation;
        
        float diff = max(dot(normal, lightDir), 0.0);

        diffuse += radiance * albedo * diff;
    }

    if(useGamma)
        diffuse = pow(diffuse, vec3(1.0 / 2.2));

    FragColor = vec4(diffuse, 1.0f);
} 
#end fragment