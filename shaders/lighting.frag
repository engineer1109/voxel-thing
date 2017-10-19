#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;

uniform vec3 viewPos;
uniform vec3 lightPos;

uniform sampler2D texture1;

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;

void main() {
    float ambientStrength = 0.1;
    float specularStrength = 0.5;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diffAmount = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * diffAmount;

    vec3 ambient = ambientStrength * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float specularAmount = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * specularAmount * lightColor;

    vec3 color = texture(texture1, TexCoord).xyz;

	FragColor = vec4(color * (ambient + diffuse + specular) , 1.0);
}
