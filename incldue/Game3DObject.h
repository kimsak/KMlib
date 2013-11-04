//
//  Game3DObject.h
//
//  Created by 木村 裕作 on 2013/05/22.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef GAME_3D_OBJECT
#define GAME_3D_OBJECT
#include "GameObject.h"
#include "KMMath.h"
#include "Color.h"
#include <string>
#include <map>

#define MODEL_PROPERTY      "Model"

class Game3DObject : public GameObject {
public:
    CVector         position;
    CVector         scale;
    CQuaternion     rotation;
    
    Color           color;
    
    /**
     *  コンストラクタ
     */
    Game3DObject(GameCore *gamePtr) : GameObject(gamePtr), position(), scale(1,1,1), rotation(), color() {}
};

#endif /*GAME_3D_OBJECT*/
