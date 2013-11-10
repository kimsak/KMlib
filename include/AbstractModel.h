//
//  AbstractModel.h
//  KandataGame
//
//  Created by 木村 裕作 on 2013/07/30.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef ABSTRACT_MODEL_H_
#define ABSTRACT_MODEL_H_
#include "Component.h"

class Game3DObject;

class AbstractModel : public IComponent {
public:
    // デストラクタ
    virtual ~AbstractModel() {}
    
    virtual void Render(const Game3DObject *) = 0;
};

#endif  /*defined(ABSTRACT_MODEL_H_)*/
