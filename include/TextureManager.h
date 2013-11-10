//
//  TextureManager.h
//  KandataGame
//
//  Created by 木村 裕作 on 2013/06/24.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include <map>
#include <string>
#include "_useGL.h"
#include "Texture.h"

class TextureManager {
    std::map<std::string, CTexture *> texture_map;
    
    bool LoadTexture(const unsigned char *pPixels, int width, int height, CTexture *pTexture);
public:
    /**
     *  テクスチャを作成し、マップに登録する。
     */
    bool CreateTexture(std::string name, std::string filename, std::string type_name);
    
    /**
     *  テクスチャオブジェクトの参照を取得する。
     */
    CTexture *GetTexture(std::string name) const;
    
    /**
     *  全テクスチャの破棄
     */
    void Dispose();
};

#endif /* defined(TEXTURE_MANAGER_H_) */
