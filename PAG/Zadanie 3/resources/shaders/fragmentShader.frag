#version 450 core

out vec4 FragColor;

in VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform sampler2D texture_data;

uniform bool point_light_enable;
uniform vec3 point_lightPos;
uniform vec3 point_lightCol;
uniform float point_lightSku;
uniform float point_lightWli;
uniform float point_lightWkw;

uniform bool directional_light_enable;
uniform vec3 direction_lightDir;
uniform vec3 direction_lightCol;

uniform bool mark;

uniform vec3 viewPos;

uniform bool spot_1_light_enable;
uniform Light light_1;
uniform Material material_1;

uniform bool spot_2_light_enable;
uniform Light light_2;
uniform Material material_2;

void main()
{
    vec3 color = texture(texture_data, fs_in.TexCoords).rgb;
    vec3 ambient = 0 * color;
    vec3 normal = normalize(fs_in.Normal);
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);

    vec3 dir_light = vec3(0);
    if(directional_light_enable)
    {
        vec3 direction_lightDir = normalize(-direction_lightDir);
        float direction_diff = max(dot(normal, direction_lightDir), 0.0);
        vec3 direction_diffsue = 0.5 * direction_diff * color;

        vec3 direction_reflectDir = reflect(-direction_lightDir, normal);
        float direction_spec = pow(max(dot(viewDir, direction_reflectDir), 0.0), 1.0);
        vec3 direction_specular = direction_lightCol * direction_spec * color;

        dir_light = ambient + direction_diffsue + direction_specular;
    }


    vec3 poi_light = vec3(0);
    if(point_light_enable)
    {
        vec3 point_lightDir = normalize(point_lightPos - fs_in.FragPos);
        float point_diff = max(dot(point_lightDir, normal), 0.0);
        vec3 point_diffuse = point_diff * point_lightCol * color;

        vec3 point_reflectDir = reflect(-point_lightDir, normal);
        float point_spec = 0.0;

        vec3 point_halfwayDir = normalize(point_lightDir + viewDir);
        point_spec = pow(max(dot(normal, point_halfwayDir), 0.0), point_lightSku);
        vec3 point_specular = point_lightCol * point_spec;

        float distance = length(point_lightPos - fs_in.FragPos);
        float attenuation = 1.0 / (1 + point_lightWli * distance + point_lightWkw * (distance * distance));

        poi_light = ambient*attenuation + point_diffuse*attenuation + point_specular*attenuation;
    }


    vec3 spot_light_1 = vec3(0);
    if(spot_1_light_enable)
    {
        vec3 lightDir = normalize(light_1.position - fs_in.FragPos);
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = light_1.diffuse * diff * texture(material_1.diffuse, fs_in.TexCoords).rgb;

        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material_1.shininess);
        vec3 specular = light_1.specular * spec * texture(material_1.specular, fs_in.TexCoords).rgb;

        float theta = dot(lightDir, normalize(-light_1.direction));
        float epsilon = (light_1.cutOff - light_1.outerCutOff);
        float intensity = clamp((theta - light_1.outerCutOff) / epsilon, 0.0, 1.0);
        diffuse  *= intensity;
        specular *= intensity;

        float distance = length(light_1.position - fs_in.FragPos);
        float attenuation = 1.0 / (light_1.constant + light_1.linear * distance + light_1.quadratic * (distance * distance));

        spot_light_1 = ambient*attenuation + diffuse*attenuation + specular*attenuation;
    }

    vec3 spot_light_2 = vec3(0);
    if(spot_2_light_enable)
    {
        vec3 lightDir = normalize(light_2.position - fs_in.FragPos);
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = light_2.diffuse * diff * texture(material_2.diffuse, fs_in.TexCoords).rgb;

        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material_2.shininess);
        vec3 specular = light_2.specular * spec * texture(material_2.specular, fs_in.TexCoords).rgb;

        float theta = dot(lightDir, normalize(-light_2.direction));
        float epsilon = (light_2.cutOff - light_2.outerCutOff);
        float intensity = clamp((theta - light_2.outerCutOff) / epsilon, 0.0, 1.0);
        diffuse  *= intensity;
        specular *= intensity;

        float distance = length(light_2.position - fs_in.FragPos);
        float attenuation = 1.0 / (light_2.constant + light_2.linear * distance + light_2.quadratic * (distance * distance));

        spot_light_2 = ambient*attenuation + diffuse*attenuation + specular*attenuation;
    }

    vec3 result = dir_light + poi_light + spot_light_1 + spot_light_2;

    if(mark)
    {
        result = vec3(1,1,1);
    }

    FragColor = vec4(result, 1.f);
}
