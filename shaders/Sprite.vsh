//#version 150

attribute vec4 position;
attribute vec2 texcoord;

varying vec4 colorVarying;
varying vec2 texCoord0;

uniform vec4 monoColor;
uniform mat4 modelViewProjectionMatrix;

uniform mat4 texMatrix;

void main()
{
    colorVarying = monoColor;
    
    gl_Position = modelViewProjectionMatrix * position;
	
    vec4 texcoordVec4 = vec4(texcoord, 0, 1);
    texcoordVec4 = texMatrix * texcoordVec4;
    texCoord0 = texcoordVec4.xy;
    //gl_Texcoord[0] = texcoord;
}
