//
//  Camera.mm
//  KandataGame
//
//  Created by 木村 裕作 on 2013/08/06.
//  Copyright (c) 2013年 木村 裕作. All rights reserved.
//
#include "Game3DObject.h"
#include "Camera.h"

/**
 *  コストラクタ（デフォルト）
 */
Camera::Camera() : fovy(30.0f), aspect(1.0f), nearClip(1.0f), farClip(100.0f) {
    SetPerspective(fovy, aspect, nearClip, farClip);
}

/**
 *  コストラクタ
 */
Camera::Camera(float _fovy, float _nearClip, float _farClip) : fovy(_fovy), nearClip(_nearClip), farClip(_farClip)
{
    SetPerspective(fovy, aspect, nearClip, farClip);
}

void Camera::SetLookAt(const Vector3 &eyePos, const Vector3 &targetPos, const Vector3 &upperDir) {
    _viewMatrix = CMatrix4::LookAt(eyePos, targetPos, upperDir);
}

void Camera::SetPerspective(float _fovy, float aspect, float nClip, float fClip) {
    fovy = _fovy, this->aspect = aspect, nearClip = nClip, farClip = fClip;
    _projMatrix = CMatrix4::Perspective(fovy, this->aspect, nearClip, farClip);
}

void Camera::SetPerspective(float aspect, float nClip, float fClip) {
    this->aspect = aspect, nearClip = nClip, farClip = fClip;
    _projMatrix = CMatrix4::Perspective(fovy, this->aspect, nearClip, farClip);
}

void Camera::SetPerspective() {
    _projMatrix = CMatrix4::Perspective(fovy, aspect, nearClip, farClip);
}
