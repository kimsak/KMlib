//
//  AbstractObject.h
//  KandataGame
//
//  Created by 木村 裕作 on 2013/08/12.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef ABSTRACT_OBJECT_H_
#define ABSTRACT_OBJECT_H_
#include <string>
#define NO_NAME     "No Name"

class AbstractObject {
    std::string name;
public:
    // コンストラクタ
    AbstractObject() : name(NO_NAME) {}
    
    // デストラクタ
    virtual ~AbstractObject() {}
    
    virtual void Init() = 0;
    virtual void Move() = 0;
    virtual void Draw() = 0;
    virtual void Term() = 0;
    
    virtual AbstractObject *SetName(std::string name) {
        this->name = name;
        return this;
    }
    
    virtual std::string GetName() const {
        return name;
    }
};

#endif
