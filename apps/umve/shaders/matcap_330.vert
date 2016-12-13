#version 330 core

/* Vertex shader special variables
 *
 * in  int   gl_VertexID;
 * in  int   gl_InstanceID;
 * out gl_PerVertex {
 *     vec4  gl_Position;
 *     float gl_PointSize;
 *     float gl_ClipDistance[];
 * };
 */

in vec4 pos;
in vec3 normal;

out vec3 onormal;

uniform mat4 viewmat;
uniform mat4 projmat;

void main(void)
{
    onormal = normalize((viewmat * vec4(normal, 0.0)).xyz);
    gl_Position = projmat * (viewmat * pos);
}

