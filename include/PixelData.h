//
//  PixelData.h
//  KandataGame
//
//  Created by 木村 裕作 on 2013/06/24.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef PIXEL_DATA_H_
#define PIXEL_DATA_H_

struct ImageData;

class PixelData {
    ImageData *pData;
public:
    static bool LoadAndCopyPixelData(const char *, const char *, PixelData *pPixelData);
    
    static bool ResizePixelData(const PixelData *pSrcPixels, int *pWidth, int *pHeight, unsigned char **ppPixels);
    
    PixelData();
    ~PixelData();
    
    int GetWidth() const;
    int GetHeight() const;
    const unsigned char *GetPixels() const;
};

#endif /*defined(PIXEL_DATA_H_)*/
