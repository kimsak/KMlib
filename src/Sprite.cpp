//
//  CSprite.mm
//  iOS_Sample2
//
//  Created by 木村 裕作 on 2013/04/07.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//
#include "_useGL.h"
#include "Sprite.h"
#include "Math.h"
#include "Texture.h"
#include "GameCore.h"
#include "ShaderManager.h"

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

/*static*/Shader *CSprite::pShader = nullptr;

/*static*/float CSprite::displayWidth = 1;
/*static*/float CSprite::displayHeight = 1;

/*static*/void CSprite::Initialize(GameCore *pGame) {
    /**
     *  ディスプレイの設定
     */
    displayWidth = (float)pGame->GetDisplayWidth(), displayHeight = (float)pGame->GetDisplayHeight();
    
    /**
     *  専用シェーダーの作成
     */
    LoadShader(pGame);

}

/*static*/void CSprite::Fianlize() {
    
}

/*static*/void CSprite::LoadShader(GameCore *pGame) {
    const char *shader_name = "Sprite";
    pGame->GetShaderMgr()->CreateShader(shader_name, shader_name, shader_name);
    // シェーダーの取得
    pShader = pGame->GetShaderMgr()->GetShader(shader_name);
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
	CMatrix4 tmMat = CMatrix4::Scale(CVector(sw, sh, 1));
    tmMat *= CMatrix4::Translation(CVector(srcRect.GetX(), srcRect.GetY(), 0));
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
	mvpMat *= CMatrix4::Scale(CVector(destRect.GetWidth()/2.0f, destRect.GetHeight()/2.0f, 1));
//	mvpMat *= CMatrix4::Rotation(CQuaternion(rad/(2*GL_PI), CVector(0, 0, 1)));
	mvpMat *= CMatrix4::Translation(CVector(-displayWidth/2.0f+destRect.GetX(), displayHeight/2.0f-destRect.GetY(), 0));
	mvpMat *= CMatrix4::LookAt(CVector(0, 0, 10), CVector(), CVector(0, 1, 0));
	mvpMat *= CMatrix4::Orthof(-displayWidth/2.0f, displayWidth/2.0f, displayHeight/2.0f, -displayHeight/2.0f, 1, 100);
	
    pShader->SetUniform("modelViewProjectionMatrix", mvpMat);
	
	// texMatrix
	CMatrix4 tmMat = CMatrix4::Scale(CVector(srcRect.GetWidth()/texture->GetWidth(), srcRect.GetHeight()/texture->GetHeight(), 1));
	tmMat *= CMatrix4::Translation(CVector(srcRect.GetX()/texture->GetWidth(), srcRect.GetHeight()/texture->GetHeight(), 0));
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
