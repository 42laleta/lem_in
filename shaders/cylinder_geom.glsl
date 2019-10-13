#version 120
#extension GL_EXT_geometry_shader4: enable

uniform float		width;
varying out vec2	gCoord;
varying out vec2	pt_1;
varying out vec2	pt_2;
varying out vec2	pt_cur;
varying out float	l_w;

void main()
{ 
	float	w;
	float	lw;

	vec2 pt1 = gl_PositionIn[0].xy / gl_PositionIn[0].w;
    vec2 pt2 = gl_PositionIn[1].xy / gl_PositionIn[1].w;
    vec2 dir2D = normalize(pt1 - pt2);
    vec2 normOffset = vec2(-dir2D.y, dir2D.x);

	w = gl_PositionIn[0].w;
	if (w < 1)
		w = 1;
	lw = width / w;
	l_w = lw;

    gl_Position = vec4(pt1 + ( normOffset - dir2D) * lw, gl_PositionIn[0].zw);
pt_cur = gl_Position.xy;
    gl_Position.xy *= gl_Position.w;
pt_1 = pt1;
pt_2 = pt2;
    gCoord = vec2(1,1);
    EmitVertex();

    gl_Position = vec4(pt1 + (-normOffset - dir2D) * lw, gl_PositionIn[0].zw);
pt_cur = gl_Position.xy;
    gl_Position.xy *= gl_Position.w;
pt_1 = pt1;
pt_2 = pt2;
    gCoord = vec2(-1,1);
    EmitVertex();

    gl_Position = vec4(pt2 + ( normOffset + dir2D) * lw, gl_PositionIn[1].zw);
pt_cur = gl_Position.xy;
    gl_Position.xy *= gl_Position.w;
pt_1 = pt1;
pt_2 = pt2;
    gCoord = vec2(1,-1);
    EmitVertex();

    gl_Position = vec4(pt2 + (-normOffset + dir2D) * lw, gl_PositionIn[1].zw);
pt_cur = gl_Position.xy;
    gl_Position.xy *= gl_Position.w;
pt_1 = pt1;
pt_2 = pt2;
    gCoord = vec2(-1,-1);
    EmitVertex();
	EndPrimitive();
}
