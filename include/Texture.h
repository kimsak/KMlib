//
//  Texture.h
//  iOS_Sample2
//
//  Created by 木村 裕作 on 2013/03/30.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef KMLIB_TEXTURE_H_
#define KMLIB_TEXTURE_H_
#include "Component.h"
#include <string>
#include <memory>

class CTexture;
typedef std::shared_ptr<CTexture> TextureRef;

class CTexture : public IComponent {
    unsigned int textureID;
    int width, height;
    int originalW, originalH;
public:
    CTexture(int w=-1, int h=-1);
    ~CTexture();
    
    void SetTextureSize(int w, int h) {
        width = w, height = h;
    }
    
    unsigned GetID() const { return textureID; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    float GetAspect() const { return (float)width/height; }
    
    void SetOriginalSize(int ow, int oh) {
        originalW = ow, originalH = oh;
    }
    int GetOriginalW() const { return originalW; }
    int GetOriginalH() const { return originalH; }
    float GetOriginalAspect() const {
        return (float)originalW/originalH;
    }
    
    void Bind(int unit = -1);
    void Unbind();
    
    static TextureRef Create(const std::string &filename, const std::string &ext);
};


#endif
