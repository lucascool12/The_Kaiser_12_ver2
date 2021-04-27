#version 430

layout(location = 0) in vec2 vertexPos;  //origin point where buffer got created 
layout(location = 1) in vec4 theColor;
uniform vec2 oPos = vec2(0,0); //new origin point
uniform float rotAngle = 0; //
uniform float scale = 1;
uniform vec2 w;
out vec4 color;

void main() {
    vec2 pos = vertexPos*scale ;
    float reRatio = w.x/w.y;
    float windowScale_x = 600.0/w.x;
    float windowScale_y = 600.0/w.y;
    //pos.x = pos.x * windowScale_x;
    //pos.y = pos.y * windowScale_y ;
    float cos_angle = cos(rotAngle);
    float sin_angle = sin(rotAngle);
    mat2 rotMat = mat2(vec2(cos_angle,sin_angle),vec2(-sin_angle,cos_angle));
    //vec2 temp;
    // temp.x = (pos.x ) * cos_angle - (pos.y) * sin_angle;
    // temp.y = (pos.x) * sin_angle + (pos.y) * cos_angle;
    pos = rotMat * pos;
    pos.x = (pos.x + oPos.x )* windowScale_x*reRatio;
    pos.y = (pos.y + oPos.y )* windowScale_y*reRatio;
    color = theColor;
    gl_Position = vec4(pos,0,1);
}