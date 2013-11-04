//
//  ShaderManager.mm
//  KandataGame
//
//  Created by 木村 裕作 on 2013/06/22.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#include "ShaderManager.h"
#include "TextSrcData.h"

const int LOG_BUF_SIZE = 2048;

// シェーダーの作成
bool ShaderManager::CreateShader(const std::string &name, const std::string &vertexSrcPath, const std::string &fragmentSrcPath) {
    // 入力した名前がすでに存在してるかどうか調べる。
    // 登録されていたらfalseを返す。
    if( GetShader(name) ) return false;
    
    // ソースの中身を読み込む
    TextSrcDataRef vsh_dataRef, fsh_dataRef;
    if( (vsh_dataRef = TextSrcData::LoadContentFromFile(vertexSrcPath.c_str(), "vsh")) == nullptr ||
       (fsh_dataRef = TextSrcData::LoadContentFromFile(fragmentSrcPath.c_str(), "fsh")) == nullptr)
       return false;
    
//    const char *vSrcData, *fSrcData;
//    if( !::LoadSourceData(vertexSrcPath.c_str(), fragmentSrcPath.c_str(), &vSrcData, &fSrcData)) {
//        return false;
//    }
    
    // シェーダーをビルドする
    Shader *pShader = nullptr;
    if ( !(pShader = Shader::Create(vsh_dataRef, fsh_dataRef)) ) {
        return false;
    }
    
    // シェーダーの登録
    shaders[name] = pShader;
    
    return true;
}

Shader *ShaderManager::GetShader(const std::string &name) {
    return shaders.find(name) != shaders.end() ? shaders[name] : nullptr;
}

// シェーダーの全破棄
void ShaderManager::Dispose() {
    for (auto it=shaders.begin(); it!=shaders.end(); it++) {
        delete it->second;
    }
    shaders.clear();
}

