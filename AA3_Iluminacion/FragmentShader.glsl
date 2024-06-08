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

struct SpotLight {
    PointLight pointBase;
    vec3 direction;
    float edge;
};

struct Material {
    float specularIntensity;
    float shininess;
};

const int MAX_DIRECTIONAL_LIGHTS = 3;
const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

uniform vec2 windowSize;

uniform int usingTexture;
uniform sampler2D textureSampler;
uniform vec4 baseColor;

uniform vec3 eyePosition;

uniform int directionalLightCount;
uniform int pointLightCount;
uniform int spotLightCount;

uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform Material material;

in vec2 uvsFragmentShader;
in vec3 normalsFragmentShader;
in vec3 fragmentPosition;

out vec4 fragColor;

vec4 CalculateLight(Light light, vec3 direction) {
    vec4 ambientColor = vec4(light.color, 1.f) * light.ambientIntensity;

    float diffuseFactor = max(dot(normalize(normalsFragmentShader), normalize(direction)), 0.f);
    vec4 diffuseColor = vec4(light.color * light.diffuseIntensity * diffuseFactor, 1.0f);

    vec4 specularColor = vec4(0, 0, 0, 0);

    if (diffuseFactor > 0.f) {
        vec3 fragToEye = normalize(eyePosition - fragmentPosition);
        vec3 reflectedVertex = normalize(reflect(direction, normalize(normalsFragmentShader)));
    
        float specularFactor = dot(fragToEye, reflectedVertex);

        if (specularFactor > 0.f) {
            specularFactor = pow(specularFactor, material.shininess);
            specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0f);
        }
    }
    
    return (ambientColor + diffuseColor + specularColor);
}

vec4 CalculateDirectionalLight(DirectionalLight dLight) {
    vec4 color = CalculateLight(dLight.base, dLight.direction);

    return color;
}
vec4 CalculatePointLight(PointLight pLight) {
    vec3 direction = fragmentPosition - pLight.position;
    float distance = length(direction);
    direction = normalize(direction);

    vec4 color = CalculateLight(pLight.base, direction);
    float attenuation = pLight.exponent * distance * distance + 
                        pLight.linear * distance +
                        pLight.constant;

    return (color / attenuation);
}

vec4 CalculateSpotLight(SpotLight sLight) {
    vec3 rayDirection = normalize(fragmentPosition - sLight.pointBase.position);
    float slFactor = dot(rayDirection, sLight.direction);

    if(slFactor > sLight.edge) {
        vec4 color = CalculatePointLight(sLight.pointBase);

        return (color * (1.f - (1.f - slFactor) * (1.f / (1.f - sLight.edge))));

    } else {
        return vec4(0, 0, 0, 0);
    }
}

vec4 CalculateDirectionalLight() {
    vec4 totalColor = vec4(0, 0, 0, 0);

    for (int i = 0; i < directionalLightCount; i++) {
         totalColor += CalculateDirectionalLight(directionalLights[i]);
    }

    return totalColor;
}

vec4 CalculatePointLights() {
    vec4 totalColor = vec4(0, 0, 0, 0);

    for (int i = 0; i < pointLightCount; i++) {
        totalColor += CalculatePointLight(pointLights[i]);
    }

    return totalColor;
}

vec4 CalculateSpotLights() {
    vec4 totalColor = vec4(0, 0, 0, 0);

    for (int i = 0; i < spotLightCount; i++) {
        totalColor += CalculateSpotLight(spotLights[i]);
    }

    return totalColor;
}
void main() {
    vec2 adjustTexCoord = vec2(uvsFragmentShader.x, 1.0 - uvsFragmentShader.y);

    vec4 finalColor = vec4(0, 0, 0, 0);
    finalColor += CalculateDirectionalLight();
    finalColor += CalculatePointLights();
    finalColor += CalculateSpotLights();

    if (usingTexture == 1) {
        vec4 textureColor = texture(textureSampler, adjustTexCoord);
        
        fragColor = textureColor * finalColor;
    }
    else {
        fragColor = baseColor * finalColor;
    }
}
