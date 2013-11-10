//
//  GameCore.h
//  KandataGame
//
//  Created by 木村 裕作 on 2013/06/16.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef BASE_GAME_H_
#define BASE_GAME_H_
#include "Texture.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#if defined(GAMECORE_GLINFO_DISPLAY)
#include <iostream>
#endif  // defined(GAMECORE_GLINFO_DISPLAY)

typedef unsigned ShaderObject;

class GameCore {
    static GameCore core;
    
    int displayWidth, displayHeight;
    
    TextureManager      textureManager;
    ShaderManager       shaderManager;
    
public:
    static GameCore &GetInstance() { return core; }
    
    // 仮想デストラクタ
    virtual ~GameCore() {}
    
    virtual void Initialize(int w = 1, int h = 1) {
        displayWidth = w, displayHeight = h;
        
#if defined (GAMECORE_GLINFO_DISPLAY)
        std::cout << "GL Vendor: " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "GL Renderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
#endif  // defined(GAMECORE_GLINFO_DISPLAY)
    }
    
    virtual void Finalize() {
        textureManager.Dispose();
        shaderManager.Dispose();
    };
    
    int GetDisplayWidth() const { return displayWidth; }
    int GetDisplayHeight() const { return displayHeight; }
    float GetDisplayAspect() const { return (float)displayWidth/displayHeight; }
    
    ShaderManager *GetShaderMgr() {
        return &shaderManager;
    }
    
    TextureManager *GetTextureMgr() {
        return &textureManager;
    }
    
    CTexture *GetTexture(std::string name) const {
        return textureManager.GetTexture(name);
    }
    
};

/**
 *  GAMECORE_INSTANCEが定義されていればstatic変数の定義をする。
 */
#if defined(GAMECORE_INSTANCE)
GameCore GameCore::core;
#endif  // GAMECORE_INSTANCE

#endif
