#version 440 core

uniform vec3 directionalColor;
uniform float directionalAmbientIntensity;
uniform vec3 directionalDirection;

uniform vec3 pointColor;
uniform float pointAmbientIntensity;
uniform vec3 pointPosition;
uniform float pointConstant;
uniform float pointLinear;
uniform float pointQuadratic;

uniform vec3 spotColor;
uniform float spotAmbientIntensity;
uniform vec3 spotPosition;
uniform float spotConstant;
uniform float spotLinear;
uniform float spotQuadratic;
uniform vec3 spotDirection;
uniform float spotCutOff;
uniform float spotOuterCutOff;

uniform float materialDiffuseIntensity;
uniform float materialSpecularIntensity;
uniform float materialShininess;
uniform vec3 cameraPosition;

uniform vec2 windowSize;

uniform int usingTexture;
uniform sampler2D textureSampler;
uniform vec4 baseColor;

in vec2 uvsFragmentShader;
in vec3 normalsFragmentShader;
in vec3 fragmentPosition;

out vec4 fragColor;

// Calculamos la luz ambiental
// Ia = Ka * La 
// Intensidad Ambiental = Factor Ambiental * Color Ambiental
vec3 CalculateAmbientIntensity(vec3 objectColor, float ambientFactor) {
    return (objectColor * ambientFactor);
}

// Calculamos la luz difusa
// Id = Kd * (L * N) * Ld 
// Intensidad difusa = Factor difuso * (Vector Luz * Vector Normal del plano) * Color Difuso
vec3 CalculateDiffuseIntensity(vec3 color, vec3 normal, vec3 lightDirection, float diffuseFactor) {
    vec3 diffuseColor = vec3(0, 0, 0);

    // Calcula el dot product entre la normal y la direcion de la luz
    // Con la funcion max(), nos aseguramos de que la luz difusa nunca sea negativa.
    float intensity = max(dot(normalize(normal), normalize(lightDirection)), 0.f);

    return (color * intensity * diffuseFactor);
}

// Calculamos la luz especular
// Is = Ks * (V * r)^shininess * Ls 
// Intensidad especular = Factor Especular * (Vector visor(camara) * Vector reflector)^Shininnes(depende del material) * Color Especular
vec3 CalculateSpecularIntensity(vec3 color, vec3 normal, vec3 lightDirection, vec3 viewPosition, float specularFactor, float shininess) {
    vec3 specularColor = vec3(0, 0, 0);

    normal = normalize(normal);
    lightDirection = normalize(lightDirection);
    viewPosition = normalize(viewPosition);

    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float reflectionIntensity = dot(viewPosition, reflectionDirection);

    if (reflectionIntensity > 0.f) {
        reflectionIntensity = pow(reflectionIntensity, shininess);
        specularColor = color * specularFactor * reflectionIntensity;
    }

    return specularColor;
}

// Calculamos la iluminacion de Phong
// La * Ka + Ld * (Kd * (L * n)) + Ls * (Ks * (V * r)^alpha)
vec3 CalculatePhongLighting(vec3 color, float ambient, vec3 direction) {
    vec3 ambientLight = CalculateAmbientIntensity(color, ambient);
    vec3 diffuseLight = CalculateDiffuseIntensity(color, normalsFragmentShader, direction, materialDiffuseIntensity);
    vec3 specularLight = CalculateSpecularIntensity(color, normalsFragmentShader, direction, cameraPosition, materialSpecularIntensity, materialShininess);

    return (ambientLight + diffuseLight + specularLight);
}

// Calculamos la attenuacion, que la luz afecte dependiendo de la distancia de donde este al plano
// 1.0f / Kc + Kl * d + Kq * d^2
float CalculateAttenuation(float constant, float linear, float quadratic, float distance)
{
    return (1.0f / (constant + linear * distance + quadratic * distance * distance));
}

// Calculamos la luz direccional
vec3 CalculateDirectionalLight()
{
    return CalculatePhongLighting(directionalColor, directionalAmbientIntensity, -directionalDirection);
}

// Calculamos la luz puntual usando la atenuacion.
vec3 CalculatePointLight()
{
    vec3 pointDirection = pointPosition - fragmentPosition;

    vec3 pointColor = CalculatePhongLighting(pointColor, pointAmbientIntensity, normalize(pointDirection));
    float attenuation = CalculateAttenuation(pointConstant, pointLinear, pointQuadratic, length(pointDirection));

    return (pointColor * attenuation);
}

// Calculamos la luz foco
vec3 CalculateSpotLight()
{
    // Soft edges: I = angle - tetha / epsilon
    // angle = el angulo de corte que especifica el radio del foco.
    // tetha = el angulo entre el vector que apunta al fragment hacia la fuente de luz y la direccion que el foco esta apuntando. Tendria que ser menor que el angulo
    // epsilon = es el coseno entre la diferencia del cono interior al cono exterior. 
    // I = angle - (vector del fragment * vector del foco) / cos(cono interior) - cos(cono exterior) 

    vec3 spotDir = spotPosition - fragmentPosition;

    float tetha = dot(normalize(spotDir), normalize(-spotDirection));

    float cosInnerCutOff = cos(radians(spotCutOff));
    float cosOuterCutOff = cos(radians(spotOuterCutOff));

    float epsilon = cosInnerCutOff - cosOuterCutOff;
    float intensity = clamp((tetha - cosOuterCutOff) / epsilon, 0.0f, 1.0f);

    if(tetha > cosOuterCutOff) {
        float attenuation = CalculateAttenuation(spotConstant, spotLinear, spotQuadratic, length(spotDir));
        vec3 spotColor = CalculatePhongLighting(spotColor, spotAmbientIntensity, normalize(spotDir));

        return (spotColor * intensity * attenuation);
    } else {
        return vec3(0, 0, 0);
    }
}

vec3 CalculateLightCasters()
{
    vec3 finalColor = vec3(0.f, 0.f, 0.f);

    // DIRECTIONAL LIGHT
    finalColor += CalculateDirectionalLight();

    // POINT LIGHT
    finalColor += CalculatePointLight();

    // SPOT LIGHT
    finalColor += CalculateSpotLight();

    return finalColor;
}

void main() {
    vec2 adjustTexCoord = vec2(uvsFragmentShader.x, 1.0 - uvsFragmentShader.y);

    vec4 finalColor = vec4(CalculateLightCasters(), 1.f);

    if (usingTexture == 1) {
        fragColor = texture(textureSampler, adjustTexCoord) * finalColor;
    }
    else {
        fragColor = baseColor * finalColor;
    }
}