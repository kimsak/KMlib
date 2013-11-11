//
//  CSprite.mm
//  iOS_Sample2
//
//  Created by 木村 裕作 on 2013/04/07.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//
#include "_useGL.h"
#include "Sprite.h"
#include "Shader.h"
#include "Texture.h"

/**
 *  シェーダーのソースデータ（頂点シェーダー）
 */
static const char vertex_src[] =
"attribute vec4 position;"
"attribute vec2 texcoord;"

"varying vec4 colorVarying;"
"varying vec2 texCoord0;"

"uniform vec4 monoColor;"
"uniform mat4 modelViewProjectionMatrix;"

"uniform mat4 texMatrix;"

"void main() {"
"  colorVarying = monoColor;"
"  gl_Position = modelViewProjectionMatrix * position;"
"  vec4 texcoordVec4 = vec4(texcoord, 0, 1);"
"  texcoordVec4 = texMatrix * texcoordVec4;"
"  texCoord0 = texcoordVec4.xy;"
"}";

/**
 *  シェーダーのソースデータ（フラグメントシェーダー）
 */
static const char fragment_src[] =
"varying vec4 colorVarying;"
"varying vec2 texCoord0;"

"uniform sampler2D sampler;"

"void main() {"
"  vec2 n_texcoord = texCoord0;"
"  n_texcoord.y = 1.0 - texCoord0.y;"
"  if(colorVarying.w > 0.0) gl_FragColor = colorVarying * texture2D(sampler, n_texcoord);"
"  else discard;"
"}";

// 頂点データ
// 左上原点
static float points[] = {
//	-1, -1, 0,
//	1, -1, 0,
//	-1, 1, 0,
//	1, 1, 0
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
/*static*/Shader *CSprite::pShader = nullptr;

/*static*/float CSprite::displayWidth = 1;
/*static*/float CSprite::displayHeight = 1;

/*static*/void CSprite::Initialize(int width, int height) {
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

/*static*/void CSprite::Fianlize() {
    // シェーダーの破棄
    if(pShader) delete pShader;
}

void CSprite::Draw(CTexture *texture) {
	if(texture==NULL) return;
//	DrawRotScl(texture, x, y, 1, 1, 0, device);
	CRectangle src, dest;
	src.SetSize(texture->GetWidth(), texture->GetHeight());
	dest.SetBounds(x, y, src.GetWidth(), src.GetHeight());
	DrawRect(texture, src, dest);
}

/**
 *	回転、伸縮の指定をしてテクスチャを描画する関数
 *	描画するテクスチャの座標は中心が基準
 */
void CSprite::DrawRotScl(CTexture *texture, float sclX, float sclY, float rad) {
	if(!texture || !pShader) return;
	
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
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetID());
	
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
	glBindTexture(GL_TEXTURE_2D, 0);
	
	/**
	 *	頂点座標の対応付けを解除する。
	 */
    pShader->DisableAttribArray("texcoord");
    pShader->DisableAttribArray("position");
	
	/**
	 *	シェーダーの解除
	 */
	pShader->Unbind();
}

/**
 *	矩形オブジェクトを使って描画領域とテクスチャの描画範囲を指定し描画する関数
 *	矩形の座標は左上が基準
 */
void CSprite::DrawRect(CTexture *texture, const CRectangle &srcRect, const CRectangle &destRect) {
	if(!texture || !pShader) return;
	
	/**
	 *	シェーダーの設定
	 */
	pShader->Bind();
	
	/**
	 *	Atrribute変数の設定
	 */
    // position
    pShader->SetAttribf("position", 3, GL_FALSE, 3, points);
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
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetID());
	
	// modelViewProjectionMatrix
	// 行列変換
//	CMatrix4 mvpMat = CMatrix4::Translation(CVector(1, -1, 0));
	CMatrix4 mvpMat;
	mvpMat *= CMatrix4::Scale(Vector3(destRect.GetWidth()/2.0f, destRect.GetHeight()/2.0f, 1));
//	mvpMat *= CMatrix4::Rotation(CQuaternion(rad/(2*GL_PI), CVector(0, 0, 1)));
	mvpMat *= CMatrix4::Translation(Vector3(-displayWidth/2.0f+destRect.GetX(), displayHeight/2.0f-destRect.GetY(), 0));
	mvpMat *= CMatrix4::LookAt(Vector3(0, 0, 10), Vector3(), Vector3(0, 1, 0));
	mvpMat *= CMatrix4::Orthof(-displayWidth/2.0f, displayWidth/2.0f, displayHeight/2.0f, -displayHeight/2.0f, 1, 100);
	
    pShader->SetUniform("modelViewProjectionMatrix", mvpMat);
	
	// texMatrix
	CMatrix4 tmMat = CMatrix4::Scale(Vector3(srcRect.GetWidth()/texture->GetWidth(), srcRect.GetHeight()/texture->GetHeight(), 1));
	tmMat *= CMatrix4::Translation(Vector3(srcRect.GetX()/texture->GetWidth(), srcRect.GetHeight()/texture->GetHeight(), 0));
    pShader->SetUniform("texMatrix", tmMat);
	
	/**
	 *	描画
	 */
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	// テクスチャの解除
	glBindTexture(GL_TEXTURE_2D, 0);
	
    /**
	 *	頂点座標の対応付けを解除する。
	 */
    pShader->DisableAttribArray("texcoord");
    pShader->DisableAttribArray("position");

    
	/**
	 *	シェーダーの解除
	 */
	pShader->Unbind();
}
