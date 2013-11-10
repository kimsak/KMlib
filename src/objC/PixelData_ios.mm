//
//  PixelData_ios.mm
//  KMlib
//
//  Created by 木村 裕作 on 2013/11/10.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#include "PixelData.h"

/**
 *  ImageDataクラスの定義
 */
#ifdef __APPLE__
#import <UIKit/UIKit.h>

struct ImageData {
    int width, height;
    CFDataRef imageRef;
};

// 画像のピクセルデータを読み込む
/*static*/bool PixelData::LoadAndCopyPixelData(const char *filename, const char *type_name, PixelData *pPixelData) {
    // ファイルパスの取得
    NSString *ns_filename = [NSString stringWithCString:filename encoding:NSUTF8StringEncoding],
    *ns_typename = [NSString stringWithCString:type_name encoding:NSUTF8StringEncoding];
    
    NSString *ns_filepath = [[NSBundle mainBundle] pathForResource:ns_filename ofType:ns_typename];
    
    // UIImageの取得
    UIImage *image = [UIImage imageWithContentsOfFile:ns_filepath];
    
    CGImageRef imageRef = [image CGImage];
    pPixelData->pData->width = (int)CGImageGetWidth(imageRef), pPixelData->pData->height = (int)CGImageGetHeight(imageRef);
    
    // ピクセルデータの取得
    pPixelData->pData->imageRef = CGDataProviderCopyData(CGImageGetDataProvider(imageRef));
    return true;
}

// コンストラクタ
PixelData::PixelData() : pData(new ImageData) {
    pData->width = pData->height = 1;
    pData->imageRef = nil;
}

// デストラクタ
PixelData::~PixelData() {
    if(pData) {
        CFRelease(pData->imageRef);
        delete pData;
    }
}

int PixelData::GetWidth() const {
    return pData->width;
}

int PixelData::GetHeight() const {
    return pData->height;
}

const unsigned char *PixelData::GetPixels() const {
    return CFDataGetBytePtr(pData->imageRef);
}




#endif  // __APPLE__