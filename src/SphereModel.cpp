//
//  SphereModel.cpp
//  KMLib
//
//  Created by 木村 裕作 on 2013/10/26.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#include "SphereModel.h"
#include "Game3DObject.h"
#include <memory>
using namespace std;

void SphereModel::Render(const Game3DObject *pObj) {
    if(!pObj) return;
    
    // シェーダーの取得
    Shader *pShader = pObj->Get_pGame()->GetShaderMgr()->GetShader(USE_SHADER_NAME);
    pShader->Bind(); {
        float radius = 1.0f;
        
        shared_ptr<float> verts     ( new float[(segments+1)*2*3] );
        shared_ptr<float> normals   ( new float[(segments+1)*2*3] );
        shared_ptr<float> texCoords ( new float[(segments+1)*2*2] );
        
        /**
         *  Attribute変数の設定
         */
        // position
        pShader->SetAttribf("position", 3, GL_FALSE, 0, verts.get());
        // normal
        pShader->SetAttribf("normal", 3, GL_FALSE, 0, normals.get());
        
        /**
         *	Uniform変数の設定
         */
        CMatrix4
            scl = CMatrix4::Scale(pObj->scale),
            rot = CMatrix4::Rotation(pObj->rotation),
            trs = CMatrix4::Translation(pObj->position);
        CMatrix4 wld = scl * rot * trs;
        // worldMatrix
        pShader->SetUniform("worldMatrix", wld);
        // normalMatrix
        pShader->SetUniform("normalMatrix", rot);
        // monoColor
        pShader->SetUniform("monoColor", pObj->color);
        
        /**
         *  値設定
         */
        for (int j = 0, n = segments/2; j < n; j++) {
            float theta1 = j * 2 * PI_VALUE / segments - (PI_VALUE / 2.0f);
            float theta2 = (j + 1) * 2 * PI_VALUE / segments - (PI_VALUE / 2.0f);
            
            for (int i = 0; i <= segments; i++) {
                CVector e, p;
                float theta3 = i * 2 * PI_VALUE / segments;
                
                e.X = cosf( theta1 ) * cosf( theta3 );
                e.Y = sinf( theta1 );
                e.Z = cosf( theta1 ) * sinf( theta3 );
                
                p = e * radius + pObj->position;
                normals.get()[i*3*2+0] = e.X; normals.get()[i*3*2+1] = e.Y; normals.get()[i*3*2+2] = e.Z;
                texCoords.get()[i*2*2+0] = 0.999f - i / (float)segments; texCoords.get()[i*2*2+1] = 0.999f - 2 * j / (float)segments;
                verts.get()[i*3*2+0] = p.X; verts.get()[i*3*2+1] = p.Y; verts.get()[i*3*2+2] = p.Z;
                
                e.X = cosf( theta2 ) * cosf( theta3 );
                e.Y = sinf( theta2 );
                e.Z = cosf( theta2 ) * sinf( theta3 );
                p = e * radius + pObj->position;
                normals.get()[i*3*2+3] = e.X; normals.get()[i*3*2+4] = e.Y; normals.get()[i*3*2+5] = e.Z;
                texCoords.get()[i*2*2+2] = 0.999f - i / (float)segments; texCoords.get()[i*2*2+3] = 0.999f - 2 * ( j + 1 ) / (float)segments;
                verts.get()[i*3*2+3] = p.X; verts.get()[i*3*2+4] = p.Y; verts.get()[i*3*2+5] = p.Z;
            }
            
            // 描画
            glDrawArrays( GL_TRIANGLE_STRIP, 0, (segments + 1) * 2);
        }
        
        pShader->DisableAttribArray("position");
        pShader->DisableAttribArray("normal");
    }
    pShader->Unbind();
}