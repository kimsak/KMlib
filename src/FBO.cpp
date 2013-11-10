//
//  FBO.cpp
//  KMLib
//
//  Created by 木村 裕作 on 2013/10/18.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#include "FBO.h"

using namespace KMLib;

/**
 *  コンストラクタ
 */
FBO::FBO(unsigned _width, unsigned _height, bool color, bool depth, bool stencil) :
width(_width),
height(_height),
tex(nullptr),
fbID(0),
rboID(0)
{
    // 深度テクスチャの作成
    if(depth) {
        // テクスチャの設定
        tex = new CTexture(width, height);
        tex->Bind();
        
        // 深度バッファテクスチャの割り当て
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#if defined (IOS_BUILD)     // iOS
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#else                       // Mac OS X
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
#endif
        tex->Unbind();
    }
    
    /**
     *  カラーバッファの作成
     */
    if(color) {
        // カラーレンダーバッファの作成
        glGenRenderbuffers(1, &rboID);
        glBindRenderbuffer(GL_RENDERBUFFER, rboID);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }
    
    
    // フレームバッファの作成
    glGenFramebuffers(1, &fbID);
    Bind();
    
    // フレームバッファとの結合
    if(tex)         glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex->GetID(), 0);
    if(rboID > 0)   glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rboID);
    
    // カラーバッファの読み書き無効
//    glDrawBuffer(GL_NONE);
//    glReadBuffer(GL_NONE);
    
    Unbind();
    tex->Unbind();
}

/**
 *  デストラクタ
 */
FBO::~FBO() {
    if(tex) delete tex, tex = nullptr;
    if(rboID) glDeleteRenderbuffers(1, &rboID);
    if(fbID) glDeleteFramebuffers(1, &fbID);
}

void FBO::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbID);
}

void FBO::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

