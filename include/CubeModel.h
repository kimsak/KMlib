//
//  CubeModel.h
//  KandataGame
//
//  Created by 木村 裕作 on 2013/08/01.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef CUBE_MODEL_H_
#define CUBE_MODEL_H_

#include "AbstractModel.h"

class CubeModel : public AbstractModel {
public:
    virtual void Render() override;
    
    virtual void SetAttrPos(Shader *pShader, const std::string &name) override;
    virtual void SetAttrNorm(Shader *pShader, const std::string &name) override;
};

#endif /* defined(__KandataGame__CubeModel__) */
