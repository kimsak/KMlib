//
//  Scene.h
//  iOS_Sample2
//
//  Created by 木村 裕作 on 2013/03/30.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef SCENE_H_
#define SCENE_H_

class CScene {
public:
    // デストラクタ
    virtual ~CScene() {}
    
    // Virtual functions
    virtual void LoadContents() = 0;
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};

/**
 *  シーンクラスの初期化処理を委譲する関数（インライン）
 */
inline CScene *InitScene(CScene *scene) {
    if(scene) {
        scene->LoadContents();
        scene->Init();
    }
    return scene;
}

#endif /*SCENE_H_*/
