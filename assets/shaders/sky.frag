#version 330 core

in vec3 viewRay;
out vec4 FragColor;

uniform mat4 invProj;
uniform mat4 invView;

uniform vec3 uTopColor;
uniform vec3 uHorizonColor;
uniform vec3 uBottomColor;

void main()
{
    vec4 ray = invProj * vec4(viewRay, 1.0);
    ray = vec4(ray.xyz, 0.0);

    vec3 worldDir = normalize((invView * ray).xyz);

    float t = worldDir.y * 0.5 + 0.5;

    vec3 sky =
        mix(uBottomColor, uHorizonColor, smoothstep(0.0, 0.5, t));

    sky =
        mix(sky, uTopColor, smoothstep(0.5, 1.0, t));

    FragColor = vec4(sky, 1.0);
}