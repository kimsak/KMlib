//
//  Game2DObject.mm
//  KandataGame
//
//  Created by 木村 裕作 on 2013/07/21.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#include "Game2DObject.h"
#include "_useGL.h"
#include "Math.h"

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


void Game2DObject::Draw() {
    // テクスチャの有無を確認
    if(!GetTexture()) {
        return;
    }
    
    // シェーダー識別子の取得(Basic.vsh,fsh)
    Shader *pShader = Get_pGame()->GetShaderMgr()->GetShader("Basic");
    if(!pShader) return;
    
    // シェーダーの設定
    pShader->Bind();
    
    /**
     *  Attribute変数の設定
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
	    
    // modelViewProjectionMatrix
	// 行列変換
    // wldMat
    CMatrix4 wldMat = CMatrix4::Scale(Vector3(sclX, sclY, 1));
    wldMat *= CMatrix4::Rotation(CQuaternion(rotation, AXIS_Z));
    wldMat *= CMatrix4::Translation(Vector3(x, y, z));
    pShader->SetUniform("wldMat", wldMat);
    
	// texMatrix
    pShader->SetUniform("texMatrix", CMatrix4());
    
	// テクスチャの設定
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, GetTexture()->GetID());

	/**
	 *	描画
	 */
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	// テクスチャの解除
	glBindTexture(GL_TEXTURE_2D, 0);
	
	/**
	 *	頂点座標の対応付けを解除する。
	 */
    pShader->DisableAttribArray("position");
    pShader->DisableAttribArray("texcoord");
	
	/**
	 *	シェーダーの解除
	 */
	pShader->Unbind();
}