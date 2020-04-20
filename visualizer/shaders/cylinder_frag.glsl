#version 120

varying vec2 gCoord;
varying vec2 pt_1;
varying vec2 pt_2;
varying vec2 pt_cur;
varying float l_w;

float distToLine(vec2 pt1, vec2 pt2, vec2 testPt)
{
    vec2 lineDir = pt2 - pt1;
    vec2 perpDir = vec2(lineDir.y, -lineDir.x);
    vec2 dirToPt1 = pt1 - testPt;
    return (dot(normalize(perpDir), dirToPt1)); //abs
}

void main(void)
{
//vec3 l = normalize(gl_LightSource[0].position.xyz);
float dr = distToLine(pt_1, pt_2, pt_cur);
//vec3 n = vec3(pt_2 - pt_1, dr);
//float intensity = .2 + max(dot(l,normalize(n)), 0.0);
//float d = 0.5 * intensity;;
//float d = (1.0 - dr / l_w);
//gl_FragColor = vec4(vec3(d), 1.0);
gl_FragDepth = gl_FragCoord.z + dr * gl_DepthRange.diff / 2.0  * gl_ProjectionMatrix[2].z;
 
//   float dist = distToLine(pt_1, pt_2, pt_cur);
//   float d = (1.0 - dist / 0.008);
//   gl_FragColor = vec4(vec3(d), 1.0);


	float r2 = dot(gCoord, gCoord);
    float d = exp(r2 * -1.2); // Gaussian Splat
    gl_FragColor = vec4(vec3(d), 1.0);
}
