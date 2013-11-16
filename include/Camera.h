//
//  Camera.h
//  KandataGame
//
//  Created by 木村 裕作 on 2013/08/06.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//

#ifndef CAMERA_H_
#define CAMERA_H_
#include "KMMath.h"
#include "_useGL.h"
#include "Component.h"

class Game3DObject;
class Shader;

class Camera : public IComponent {
    float fovy;
    float aspect;
    float nearClip;
    float farClip;
    
    CMatrix4 _viewMatrix;
    CMatrix4 _projMatrix;
public:
    /**
     *  コンストラクタ
     */
    Camera();
    Camera(float _fovy, float _nearClip, float _farClip);
    
    Camera *SetFov(float f) {
        if(f > 0) fovy = f;
        return this;
    }
    
    Camera *SetNearClip(float nearClip) {
        if(nearClip > 0) this->nearClip = nearClip;
        return this;
    }
    
    Camera *SetFarClip(float farClip) {
        if(farClip > nearClip) this->farClip = farClip;
        return this;
    }
    
    Camera *SetAspect(float aspect) {
        if(aspect > 0) this->aspect = aspect;
        return this;
    }
    
    float GetFov() const        { return fovy; }
    float GetNearClip() const   { return nearClip; }
    float GetFarClip() const    { return farClip; }
    
    const CMatrix4 &GetViewMatrix() const { return _viewMatrix; }
    const CMatrix4 &GetProjMatrix() const { return _projMatrix; }
    
    void SetLookAt(const Vector3 &eyePos, const Vector3 &targetPos, const Vector3 &upperDir);
    
    void SetPerspective(float _fovy, float aspect, float nClip, float fClip);
    void SetPerspective(float aspect, float nClip, float fClip);
    void SetPerspective();
};

#endif /* defined(CAMERA_H_) */
