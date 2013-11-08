//
//  Shader.mm
//  KandataGame
//
//  Created by 木村 裕作 on 2013/10/10.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#include "Shader.h"
#include <stdio.h>

#define LOG_BUF_SIZE    (2048)

/*static*/GLuint Shader::CompileShader(GLenum shader_type, const char *filename, const char *srcData) {
    GLint compileResult;
    
    // シェーダーオブジェクトの作成
    GLuint shaderID = glCreateShader(shader_type);
    
    // シェーダーオブジェクトに読み込む
    glShaderSource(shaderID, 1, (const GLchar **)&srcData, NULL);
    // シェーダーオブジェクトのコンパイル
    glCompileShader(shaderID);
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult);
    
    //	printShaderInfoLog(shaderID);		// コンパイルログの出力
    if(compileResult==GL_FALSE) {
        fprintf(stderr, "Compile Error! --> %s\n", filename);
        // ログの出力
        {
        int length = 0, logSize = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logSize);
        if(logSize>1) {
            char buf[LOG_BUF_SIZE];
            glGetShaderInfoLog(shaderID, LOG_BUF_SIZE, &length, buf);
            fprintf(stderr, "%s\n", buf);
        }
        }
        glDeleteShader(shaderID);
        return 0;
    }
    
    return shaderID;
}

/*static*/Shader *Shader::Create(TextSrcDataRef vertexRef, TextSrcDataRef fragRef) {
    GLuint vtxID, frgID;
    GLint pgLink;
    
    // 各ソースのコンパイル
    // 頂点シェーダー
    if( !(vtxID = CompileShader(GL_VERTEX_SHADER, vertexRef->GetFilename(), vertexRef->GetContents())) )
        return nullptr;
    // フラグメントシェーダー
    if( !(frgID = CompileShader(GL_FRAGMENT_SHADER, fragRef->GetFilename(), fragRef->GetContents())) ) {
        glDeleteShader(vtxID);
        return nullptr;
    }
    
    //
    // リンク処理
    Shader *pShader = new Shader;
    // オブジェクトの関連付け
    glAttachShader(pShader->programID, vtxID);
    glAttachShader(pShader->programID, frgID);
    // リンク処理
    glLinkProgram(pShader->programID);
    glGetProgramiv(pShader->programID, GL_LINK_STATUS, &pgLink);
    if(pgLink == GL_FALSE) {
        fprintf(stderr, "Link Error! --> %s, %s\n", vertexRef->GetFilename(), fragRef->GetFilename());
        {   // ログ出力
            int length = 0, logSize = 0;
            glGetProgramiv(pShader->programID, GL_INFO_LOG_LENGTH, &logSize);
            if( logSize > 1 ) {
                char buf[ LOG_BUF_SIZE ];
                glGetProgramInfoLog(pShader->programID, LOG_BUF_SIZE, &length, buf);
                fprintf(stderr, "%s\n", buf);
            }
        }
        delete pShader;
        return nullptr;
    }
    
    return pShader;
}

/**
 *  コンストラクタ
 */
Shader::Shader() : programID( glCreateProgram() ) {
}

/**
 *  デストラクタ
 */
Shader::~Shader() {
    if (programID != 0) {
        glDeleteProgram(programID);
    }
}

/**
 *  シェーダーのバインド
 */
void Shader::Bind() const {
    glUseProgram(programID);
}

/**
 *  シェーダーのアンバインド
 */
void Shader::Unbind() {
    if(glIsProgram(programID) == GL_TRUE) glUseProgram(0);
}

// ==============================
// Attribute

void Shader::SetAttribi(const std::string &name, GLint size, GLboolean normalized, GLsizei stride, const GLint *pointer) {
    GLuint loc = glGetAttribLocation(programID, name.c_str());
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, size, GL_INT, normalized, sizeof(int)*stride, pointer);
}

void Shader::SetAttribf(const std::string &name, GLint size, GLboolean normalized, GLsizei stride, const GLfloat *pointer) {
    GLuint loc = glGetAttribLocation(programID, name.c_str());
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, size, GL_FLOAT, normalized, sizeof(float)*stride, pointer);
}

void Shader::DisableAttribArray(const std::string &name) {
    GLuint loc = glGetAttribLocation(programID, name.c_str());
    glDisableVertexAttribArray(loc);
}

// ==============================
// Uniform

void Shader::SetUniform(const std::string &name, int data) {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    glUniform1i(loc, data);
}

void Shader::SetUniform(const std::string &name, float data) {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    glUniform1f(loc, data);
}

void Shader::SetUniform(const std::string &name, const int *data_array, int count) {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    glUniform1iv(loc, count, data_array);
}

void Shader::SetUniform(const std::string &name, const float *data_array, int count) {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    glUniform1fv(loc, count, data_array);
}

void Shader::SetUniform(const std::string &name, const Vector2 &data) {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    glUniform2f(loc, data.X, data.Y);
}

void Shader::SetUniform(const std::string &name, const Vector3 &data) {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    glUniform3f(loc, data.X, data.Y, data.Z);
}

void Shader::SetUniform(const std::string &name, const CMatrix4 &data) {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat *)&data);
}

void Shader::SetUniform(const std::string &name, const Color &color) {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    glUniform4fv(loc, 1, (const GLfloat *)&color);
}
