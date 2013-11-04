//
//  FBO.h
//  KMLib
//
//  Created by 木村 裕作 on 2013/10/18.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef __KMLib__FBO__
#define __KMLib__FBO__
#include "_useGL.h"
#include "Texture.h"

namespace KMLib {
    
    class FBO {
        GLuint fbID, rboID;
        CTexture *tex;
        
        unsigned width, height;
    public:
        
        // コンストラクタ
        FBO(unsigned _width, unsigned _height, bool color=true, bool depth=true, bool stencil=false);
        
        // デストラクタ
        ~FBO();
        
        void Bind();
        void Unbind();
        
        CTexture *GetTexture() {
            return tex;
        }
    };
    
}

#endif /* defined(__KMLib__FBO__) */
