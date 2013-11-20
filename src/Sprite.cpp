//
//  CSprite.mm
//  iOS_Sample2
//
//  Created by 木村 裕作 on 2013/04/07.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//
#include "_useGL.h"
#include "Sprite.h"
#include "Texture.h"
#include "Shader.h"

/**
 *  シェーダーのソースデータ（頂点シェーダー）
 */
static const char vertex_src[] =
"attribute vec4 position;\n"
"attribute vec2 texcoord;\n"

#if defined (IOS_BUILD)
"varying mediump vec4 outColor;\n"
"varying mediump vec2 texCoord0;\n"
#else
"varying vec4 outColor;\n"
"varying vec2 texCoord0;\n"
#endif

"uniform vec4 monoColor;\n"
"uniform mat4 modelViewProjectionMatrix;\n"

"uniform mat4 texMatrix;\n"

"void main() {\n"
"  outColor = monoColor;\n"
"  gl_Position = modelViewProjectionMatrix * position;\n"
"  vec4 texcoordVec4 = vec4(texcoord, 0, 1);\n"
"  texcoordVec4 = texMatrix * texcoordVec4;\n"
"  texCoord0 = texcoordVec4.xy;\n"
"}\n";

/**
 *  シェーダーのソースデータ（フラグメントシェーダー）
 */
static const char fragment_src[] =
#if defined (IOS_BUILD)
"varying mediump vec4 outColor;\n"
"varying mediump vec2 texCoord0;\n"
#else
"varying vec4 outColor;\n"
"varying vec2 texCoord0;\n"
#endif

"uniform sampler2D sampler;\n"

"void main() {\n"
"  if(outColor.w > 0.0) gl_FragColor = outColor * texture2D(sampler, texCoord0);\n"
"  else discard;\n"
"}\n";

// 頂点データ
// 左上原点
static float points[] = {
	0, -1, 0,
	1, -1, 0,
	0, 0, 0,
	1, 0, 0
};

// 頂点データ（別）
// 原点中心
static float points2[] = {
    -1, -1, 0,
    1, -1, 0,
    -1, 1, 0,
    1, 1, 0
};

// UV座標
static float tex_coords[] = {
	0, 1,
	1, 1,
	0, 0,
	1, 0
};

// 専用シェーダー
/*static*/Shader *Sprite::pShader = nullptr;

/*static*/float Sprite::displayWidth = 1;
/*static*/float Sprite::displayHeight = 1;

/*static*/void Sprite::Initialize(int width, int height) {
    /**
     *  ディスプレイの設定
     */
    displayWidth = (float)width, displayHeight = (float)height;
    
    /**
     *  専用シェーダーの作成
     */
    if(pShader == nullptr) {
        // シェーダーの読込
        pShader = Shader::Create(vertex_src, fragment_src);
    }

}

/*static*/void Sprite::Fianlize() {
    // シェーダーの破棄
    if(pShader) delete pShader, pShader = nullptr;
}

/**
 *	回転、伸縮の指定をしてテクスチャを描画する関数
 *	描画するテクスチャの座標は中心が基準
 */
void Sprite::DrawRotScl(CTexture *texture, float sclX, float sclY, float rad) {
	if(!texture || !pShader) return;
    
    // 現在のシェーダープログラムの保存
    int currprogram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currprogram);
	
	/**
	 *	シェーダーの設定
	 */
	pShader->Bind();
	
	/**
	 *	Atrribute変数の設定
	 */
	// position
    pShader->SetAttribf("position", 3, GL_FALSE, 3, points2);
	// texcoord
    pShader->SetAttribf("texcoord", 2, GL_FALSE, 2, tex_coords);
	
	/**
	 *	Uniform変数の設定
	 */
	// monoColor
//	float color[] = {1,1,1,1};
    pShader->SetUniform("monoColor", color);
	
	// sampler
    pShader->SetUniform("sampler", 0);
	
	// テクスチャの設定
	texture->Bind(0);
	
	// modelViewProjectionMatrix
	// 行列変換
    
    // 変換行列の設定
    float t_x = sclX * texture->GetOriginalW() / 2 - displayWidth / 2 + x,
        t_y = -sclY * texture->GetOriginalH() / 2 + displayHeight / 2 - y;
    
	CMatrix4 mvpMat;
    mvpMat[0] = sclX * texture->GetOriginalW() * cosf(rad) / displayWidth;
    mvpMat[1] = -sclX * texture->GetOriginalW() * sinf(rad) / displayHeight;
    mvpMat[4] = sclY * texture->GetOriginalH() * sinf(rad) / displayWidth;
    mvpMat[5] = sclY * texture->GetOriginalH() * cosf(rad) / displayHeight;
    mvpMat[12] = 2 * t_x / displayWidth;
    mvpMat[13] = 2 * t_y / displayHeight;
	
    pShader->SetUniform("modelViewProjectionMatrix", mvpMat);
	
	// texMatrix
    float   sw = (float)texture->GetOriginalW()/texture->GetWidth(),
            sh = (float)texture->GetOriginalH()/texture->GetHeight();
	CMatrix4 tmMat = CMatrix4::Scale(Vector3(sw, sh, 1));
    tmMat *= CMatrix4::Translation(Vector3(srcRect.GetX(), srcRect.GetY(), 0));
    pShader->SetUniform("texMatrix", tmMat);
	
	/**
	 *	描画
	 */
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	// テクスチャの解除
	texture->Unbind();
	
	/**
	 *	頂点座標の対応付けを解除する。
	 */
    pShader->DisableAttribArray("texcoord");
    pShader->DisableAttribArray("position");
	
	/**
	 *	シェーダーの解除（もとに戻す）
	 */
	glUseProgram(currprogram);
}

