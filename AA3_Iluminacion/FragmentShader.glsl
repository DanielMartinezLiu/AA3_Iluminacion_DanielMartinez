#version 440 core

struct DirectionalLight {
    vec3 color;
    float ambientIntensity;
    vec3 direction;
    float diffuseIntensity;
};

struct Material {
    float specularIntensity;
    float shininess;
};

uniform vec2 windowSize;

uniform int usingTexture;
uniform sampler2D textureSampler;
uniform vec4 baseColor;

uniform vec3 eyePosition;

uniform DirectionalLight directionalLight;
uniform Material material;

in vec2 uvsFragmentShader;
in vec3 normalsFragmentShader;
in vec3 fragmentPosition;

out vec4 fragColor;

void main() {
    vec2 adjustTexCoord = vec2(uvsFragmentShader.x, 1.0 - uvsFragmentShader.y);
    vec4 ambientColor = vec4(directionalLight.color, 1.f) * directionalLight.ambientIntensity;

    float diffuseFactor = max(dot(normalize(normalsFragmentShader), normalize(directionalLight.direction)), 0.f);
    vec4 diffuseColor = vec4(directionalLight.color, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;

    vec4 specularColor = vec4(0, 0, 0, 0);

    if (diffuseFactor > 0.f)
    {
        vec3 fragToEye = normalize(eyePosition - fragmentPosition);
        vec3 reflectedVertex = normalize(reflect(-directionalLight.direction, normalize(normalsFragmentShader)));
    
        float specularFactor = max(dot(fragToEye, reflectedVertex), 0.0);

        if (specularFactor > 0.f)
        {
            specularFactor = pow(specularFactor, material.shininess);
            specularColor = vec4(directionalLight.color * material.specularIntensity * specularFactor, 1.0);
        }
    }

    if (usingTexture == 1)
    {
        vec4 textureColor = texture(textureSampler, adjustTexCoord);
        fragColor = textureColor * (ambientColor + diffuseColor + specularColor);
    }
    else
    {
        fragColor = baseColor;
    }
}
