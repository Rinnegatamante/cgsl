attribute vec3 position;
attribute vec3 normal;
uniform mat4 ModelViewProjectionMatrix;
uniform mat4 NormalMatrix;
uniform vec4 LightSourcePosition;
uniform vec4 MaterialColor;
varying vec4 Color;
void main() {
    vec3 N = normalize((NormalMatrix * vec4(normal, 1.0)).xyz);
    vec3 L = normalize(LightSourcePosition.xyz);
    float diffuse = max(dot(N, L), 0.0);
    Color = diffuse * MaterialColor;
    gl_Position = ModelViewProjectionMatrix * vec4(position, 1.0);
}