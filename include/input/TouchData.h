//
//  TouchData.h
//  KMlib
//
//  Created by 木村 裕作 on 2013/11/17.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef KMlib_TouchData_h
#define KMlib_TouchData_h
#include "KMMath.h"

enum KMTouchPhase {
    KMTouchDefault,
    KMTouchBegan,
    KMTouchMoved,
    KMTouchStationary,
    KMTouchEnded,
    KMTouchCancelled,
};

class TouchData {
    Vector2         currPos;
    Vector2         prevPos;
    KMTouchPhase    phase;
    double          timeStamp;
    int             tapCount;
    
    // 初期化
    void Initialize();
public:
    // コンストラクタ
    TouchData() :
    currPos(),
    prevPos(),
    phase(KMTouchDefault),
    timeStamp(0.0),
    tapCount(0)
    {}
    
    // Setter
    void SetCurrPos(const Vector2 &pos);
    void SetPrevPos(const Vector2 &pos);
    void SetPhase(KMTouchPhase _phase);
    void SetTimeStamp(double _time_stamp);
    void SetTapCount(int count);
    
    // Getter
    Vector2 GetCurrPos() const      { return currPos; }
    Vector2 GetPrevPos() const      { return prevPos; }
    KMTouchPhase GetPhase() const;
    double GetTimeStamp() const     { return timeStamp; }
    int GetTapCount() const         { return tapCount; }
};

#endif
