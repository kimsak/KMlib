//
//  Shader.vsh
//  iOS_Sample1
//
//  Created by 木村 裕作 on 2013/03/26.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//
//#version 150

void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}