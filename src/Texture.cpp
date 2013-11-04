//
//  Texture.cpp
//  iOS_Sample2
//
//  Created by 木村 裕作 on 2013/03/30.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#include "Texture.h"
#include "_useGL.h"

CTexture::CTexture(int w, int h) : textureID(0), width(w), height(h) {
    // テクスチャオブジェクトの作成
    glGenTextures(1, &textureID);
    
    originalW = w;
    originalH = h;
}

CTexture::~CTexture() {
    // テクスチャオブジェクトの解放
    glDeleteTextures(1, &textureID);
}

void CTexture::Bind() {
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void CTexture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
