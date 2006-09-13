uniform float amplitude;
uniform vec2 scale;
uniform vec4 baseColor;

varying vec2 screenpos;

varying vec3 lightDir;
varying vec3 normal;

float crng(float x) {
    return 0.5 + (x / 2.0);
}

float brightnessAt(vec2 pos) {
    return crng( sin(80.0 * pos.y) );
}

vec2 distort(vec2 pos) {
	pos *= scale;
    vec2 sinp = vec2(pos.x, pos.y + amplitude * sin(pos.x * 40.0) );
//    return vec2(sinp.x, sinp.y * cos(sinp.x));
	return sinp;
}

void main(void) {
    normal = normalize(normal);
    lightDir = normalize(lightDir);
	float n = dot(normal, lightDir);
	n = max(0.0, min(1.0, n));
    n += 0.1;

    vec2 newpos = distort(screenpos);
    float threshold = brightnessAt(newpos);

    float diff = max(0.0, n - threshold);
    diff = smoothstep(-0.1, 0.6, diff);

    gl_FragColor = baseColor * diff;
}
