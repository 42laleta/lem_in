#version 120

attribute vec3		coord_3d;
uniform vec4		viewport;

void main(void)
{
	gl_Position = gl_ModelViewProjectionMatrix * vec4(coord_3d, 1.0);
}
