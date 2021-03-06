//
//  Sprite.h
//  iOS_Sample2
//
//  Created by 木村 裕作 on 2013/04/07.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef SPRITE_H_
#define SPRITE_H_
#include "Color.h"
#include "KMMath.h"

class CTexture;
class Shader;

class Sprite {
    static Shader *pShader;
    static float displayWidth, displayHeight;
    
    // インスタンス変数
    float       x;
    float       y;
    Color       color;
    CRectangle  srcRect;
public:
    /**
     *  スプライトクラスの初期化処理
     *  @param width ディスプレイの幅
     *  @param height ディスプレイの高さ
     */
    static void Initialize(int width, int height);
    
    /**
     *  終了前処理
     */
    static void Fianlize();
    
    /**
     *  コンストラクタ
     */
    Sprite(float _x, float _y, const Color &_color) : x(_x), y(_y), color(_color), srcRect() {}
    
    void SetSrcRect(float _x, float _y, float _w, float _h) {
        srcRect.SetBounds(_x, _y, _w, _h);
    }
	
    /**
     *  スプライト描画関数
     *  @param x 描画位置(x座標)
     *  @param y 描画位置(y座標)
     *  @param sclX 描画するスプライトの伸縮倍率(x方向)
     *  @param sclY 描画するスプライトの伸縮倍率(y方向)
     */
	void DrawRotScl(CTexture *texture, float sclX, float sclY, float rad);
    
};

#endif // SPRITE_H_
