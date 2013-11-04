//
//  PixelData.mm
//  KandataGame
//
//  Created by 木村 裕作 on 2013/08/15.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#include "PixelData.h"

/*static*/bool PixelData::ResizePixelData(const PixelData *pSrcPixels, int *pWidth, int *pHeight, unsigned char **ppPixels) {
    // 元画像の幅と高さをコピー
    const int originalW = pSrcPixels->GetWidth();
    const int originalH = pSrcPixels->GetHeight();
    
    // 幅と高さをそれぞれそれらより大きい2のべき乗の値に補正する。
    int rw = 1, rh = 1;
    for(; rw < originalW; rw <<= 1);
    for(; rh < originalH; rh <<= 1);
    *pWidth = rw;
    *pHeight = rh;
    
    // 補正後の幅高さに応じたピクセルの配列を生成する
    *ppPixels = new unsigned char[rw*rh*4];
    
    // ピクセルデータの設定
    const unsigned char *pSrcBuffer = pSrcPixels->GetPixels();    // ソース元のピクセル配列を取得
    for (int h = 0; h < rh; ++h) {
        for (int w = 0; w < rw; ++w) {
            const int index = (w + h * rw) * 4;
            // RBGAデータの設定
            bool isCopyable = w < originalW && h < originalH;   // 元画像のピクセル範囲内かどうかの判定
            (*ppPixels)[index+3] = isCopyable ? pSrcBuffer[(w+h*originalW)*4+3] : 255;  // Alpha
            (*ppPixels)[index+2] = isCopyable ? pSrcBuffer[(w+h*originalW)*4+2] : 0;    // Blue
            (*ppPixels)[index+1] = isCopyable ? pSrcBuffer[(w+h*originalW)*4+1] : 0;    // Green
            (*ppPixels)[index] = isCopyable ? pSrcBuffer[(w+h*originalW)*4] : 255;      // Red
        }
    }
    
    return true;
}
