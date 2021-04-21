#version 430

layout(location = 0) in vec2 vertexPos;  //origin point where buffer got created 
uniform vec2 oPos = vec2(0,0); //new origin point
uniform float rotAngle = 0; //
uniform float scale = 1;

void main() {
    vec2 pos = vertexPos*scale ;
    float len = length(pos - oPos);
    float cos_angle = cos(rotAngle);
    float sin_angle = sin(rotAngle);
    vec2 temp;
    temp.x = (pos.x ) * cos_angle - (pos.y) * sin_angle;
    temp.y = (pos.x) * sin_angle + (pos.y) * cos_angle;
    pos = temp + oPos;
    gl_Position = vec4(pos,0,1);
}