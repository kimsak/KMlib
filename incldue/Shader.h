//
//  Shader.h
//  KandataGame
//
//  Created by 木村 裕作 on 2013/10/10.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef SHADER_H_
#define SHADER_H_

#include "_useGL.h"
#include "KMMath.h"
#include "Color.h"
#include "TextSrcData.h"
#include <memory>
#include <string>

class Shader {
    GLuint  programID;
    
public:
    // コンストラクタ
    Shader();
    
    // デストラクタ
    ~Shader();
    
    // プログラムのバインド
    void Bind() const;
    
    // アンバインド
    void Unbind();
    
    void SetAttribf(const std::string &name, GLint size, GLboolean normalized, GLsizei stride, const GLfloat *pointer );
    void SetAttribi(const std::string &name, GLint size, GLboolean normalized, GLsizei stride, const GLint *pointer );
    
    void DisableAttribArray(const std::string &name);
    
    void SetUniform(const std::string &name, int data);
    void SetUniform(const std::string &name, float data);
    void SetUniform(const std::string &name, const int *data_array, int count);
    void SetUniform(const std::string &name, const float *data_array, int count);
    void SetUniform(const std::string &name, const Vector2 &data);
    void SetUniform(const std::string &name, const Vector3 &data);
    void SetUniform(const std::string &name, const CMatrix4 &data);
    void SetUniform(const std::string &name, const Color &color);
    
    static Shader *Create(TextSrcDataRef vertexRef, TextSrcDataRef fragRef);
    
    /**
     *  シェーダーのソースをコンパイルするクラス関数
     *  @return コンパイルされた状態でのシェーダーオブジェクト識別子（>0）。失敗したら0がかえってくる。
     *  @param  shader_type ソースのタイプ（VertexかFragmentか）
     *  @param  filename    ソースのファイル名
     *  @param  srcData     ソースの中身
     */
    static GLuint CompileShader(GLenum shader_type, const char *filename, const char *srcData);
};

#endif /* defined(__KandataGame__Shader__) */
