#version 330 core

in vec3 onormal;

layout(location=0) out vec4 frag_color;

uniform sampler2D texunit;

void main(void)
{
    vec3 normal = normalize(onormal);
    // Change the normal convention
    normal = vec3(onormal.x, -onormal.y, -onormal.z);
    // Use the normal as UV coordinate for the texture lookup.
    // We use 0.495 instead of 0.5 to keep a safe distance from the border of
    // the sphere.
    vec2 uv = 0.5 + 0.495 * normal.xy;
    // Do a texture lookup at original resolution (mipmapping would lead to
    // bleeding of the background into the texture of the sphere)
    frag_color = textureLod(texunit, uv, 0);
}

