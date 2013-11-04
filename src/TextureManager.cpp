//
//  TextureManager.mm
//  KandataGame
//
//  Created by 木村 裕作 on 2013/06/24.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#include "TextureManager.h"
#include "PixelData.h"
#include <cassert>

// テクスチャの作成
bool TextureManager::CreateTexture(std::string name, std::string filename, std::string type_name) {
    // 登録の有無の確認
    if(GetTexture(name)) return false;
    
    // ピクセルデータの生成
    PixelData pixels;
    if( !PixelData::LoadAndCopyPixelData(filename.c_str(), type_name.c_str(), &pixels) ) {
        return false;
    }
    
    // ピクセルデータのリサイズ
    int w, h;
    uint8_t *pNewPixelArr = NULL;
    PixelData::ResizePixelData(&pixels, &w, &h, &pNewPixelArr);
    
    // テクスチャのロード
    CTexture *pTexture = new CTexture(w, h);
    if( !LoadTexture(pNewPixelArr, w, h, pTexture) ) {
        if(pNewPixelArr) delete [] pNewPixelArr;
        delete pTexture;    // ロード失敗なのでテクスチャの破棄
        return false;
    }
    // オリジナルサイズを設定
    pTexture->SetOriginalSize(pixels.GetWidth(), pixels.GetHeight());
    
    // テクスチャの登録
    texture_map[name] = pTexture;
    
    if(pNewPixelArr) delete [] pNewPixelArr;
    return true;
}

// テクスチャの取得
CTexture *TextureManager::GetTexture(std::string name) const {
    auto it = texture_map.find(name);
    
    return it != texture_map.end() ? it->second : NULL;
}

// テクスチャの破棄
void TextureManager::Dispose() {
    for (std::map<std::string, CTexture *>::iterator it=texture_map.begin(); it!=texture_map.end(); it++) {
        delete it->second;
    }
    texture_map.clear();
}

// テクスチャのロード
bool TextureManager::LoadTexture(const unsigned char *pPixels, int width, int height, CTexture *pTexture) {
    glBindTexture(GL_TEXTURE_2D, pTexture->GetID());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pPixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return true;
}

