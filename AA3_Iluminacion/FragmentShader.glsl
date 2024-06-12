#version 440 core

uniform vec3 directionalColor;
uniform float directionalAmbientIntensity;
uniform float directionalDiffuseIntensity;
uniform vec3 directionalDirection;

uniform vec3 pointColor;
uniform float pointAmbientIntensity;
uniform float pointDiffuseIntensity;
uniform vec3 pointPosition;
uniform float pointConstant;
uniform float pointLinear;
uniform float pointExponent;

uniform vec3 spotColor;
uniform float spotAmbientIntensity;
uniform float spotDiffuseIntensity;
uniform vec3 spotPosition;
uniform float spotConstant;
uniform float spotLinear;
uniform float spotExponent;
uniform vec3 spotDirection;
uniform float spotEdge;

uniform float materialSpecularIntensity;
uniform float materialShininess;

uniform vec2 windowSize;

uniform int usingTexture;
uniform sampler2D textureSampler;
uniform vec4 baseColor;

uniform vec3 eyePosition;

in vec2 uvsFragmentShader;
in vec3 normalsFragmentShader;
in vec3 fragmentPosition;

out vec4 fragColor;

vec4 CalculateLight(vec3 color, float ambient, float diffuse, vec3 direction) {
    vec4 ambientColor = vec4(color, 1.f) * ambient;

    float diffuseFactor = max(dot(normalize(normalsFragmentShader), normalize(direction)), 0.f);
    vec4 diffuseColor = vec4(color * diffuse * diffuseFactor, 1.0f);

    vec4 specularColor = vec4(0, 0, 0, 0);

    if (diffuseFactor > 0.f) {
        vec3 fragToEye = normalize(eyePosition - fragmentPosition);
        vec3 reflectedVertex = normalize(reflect(direction, normalize(normalsFragmentShader)));
    
        float specularFactor = dot(fragToEye, reflectedVertex);

        if (specularFactor > 0.f) {
            specularFactor = pow(specularFactor, materialShininess);
            specularColor = vec4(color * materialSpecularIntensity * specularFactor, 1.0f);
        }
    }
    
    return (ambientColor + diffuseColor + specularColor);
}


vec4 CalculateLightTypes()
{
    vec4 finalColor = vec4(0, 0, 0, 0);

    // DIRECTIONAL LIGHT
    vec4 directionalColor = CalculateLight(directionalColor, directionalAmbientIntensity, directionalDiffuseIntensity, directionalDirection);

    // POINT LIGHT
    vec3 pointDirection = fragmentPosition - pointPosition;
    float distance = length(pointDirection);
    pointDirection = normalize(pointDirection);

    vec4 pointColor = CalculateLight(pointColor, pointAmbientIntensity, pointDiffuseIntensity, pointDirection);
    float pointAttenuation = (pointExponent * distance * distance) + 
                        (pointLinear * distance) +
                        pointConstant;

    finalColor += pointColor / pointAttenuation;

    // SPOT LIGHT
    vec3 rayDirection = normalize(fragmentPosition - spotPosition);
    float slFactor = dot(rayDirection, spotDirection);

    if(slFactor > spotEdge) {
        vec3 pointDirection = fragmentPosition - spotPosition;
        float distance = length(pointDirection);
        pointDirection = normalize(pointDirection);

        vec4 spotColor = CalculateLight(spotColor, spotAmbientIntensity, spotDiffuseIntensity, spotPosition);
        float spotAttenuation = (spotExponent * distance * distance) + 
                            (spotLinear * distance) +
                            spotConstant;

        finalColor += (spotColor * (1.f - (1.f - slFactor) * (1.f / (1.f - spotEdge)))) / spotAttenuation;
    } else {
        finalColor += vec4(0, 0, 0, 0);
    }

    return finalColor;
}

void main() {
    vec2 adjustTexCoord = vec2(uvsFragmentShader.x, 1.0 - uvsFragmentShader.y);

    vec4 finalColor = CalculateLightTypes();

    if (usingTexture == 1) {
        vec4 textureColor = texture(textureSampler, adjustTexCoord);
        
        fragColor = textureColor * finalColor;
    }
    else {
        fragColor = baseColor * finalColor;
    }
}