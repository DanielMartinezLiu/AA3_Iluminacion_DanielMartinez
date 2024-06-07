#version 440 core

struct DirectionalLight {
    vec3 color;
    float ambientIntensity;
    vec3 direction;
    float diffuseIntensity;
};

uniform vec2 windowSize;
uniform int usingTexture;
uniform sampler2D textureSampler;
uniform vec4 baseColor;

uniform DirectionalLight directionalLight;

in vec2 uvsFragmentShader;
in vec3 normalsFragmentShader;

out vec4 fragColor;

void main() {
        vec2 adjustTexCoord = vec2(uvsFragmentShader.x, 1.0 - uvsFragmentShader.y);
        vec4 ambientColor = vec4(directionalLight.color, 1.f) * directionalLight.ambientIntensity;

        float diffuseFactor = max(dot(normalize(normalsFragmentShader), normalize(directionalLight.direction)), 0.f);
        vec4 diffuseColor = vec4(directionalLight.color, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;

        if (usingTexture == 1)
        {
            vec4 textureColor = texture(textureSampler, adjustTexCoord);
            fragColor = textureColor * (ambientColor + diffuseColor);
        }
        else
        {
            fragColor = baseColor;
        }
}
