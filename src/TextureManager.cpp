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
bool TextureManager::CreateAndRegisterTexture(const std::string &name, const std::string &filename, const std::string &type_name) {
    // 登録の有無の確認
    if(GetTexture(name) == nullptr) return false;
    
    TextureRef texture_ref = CTexture::Create(filename, type_name);
    if(!texture_ref) return false;
    
    // テクスチャの登録
    texture_map[name] = texture_ref;
    
    return true;
}

// テクスチャの取得
CTexture *TextureManager::GetTexture(const std::string &name) const {
    auto it = texture_map.find(name);
    
    return it != texture_map.end() ? (it->second).get() : nullptr;
}

// テクスチャの破棄
void TextureManager::DisposeAllTextures() {
    texture_map.clear();
}

