#version 430

layout(location = 0) in vec2 position;
uniform float time;
uniform float loopDuration = 3;
uniform bool mouseDown;
uniform vec2 mousePos;
uniform vec2 window;
vec2 mousePosOffset = vec2(0.0,0.0);
uniform float timeDif = 0;

void main() {
    mousePosOffset = vec2((mousePos.x*2 - window.x)/window.x, -(mousePos.y*2 - window.y)/window.y);
    
    if(mouseDown){
        gl_Position = vec4(position + mousePosOffset, 0, 1);
        return;
    }

    vec4 pos = vec4(position,0,1);
    float timeScale = 3.14159f * 2.0f / loopDuration; //should also be paused

    float currTime = mod(time, loopDuration);

    vec4 timeOffset = vec4(
        cos(currTime * timeScale) * 0.5f,
        sin(currTime * timeScale) * 0.5f,
        0.0f,
        0.0f);

    gl_Position = pos + vec4(mousePosOffset,0.0,0.0) + timeOffset;
}