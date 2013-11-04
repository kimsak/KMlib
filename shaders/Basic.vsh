//
//  Shader.vsh
//  Created by 木村 裕作 on 2013/03/26.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//
//#version 150

attribute vec4 position;
attribute vec2 texcoord;

varying vec4 colorVarying;
varying vec2 texCoord0;

uniform vec4 monoColor;
//uniform mat4 modelViewProjectionMatrix;

uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 wldMat;
//uniform mat3 normalMatrix;

uniform mat4 texMatrix;

void main()
{
    colorVarying = monoColor;
    
    mat4 t = projMat;
    t *= viewMat;
    t *= wldMat;
    gl_Position = t * position;
	
	vec4 texcoordVec4 = vec4(texcoord, 0, 1);
	texcoordVec4 = texMatrix * texcoordVec4;
	texCoord0 = texcoordVec4.xy;
	//gl_Texcoord[0] = texcoord;
}
