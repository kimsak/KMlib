//
//  SphereModel.h
//  KMLib
//
//  Created by 木村 裕作 on 2013/10/26.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef __KMLib__SphereModel__
#define __KMLib__SphereModel__

#include "AbstractModel.h"

// 定数定義
#define USE_SHADER_NAME     ("Basic3D")
#define DEFAULT_SEGMENT     (16)

class SphereModel : public AbstractModel {
    int segments;
public:
    // コンストラクタ
    SphereModel(int seg) : segments(seg) {
        if(segments <= 1) segments = DEFAULT_SEGMENT;
    }
    SphereModel() : segments(DEFAULT_SEGMENT) {}
    
    virtual void Render(const Game3DObject *) override;
    
};

#endif /* defined(__KMLib__SphereModel__) */
