#version 440 core

struct Light {
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
};

struct DirectionalLight {
    Light base;
    vec3 direction;
};

struct PointLight {
    Light base;
    vec3 position;
    float constant;
    float linear;
    float exponent;
};

struct Material {
    float specularIntensity;
    float shininess;
};

const int MAX_POINT_LIGHTS = 3;

uniform vec2 windowSize;

uniform int usingTexture;
uniform sampler2D textureSampler;
uniform vec4 baseColor;

uniform vec3 eyePosition;

uniform int pointLightCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform Material material;

in vec2 uvsFragmentShader;
in vec3 normalsFragmentShader;
in vec3 fragmentPosition;

out vec4 fragColor;

vec4 CalculateLightByDirection(Light light, vec3 direction) {
    vec4 ambientColor = vec4(light.color, 1.f) * light.ambientIntensity;

    float diffuseFactor = max(dot(normalize(normalsFragmentShader), normalize(direction)), 0.f);
    vec4 diffuseColor = vec4(light.color * light.diffuseIntensity * diffuseFactor, 1.0f);

    vec4 specularColor = vec4(0, 0, 0, 0);

    if (diffuseFactor > 0.f)
    {
        vec3 fragToEye = normalize(eyePosition - fragmentPosition);
        vec3 reflectedVertex = normalize(reflect(direction, normalize(normalsFragmentShader)));
    
        float specularFactor = dot(fragToEye, reflectedVertex);

        if (specularFactor > 0.f)
        {
            specularFactor = pow(specularFactor, material.shininess);
            specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0);
        }
    }
    
    return ambientColor + diffuseColor + specularColor;
}

vec4 CalculateDirectionalLight() {
    return CalculateLightByDirection(directionalLight.base, directionalLight.direction);
}

vec4 CalculatePointLights() {
    vec4 totalColor = vec4(0, 0, 0, 0);

    for (int i = 0; i < pointLightCount; i++)
    {
        vec3 direction = fragmentPosition - pointLights[i].position;
        float distance = length(direction);
        direction = normalize(direction);

        vec4 color = CalculateLightByDirection(pointLights[i].base, direction);
        float attenuation = pointLights[i].exponent * distance * distance + 
                            pointLights[i].linear * distance +
                            pointLights[i].constant;

        totalColor += (color / attenuation);
    }

    return totalColor;
}

void main() {
    vec2 adjustTexCoord = vec2(uvsFragmentShader.x, 1.0 - uvsFragmentShader.y);

    vec4 finalColor = CalculateDirectionalLight();
    finalColor += CalculatePointLights();

    if (usingTexture == 1)
    {
        vec4 textureColor = texture(textureSampler, adjustTexCoord);
        
        fragColor = textureColor * finalColor;
    }
    else
    {
        // Sumar el final color tambien
        fragColor = baseColor;
    }
}
