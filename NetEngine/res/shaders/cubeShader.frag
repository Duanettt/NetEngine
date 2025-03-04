#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;


uniform sampler2D texture1;
uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

// Material for normal colours
struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

// Material for textures 
struct TextureMaterial
{
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

uniform TextureMaterial tm;

uniform Material material;

struct Light 
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

void main()
{    
    // ambient
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient  = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * diff * vec3(texture(tm.diffuse, TexCoords));  
    vec3 specular = light.specular * (spec * material.specular);
    
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}