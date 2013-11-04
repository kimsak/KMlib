//
//  TextSrcData_objc.mm
//  KandataGame
//
//  Created by 木村 裕作 on 2013/08/04.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#include <cstring>
#include "TextSrcData.h"

/**
 *  iOS用のImageDataクラスの定義
 */
#ifdef __APPLE__
#include <Foundation/NSString.h>
#include <Foundation/NSBundle.h>

/*static*/
TextSrcDataRef TextSrcData::LoadContentFromFile(const char *filename, const char *extension_name) {
    if(!filename || !extension_name) return nullptr;
    
    // テキストデータクラスを作成する
    TextSrcDataRef textDataRef( new TextSrcData );
    
    // それぞれの文字列をNSStringの形式に変換
    NSString
        *ns_filename = [NSString stringWithCString:filename encoding:NSUTF8StringEncoding],
        *ns_extension_name = [NSString stringWithCString:extension_name encoding:NSUTF8StringEncoding];
    
    // ファイルパスの抽出(取得できなかったときはfalseで返す)
    NSString *ns_filepath = [[NSBundle mainBundle] pathForResource:ns_filename ofType:ns_extension_name];
    if(ns_filepath == nil) return nullptr;
    
    // テキストデータの抽出
    NSString *ns_src_data = [NSString stringWithContentsOfFile:ns_filepath encoding:NSUTF8StringEncoding error:nil];
    
    // 中身のデータをchar *で取得
    const char *src_data = [ns_src_data UTF8String];
    // 文字列の長さを取得
    size_t src_data_length = strlen(src_data);
    size_t filename_length = strlen(filename);
    
    /**
     *  ソースデータのコピー
     */
    // メモリ確保
    textDataRef->pSrcChars = new char[src_data_length + 1];
    textDataRef->filename = new char[filename_length + 1];
    // コピー
    strncpy(textDataRef->pSrcChars, src_data, src_data_length+1);
    strncpy(textDataRef->filename, filename, filename_length+1);
    
    return textDataRef;
}

#endif  // __APPLE__
