//
//  ShaderManager.h
//  KandataGame
//
//  Created by 木村 裕作 on 2013/06/22.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef SHADER_MANAGER_H_
#define SHADER_MANAGER_H_
#include <map>
#include <string>
#include "_useGL.h"
#include "Math.h"
#include "Shader.h"

class ShaderManager {
    std::map<std::string, Shader *> shaders;
public:
    /**
     *  シェーダーを作成する関数
     */
    bool CreateShader(const std::string &name, const std::string &vertexSrcPath, const std::string &fragmentSrcPath);
    
    Shader *GetShader(const std::string &name);
    
    /**
     *  登録されているシェーダーの破棄
     */
    void Dispose();
    
    // デストラクタ
    ~ShaderManager() {
        Dispose();
    }
};

#endif /* defined(SHADER_MANAGER_H_) */
