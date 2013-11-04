//
//  Texture.h
//  iOS_Sample2
//
//  Created by 木村 裕作 on 2013/03/30.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef TEXTURE_H_
#define TEXTURE_H_
#include "Component.h"

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
    
    void Bind();
    void Unbind();
};


#endif
