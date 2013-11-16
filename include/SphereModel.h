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
#include <memory>

// 定数定義
#define DEFAULT_SEGMENT     (16)

class SphereModel : public AbstractModel {
    int segments;
    
    std::shared_ptr<float>  verts;
    std::shared_ptr<float>  normals;
    std::shared_ptr<float>  texCoords;
public:
    // コンストラクタ
    SphereModel(int seg = DEFAULT_SEGMENT);
    
    virtual void Render() override;
    
    virtual void SetAttrPos(Shader *pShader, const std::string &name) override;
    virtual void SetAttrNorm(Shader *pShader, const std::string &name) override;
};

#endif /* defined(__KMLib__SphereModel__) */
