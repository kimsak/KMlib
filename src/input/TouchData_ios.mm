//
//  TouchData_ios.mm
//  KMlib
//
//  Created by 木村 裕作 on 2013/11/17.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#include "TouchData.h"
#ifdef __APPLE__

#if defined(IOS_BUILD)
#import <UIKit/UIKit.h>
#endif  // IOS_BUILD

static void AdjustPositionByOrientation(Vector2 *pPos, UIInterfaceOrientation orient) {
    float tmpX = pPos->X, tmpY = pPos->Y;
    // デバイスの幅高さを取得
    CGRect screenRect = [UIScreen mainScreen].bounds;
    
    switch (orient) {
        case UIInterfaceOrientationPortraitUpsideDown:
            pPos->X = screenRect.size.width - tmpX;
            pPos->Y = screenRect.size.height - tmpY;
            break;
        case UIInterfaceOrientationLandscapeRight:
            pPos->X = tmpY;
            pPos->Y = screenRect.size.width - tmpX;
            break;
        case UIInterfaceOrientationLandscapeLeft:
            pPos->X = screenRect.size.height - tmpY;
            pPos->Y = tmpX;
            break;
        default:
            break;
    }
}

void TouchData::Initialize() {
    // スクリーンの種類(Retina)、向きに応じてセンシングデータを変換する作業を行う
    // 画面の向きを取得する
    UIInterfaceOrientation orient = [UIApplication sharedApplication].statusBarOrientation;
    // Retina対応かスケールの取得
    float scale = [UIScreen mainScreen].scale;
    
    currPos.X *= scale, currPos.Y *= scale;
    AdjustPositionByOrientation(&currPos, orient);
    prevPos.X *= scale, prevPos.Y *= scale;
    AdjustPositionByOrientation(&prevPos, orient);
}

void TouchData::SetCurrPos(const Vector2 &pos) {
    // スクリーンの種類(Retina)、向きに応じてセンシングデータを変換する作業を行う
    // 画面の向きを取得する
    UIInterfaceOrientation orient = [UIApplication sharedApplication].statusBarOrientation;
    // Retina対応かスケールの取得
    float scale = [UIScreen mainScreen].scale;
    
    currPos = scale * pos;
    AdjustPositionByOrientation(&currPos, orient);
}

void TouchData::SetPrevPos(const Vector2 &pos) {
    // スクリーンの種類(Retina)、向きに応じてセンシングデータを変換する作業を行う
    // 画面の向きを取得する
    UIInterfaceOrientation orient = [UIApplication sharedApplication].statusBarOrientation;
    // Retina対応かスケールの取得
    float scale = [UIScreen mainScreen].scale;
    
    prevPos = scale * pos;
    AdjustPositionByOrientation(&prevPos, orient);
}

void TouchData::SetPhase(KMTouchPhase _phase) {
    phase = _phase;
}

void TouchData::SetTimeStamp(double _time_stamp) {
    timeStamp = _time_stamp;
}

void TouchData::SetTapCount(int count) {
    tapCount = count;
}


KMTouchPhase TouchData::GetPhase() const {
    switch(phase) {
        case UITouchPhaseBegan:
            return KMTouchBegan;
        case UITouchPhaseMoved:
            return KMTouchMoved;
        case UITouchPhaseStationary:
            return KMTouchStationary;
        case UITouchPhaseEnded:
            return KMTouchEnded;
        case UITouchPhaseCancelled:
            return KMTouchCancelled;
        default:
            return KMTouchDefault;
    }
}


#endif  // __APPLE__
