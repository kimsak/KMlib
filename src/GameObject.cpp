//
//  GameObject.mm
//  KandataGame
//
//  Created by 木村 裕作 on 2013/08/12.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#include "GameObject.h"

GameObject *GameObject::SearchObj(std::string name) {
    if( name == GetName() ) {
        return this;
    }
    else {
        for (GameObjList::const_iterator it = objChildren.begin(); it != objChildren.end(); ++it) {
            GameObject *pObj = (*it)->SearchObj(name);
            if(pObj) return pObj;
        }
    }
    return NULL;
}

GameObject *GameObject::RegisterChildObj(GameObject *pObj) {
    if(pObj) {
        pObj->Init();   // オブジェクトの初期化
        objChildren.push_back(pObj);
        
        return pObj;
    }
    return NULL;
}

bool GameObject::UpdateObj() {
    // 自身のオブジェクトを更新
    if(obj_state == ACTIVE) this->Move();
    
    // 子オブジェクトの更新
    for (GameObjList::iterator it = objChildren.begin(); it != objChildren.end(); ) {
        if ( (*it)->UpdateObj() == false ) {
            // オブジェクトの終了前処理
            (*it)->Term();
            
            // 子オブジェクトの中身を親が引き継ぐ
            UnderTake(*it);
            
            // リストから排除し、自身も解放
            delete *it;
            it = objChildren.erase(it);
            continue;
        }
        ++it;
    }
    
    return obj_state != DEAD;       // オブジェクトの状態がDEADでは無ければtrueを返すようにする。
}

bool GameObject::DrawObj() {
    // 子オブジェクトの描画
    for (GameObjList::const_iterator it = objChildren.begin(); it != objChildren.end(); ++it) {
        (*it)->DrawObj();
    }
    
    // 自身のオブジェクトの描画
    if(obj_state == ACTIVE) this->Draw();
    
    return true;
}

void GameObject::UnderTake(GameObject *pObj) {
    // 子オブジェクトリストの中身をコピーする
    for (GameObjList::iterator it = pObj->objChildren.begin(); it != pObj->objChildren.end(); ++it) {
        objChildren.push_back(*it);
    }
    
    // コピー元のオブジェクトリストを空にする
    pObj->objChildren.clear();
}

void GameObject::DestroyChildAll() {
    for (GameObjList::const_iterator it = objChildren.begin(); it != objChildren.end(); ++it) {
        (*it)->DestroyChildAll();
        (*it)->Term();      // オブジェクトの終了前処理
        delete *it;
    }
    objChildren.clear();
}
