//
//  InputManager.h
//  KMlib
//
//  Created by 木村 裕作 on 2013/11/17.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef KMlib_InputManager_h
#define KMlib_InputManager_h
#include <list>
#include "TouchData.h"

class InputManager {
    //////////////////////////// Touch Data List ///////////////////////////////////////
    
    // TouchListener List
//    std::list<ITouchListener *> touchlistener_list;
    
    // InputMotionデータ
//    InputMotion motion;
    
public:
    
    // モーション管理データの参照を取得する
//    InputMotion *GetMotion() {
//        return &motion;
//    }
    
    ////////////////////////////// TouchListener //////////////////////////////////////////
    
//    // タッチリスナーを追加する
//    void AddTouchListener(ITouchListener *listener) {
//        if(listener) touchlistener_list.push_back(listener);
//    }
//    
//    // タッチリスナーをリストから削除する（リスナーを実装したオブジェクトが破棄される場合）
//    void RemoveTouchListener(ITouchListener *listener) {
//        if(listener)
//            for(auto it = touchlistener_list.begin(); it != touchlistener_list.end(); ) {
//                if(*it == listener) {
//                    touchlistener_list.erase(it);
//                    break;
//                }
//                ++it;
//            }
//    }
    
    // リスナーを実装した各オブジェクトにタッチ情報を転送する
    void ForwardTouchEvent(const TouchData &touch) {
        for (auto it = touchlistener_list.begin();
             it != touchlistener_list.end(); ++it) {
            (*it)->OnTouchAction(touch);
        }
    }
};

#endif
