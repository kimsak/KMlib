//
//  CubeModel.mm
//  KandataGame
//
//  Created by 木村 裕作 on 2013/08/01.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#include "CubeModel.h"
#include "Game3DObject.h"

// 頂点データ
static GLfloat gCubeVertexData[216] =
{
    // Data layout for each line below is:
    // positionX, positionY, positionZ,     normalX, normalY, normalZ,
    0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f,         1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f,         1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f,          1.0f, 0.0f, 0.0f,
    
    0.5f, 0.5f, -0.5f,         0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,        0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f,          0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f,          0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,        0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,         0.0f, 1.0f, 0.0f,
    
    -0.5f, 0.5f, -0.5f,        -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,       -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,         -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,         -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,       -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,        -1.0f, 0.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f,       0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,        0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,        0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f,         0.0f, -1.0f, 0.0f,
    
    0.5f, 0.5f, 0.5f,          0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,        0.0f, 0.0f, 1.0f,
    
    0.5f, -0.5f, -0.5f,        0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f,         0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f,         0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, -1.0f,
    -0.5f, 0.5f, -0.5f,        0.0f, 0.0f, -1.0f
};


void CubeModel::Render(const Game3DObject *pObj) {
    assert(pObj != NULL);
    
    Shader *pShader = pObj->Get_pGame()->GetShaderMgr()->GetShader(USE_SHADER_NAME);
    if(!pShader) return;      // プログラム値が０だったら処理終了
    pShader->Bind();
    
    /**
	 *	Attribute変数の設定
	 */
	// position
    pShader->SetAttribf("position", 3, GL_FALSE, 6, gCubeVertexData);
	// normal
    pShader->SetAttribf("normal", 3, GL_FALSE, 6, gCubeVertexData + 3);
	
	/**
	 *	Uniform変数の設定
	 */
	// worldMatrix
	CMatrix4
	scl = CMatrix4::Scale(pObj->scale),
	rot = CMatrix4::Rotation(pObj->rotation),
	trs = CMatrix4::Translation(pObj->position);
	CMatrix4 wld = scl * rot * trs;
    pShader->SetUniform("worldMatrix", wld);
	// normalMatrix
    pShader->SetUniform("normalMatrix", rot);
	// monoColor
    pShader->SetUniform("monoColor", pObj->color);
	
	/**
	 *	描画
	 */
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
    pShader->DisableAttribArray("position");
    pShader->DisableAttribArray("normal");
    
    pShader->Unbind();
}
