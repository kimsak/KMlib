//
//  Texture.cpp
//  iOS_Sample2
//
//  Created by 木村 裕作 on 2013/03/30.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#include "Texture.h"
#include "_useGL.h"
#include "PixelData.h"

/**
 *  コンストラクタ
 */
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

void CTexture::Bind(int unit) {
    // テクスチャユニットの設定
    if(0 <= unit && unit < 32) glActiveTexture( (GL_TEXTURE0) + unit );
    
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void CTexture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

/*static*/CTexture *CTexture::Create(const std::string &filename, const std::string &ext) {
    /**
     *  PixelDataの生成
     */
    PixelData pixels;
    if( !PixelData::LoadAndCopyPixelData(filename.c_str(), ext.c_str(), &pixels) ) {
        return nullptr;
    }
    
    /**
     *  ピクセルデータのリサイズ
     *  （２の冪乗のサイズになるよう調整）
     */
    int w, h;
    uint8_t *pNewPixelArr = nullptr;
    PixelData::ResizePixelData(&pixels, &w, &h, &pNewPixelArr);
    
    /**
     *  テクスチャのロード
     */
    CTexture *pTexture = new CTexture(w, h);
    pTexture->Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pNewPixelArr);
    pTexture->Unbind();
    
    // オリジナルサイズを設定
    pTexture->SetOriginalSize(pixels.GetWidth(), pixels.GetHeight());
    
    if(pNewPixelArr) delete [] pNewPixelArr;    // リサイズされたピクセルデータ配列の破棄
    return pTexture;
}
