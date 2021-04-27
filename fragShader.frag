#version 430

in vec4 color;
out vec4 outColor;

void main() {
    //outColor = vec4(1.,1.,1.,1.);
    outColor = color.yzwx;
    //outColor = vec4(1,1,1,0);
}