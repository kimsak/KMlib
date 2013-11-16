//
//  BasicGame.h
//  KMlib
//
//  Created by 木村 裕作 on 2013/11/10.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef KMlib_BasicGame_h
#define KMlib_BasicGame_h

class BasicGame {
    int displayWidth, displayHeight;
public:
    /**
     *  コンストラクタ
     */
    BasicGame(int w, int h) : displayWidth(w), displayHeight(h) {}
    
    virtual void Initialize()   = 0;
    virtual void Update()       = 0;
    virtual void Draw()         = 0;
    virtual void Finalize()     = 0;
    
    void SetDisplaySize(int width, int height) {
        displayWidth = width, displayHeight = height;
    }
    
    int GetDisplayWidth() const { return displayWidth; }
    int GetDisplayHeight() const { return displayHeight; }
    float GetDisplayAspect() const { return (float)displayWidth/displayHeight; }
    
};

#endif
