#version 330 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D tex0;
in float vDistance;

uniform vec3 fogColor;

void main()
{
    float fogStart = 0.0;
    float fogEnd = 400.0;

    vec4 texColor = texture(tex0, texCoord);

    float fogFactor = smoothstep(fogStart, fogEnd, vDistance);
    fogFactor = clamp(fogFactor, 0.0, 1.0);

    vec3 finalColor = mix(texColor.rgb, fogColor, fogFactor);
    FragColor = vec4(finalColor, texColor.a);
}