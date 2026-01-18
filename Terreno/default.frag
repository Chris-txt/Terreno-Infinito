#version 330 core

out vec4 FragColor;
in vec2 texCoord;
in float vDistance;
uniform sampler2D tex0;

uniform vec3 fogColor;

void main()
{
    float fogEnd = 400.0;
    float fogStart = 50.0;

    vec4 texColor = texture(tex0, texCoord);

    float fogFactor = smoothstep(fogStart, fogEnd, vDistance);
    fogFactor = pow(fogFactor, 0.4);

    vec3 finalColor = mix(texColor.rgb, fogColor, fogFactor);
    FragColor = vec4(finalColor, texColor.a);
}