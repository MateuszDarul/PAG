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

uniform bool mark;

uniform vec3 viewPos;

uniform bool directional_light_enable;
uniform Light directional_light;
uniform Material directional_material;

uniform bool point_light_enable;
uniform Light point_light;
uniform Material point_material;

uniform bool spot_1_light_enable;
uniform Light light_1;
uniform Material material_1;

uniform bool spot_2_light_enable;
uniform Light light_2;
uniform Material material_2;

void main()
{
    vec3 color = texture(texture_data, fs_in.TexCoords).rgb;
    vec3 ambient = 0.1 * color;
    vec3 normal = normalize(fs_in.Normal);
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);

    vec3 dir_light = vec3(0);
    if(directional_light_enable)
    {
        vec3 lightDir = normalize(-directional_light.direction);
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = directional_light.diffuse * diff * texture(directional_material.diffuse, fs_in.TexCoords).rgb;

        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), directional_material.shininess);
        vec3 specular = directional_light.specular * spec * texture(directional_material.specular, fs_in.TexCoords).rgb;

        dir_light = ambient + diffuse + specular;
    }


    vec3 poi_light = vec3(0);
    if(point_light_enable)
    {
        vec3 lightDir = normalize(point_light.position - fs_in.FragPos);
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = point_light.diffuse * diff * texture(point_material.diffuse, fs_in.TexCoords).rgb;

        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), point_material.shininess);
        vec3 specular = point_light.specular * spec * texture(point_material.specular, fs_in.TexCoords).rgb;

        float distance = length(point_light.position - fs_in.FragPos);
        float attenuation = 1.0 / (point_light.constant + point_light.linear * distance + point_light.quadratic * (distance * distance));

        poi_light = ambient*attenuation + diffuse*attenuation + specular*attenuation;
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
