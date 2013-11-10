//
//  GameObject.h
//  iOSSample4
//
//  Created by 木村 裕作 on 2013/05/22.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_
#include "GameCore.h"
#include "AbstractObject.h"
#include "Component.h"
#include <list>

class GameObject;
typedef std::list<GameObject *> GameObjList;

class GameObject : public AbstractObject {
    GameCore *pGame;
    
    // 汎用辞書変数
    std::map<std::string, IComponent *> propertyTable;
    
protected:
    // 子オブジェクトリスト
    GameObjList objChildren;
    
public:
    enum ObjState {
        DEAD = -1, ACTIVE = 0, NOT_ACTIVE = 1,
    };
    ObjState obj_state;
    
    // コンストラクタ
    GameObject(GameCore *gamePtr) : AbstractObject(), pGame(gamePtr), obj_state(ACTIVE) {}
    virtual ~GameObject() {}
    
    // @Override
    virtual void Init() {}
    // @Override
    virtual void Move() {}
    // @Override
    virtual void Draw() {}
    // @Override
    virtual void Term() {}
    
    // @Override
    virtual GameObject *SetName(std::string name) {
        AbstractObject::SetName(name);
        return this;
    }
    
    /**
     *  オブジェクトの検索
     */
    virtual GameObject *SearchObj(std::string name);
    
    // 子オブジェクトリストに新しいオブジェクトを登録
    virtual GameObject *RegisterChildObj(GameObject *pObj);
    
    virtual bool UpdateObj();
    virtual bool DrawObj();
    
    /**
     *  指定したオブジェクトの持つ子オブジェクトたちを引き継いで自身の子オブジェクトリストに追加していく。
     *  @param pObj 引き継ぐオブジェクトたちの親オブジェクト
     */
    void UnderTake(GameObject *pObj);
    
    // 子オブジェクトを再帰的に破壊する
    void DestroyChildAll();
    
    GameCore *Get_pGame() const {
        return pGame;
    }
    
    /**
     *  プロパティの設定
     *  @param name     プロパティの名前（キー）
     *  @param pValue   プロパティの値
     */
    void SetValue(std::string name, IComponent *pValue) {
        if(pValue) propertyTable[name] = pValue;
    }
    
    // プロパティの取得
    IComponent *GetValue(std::string name) const {
        std::map<std::string, IComponent *>::const_iterator it = propertyTable.find(name);
        return it != propertyTable.end() ? it->second : NULL;
    }
};

#endif /*GAME_OBJECT_H_*/
