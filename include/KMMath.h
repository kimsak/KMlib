/*
 * Math.h
 *
 *  Created on: 2013/02/03
 *      Author: kimurayuusaku
 */

#ifndef MATH_H_
#define MATH_H_

#include <cmath>
#include <assert.h>

#define PI_VALUE        (3.14159265f)
#define ToRad(Deg)      ((Deg)*PI_VALUE/180.0f)

// 1次元線形補間
inline float Lerp(float x1, float x2, float t) {
    return (1-t)*x1 + t*x2;
}

// 2次元ベクトルクラス
class Vector2 {
public:
    float X, Y;
    
    
    // コンストラクタ
    Vector2() : X(0.0f), Y(0.0f) {}
    Vector2(float x, float y) : X(x), Y(y) {}
    
    /// 代入（2次元ベクトル）
    Vector2& operator=(const Vector2& v) {
        X=v.X, Y=v.Y;
        return *this;
    }
    /// 代入（float）
    Vector2& operator=(float f) {
        X = Y = f;
        return *this;
    }
    /// 代入（int）
    Vector2 & operator=(int n) {
        return *this = (float)n;
    }
    
    // 加算処理（2項）
    Vector2 operator +(const Vector2& v) const {
        return Vector2(X+v.X, Y+v.Y);
    }
    
    // 減算処理（2項）
    Vector2 operator -(const Vector2& v) const {
        return Vector2(X-v.X, Y-v.Y);
    }
    
    // 倍数処理
    Vector2 operator *(float d) const {
        return Vector2(d*X, d*Y);
    }
    friend Vector2 operator *(float d, const Vector2 &v) {
        return Vector2(d*v.X, d*v.Y);
    }
    
    // 除算処理
    Vector2 operator /(float d) const {
        if(d==0.0) {
            return *this;
        }
        else {
            return Vector2(this->X/d, this->Y/d);
        }
    }
    
    // 単項マイナス
    Vector2 operator -() const {
        return (-1.0f)*(*this);
    }
    
    // 代入加算
    Vector2 & operator +=(const Vector2& v) {
        this->X += v.X; this->Y += v.Y;
        return *this;
    }
    
    // 代入減算
    Vector2& operator -=(const Vector2& v) {
        this->X -= v.X; this->Y -= v.Y;
        return *this;
    }
    
    // 代入乗算
    Vector2& operator *=(float d) {
        this->X *= d; this->Y *= d;
        return *this;
    }
    
    // 代入除算
    Vector2& operator /=(float d) {
        if(d==0.0) return *this;
        else {
            this->X /= d; this->Y /= d;
            return *this;
        }
    }
    
    // ベクトルの大きさを求める（2乗）
    float Length2() const {
        return X*X + Y*Y;
    }
    
    // ベクトルの大きさを求める
    float Length() const {
        return sqrtf(Length2());
    }
    
    // 正規化処理
    Vector2& Normalize() {
        return (*this /= Length());
    }
    friend Vector2 Normalize(const Vector2& v) {
        return v / v.Length();
    }
    
    // 内積
    float Dot(const Vector2 &v) const {
        return X*v.X+Y*v.Y;
    }
    friend float Dot(const Vector2 &a, const Vector2 &b) {
        return a.Dot(b);
    }
    
    // 外積
    float Cross(const Vector2& v) const {
        return X*v.Y - Y*v.X;
    }
    friend float Cross(const Vector2 &a, const Vector2 &b) {
        return a.Cross(b);
    }
    
    // 線形補間関数
    Vector2 Lerp(const Vector2 &target, float d) {
        return (1-d)*(*this) + d*target;
    }
};

// 3次元ベクトルクラス
class Vector3 {
public:
    float X, Y, Z;
    
    // コンストラクタ
    Vector3() : X(0.0f), Y(0.0f), Z(0.0f) {}
    Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
    
    /// 代入（3次元ベクトル）
    Vector3& operator=(const Vector3& v) {
        X=v.X, Y=v.Y, Z=v.Z;
        return *this;
    }
    /// 代入（float）
    Vector3& operator=(float f) {
        X = Y = Z = f;
        return *this;
    }
    /// 代入（int）
    Vector3 & operator=(int n) {
        return *this = (float)n;
    }
    
    // 加算処理（2項）
    Vector3 operator +(const Vector3& v) const {
        return Vector3(X+v.X, Y+v.Y, Z+v.Z);
    }
    
    // 減算処理（2項）
    Vector3 operator -(const Vector3& v) const {
        return Vector3(X-v.X, Y-v.Y, Z-v.Z);
    }
    
    // 倍数処理
    Vector3 operator *(float d) const {
        return Vector3(d*X, d*Y, d*Z);
    }
    friend Vector3 operator *(float d, const Vector3 &v) {
        return Vector3(d*v.X, d*v.Y, d*v.Z);
    }
    
    // 除算処理
    Vector3 operator /(float d) const {
        if(d==0.0) {
            return *this;
        }
        else {
            return Vector3(this->X/d, this->Y/d, this->Z/d);
        }
    }
    
    // 単項マイナス
    Vector3 operator -() const {
        return (-1)*(*this);
    }
    
    // 代入加算
    Vector3 & operator +=(const Vector3& v) {
        this->X += v.X; this->Y += v.Y; this->Z += v.Z;
        return *this;
    }
    
    // 代入減算
    Vector3& operator -=(const Vector3& v) {
        this->X -= v.X; this->Y -= v.Y; this->Z -= v.Z;
        return *this;
    }
    
    // 代入乗算
    Vector3& operator *=(float d) {
        this->X *= d; this->Y *= d; this->Z *= d;
        return *this;
    }
    
    // 代入除算
    Vector3& operator /=(float d) {
        if(d==0.0) return *this;
        else {
            this->X /= d; this->Y /= d; this->Z /= d;
            return *this;
        }
    }
    
    // ベクトルの大きさを求める（2乗）
    float Length2() const {
        return X*X + Y*Y + Z*Z;
    }
    
    // ベクトルの大きさを求める
    float Length() const {
        return sqrtf(Length2());
    }
    
    // 正規化処理
    Vector3& Normalize() {
        return (*this /= Length());
    }
    friend Vector3 Normalize(const Vector3& v) {
        return v / v.Length();
    }
    
    // 内積
    float Dot(const Vector3 &v) const {
        return X*v.X+Y*v.Y+Z*v.Z;
    }
    friend float Dot(const Vector3 &a, const Vector3 &b) {
        return a.Dot(b);
    }
    
    // 外積
    Vector3 Cross(const Vector3& v) const {
        return Vector3(Y*v.Z-Z*v.Y, Z*v.X-X*v.Z, X*v.Y-Y*v.X);
    }
    friend Vector3 Cross(const Vector3 &a, const Vector3 &b) {
        return a.Cross(b);
    }
    
    // 線形補間関数
    Vector3 Lerp(const Vector3 &target, float d) {
        return (1-d)*(*this) + d*target;
    }
    
    void SetXY(float x, float y) {
        X = x; Y = y;
    }
    
    void SetXZ(float x, float z) {
        X = x; Z = z;
    }
    
    void SetYZ(float y, float z) {
        Y = y; Z = z;
    }
};

// ベクトルクラスに関するマクロ定義
#define AXIS_X		Vector3(1,0,0)
#define AXIS_Y		Vector3(0,1,0)
#define AXIS_Z		Vector3(0,0,1)
#define VEC_ZERO	Vector3()
#define VEC_ONE		Vector3(1,1,1)

// クォータニオンクラス
class CQuaternion {
public:
    float X, Y, Z, W;
    
    // コンストラクタ
    CQuaternion() : X(0.0f), Y(0.0f), Z(0.0f), W(1.0f) {}
    CQuaternion(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}
    
    ///	コンストラクタ
    //	angleの範囲は0=0rad,1=2π_rad
    CQuaternion(float angle, const Vector3& axis) {
        Vector3 nAxis = Normalize(axis);
        float sin_ang = sinf(angle/2.0f);
        X = sin_ang*nAxis.X, Y = sin_ang*nAxis.Y, Z = sin_ang*nAxis.Z;
        W = cosf(angle/2.0f);
    }
    
    // 代入
    CQuaternion& operator =(const CQuaternion& q) {
        X=q.X, Y=q.Y, Z=q.Z, W=q.W;
        return *this;
    }
    
    // 乗算
    CQuaternion operator *(const CQuaternion& q) const {
        CQuaternion r;
        r.W = W*q.W - X*q.X - Y*q.Y - Z*q.Z;
        r.X = W*q.X + X*q.W - Y*q.Z + Z*q.Y;
        r.Y = W*q.Y + Y*q.W + X*q.Z - Z*q.X;
        r.Z = W*q.Z + Z*q.W - X*q.Y + Y*q.X;
        return r;
    }
    
    // 代入乗算
    CQuaternion& operator *=(const CQuaternion& q) {
        return (*this = (*this)*q);
    }
    
    // 共役四元数
    CQuaternion operator ~() const {
        return CQuaternion(-X, -Y, -Z, W);
    }
    
    // クォータニオンを使ったベクトルの回転
    Vector3 Rotate(const Vector3& v) const {
        CQuaternion p(v.X, v.Y, v.Z, 0);
        p = ~(*this)*p;
        p *= (*this);
        return Vector3(p.X, p.Y, p.Z);
    }
    friend Vector3 operator *(const Vector3 &v, const CQuaternion &q) {
        return q.Rotate(v);
    }
};

/**
 *	4x4行列クラス
 */
#define MATRIX4x4_LENGTH	(16)
class CMatrix4 {
    float arr[MATRIX4x4_LENGTH];
    
public:
    // コンストラクタ
    // デフォルトでは単位行列
    CMatrix4() {
        for(int i=0; i<MATRIX4x4_LENGTH; i++) arr[i] = 0;
        arr[0] = arr[5] = arr[10] = arr[15] = 1;
    }
    
    CMatrix4(
             float m11, float m12, float m13, float m14,
             float m21, float m22, float m23, float m24,
             float m31, float m32, float m33, float m34,
             float m41, float m42, float m43, float m44
             ) {
        arr[0] = m11; arr[1] = m12; arr[2] = m13; arr[3] = m14;
        arr[4] = m21; arr[5] = m22; arr[6] = m23; arr[7] = m24;
        arr[8] = m31; arr[9] = m32; arr[10] = m33; arr[11] = m34;
        arr[12] = m41; arr[13] = m42; arr[14] = m43; arr[15] = m44;
    }
    
    CMatrix4(float value) {
        for(int i=0; i<MATRIX4x4_LENGTH; i++) arr[i] = value;
    }
    
    // インデクサみたいなもの
    float& operator [](int index) {
        assert(0<=index && index<MATRIX4x4_LENGTH);
        return arr[index];
    }
    
    // Getter
    float Get(int index) const {
        assert(0<=index && index<MATRIX4x4_LENGTH);
        return (0<=index && index<MATRIX4x4_LENGTH) ? arr[index] : 0;
    }
    
    // Setter
    void Set(int index, float value) {
        assert(0<=index && index<MATRIX4x4_LENGTH);
        if(0<=index && index<MATRIX4x4_LENGTH) arr[index] = value;
    }
    
    // コピーコストラクタ
    CMatrix4(const CMatrix4& m) {
        for(int i=0; i<MATRIX4x4_LENGTH; i++) arr[i] = m.Get(i);
    }
    
    CMatrix4 operator +(const CMatrix4& m) const {
        CMatrix4 r;
        for(int i=0; i<MATRIX4x4_LENGTH; i++)
            r.Set(i, arr[i]+m.Get(i));
        return r;
    }
    
    CMatrix4 operator -(const CMatrix4& m) const {
        CMatrix4 r;
        for(int i=0; i<MATRIX4x4_LENGTH; i++)
            r.Set(i, arr[i]-m.Get(i));
        return r;
    }
    
    CMatrix4 operator *(float num) const {
        return CMatrix4(
                        arr[0]*num, arr[1]*num, arr[2]*num, arr[3]*num,
                        arr[4]*num, arr[5]*num, arr[6]*num, arr[7]*num,
                        arr[8]*num, arr[9]*num, arr[10]*num, arr[11]*num,
                        arr[12]*num, arr[13]*num, arr[14]*num, arr[15]*num
                        );
    }
    friend CMatrix4 operator *(float num, const CMatrix4& m) {
        return m * num;
    }
    
    CMatrix4 operator *(const CMatrix4& m) const {
        CMatrix4 r;
        for(int i=0; i<4; i++) {
            for(int j=0; j<4; j++) {
                r.Set(j+i*4, 0);
                for(int k=0; k<4; k++)
                    r[j+i*4] += arr[4*i+k]*m.Get(j+4*k);
            }
        }
        return r;
    }
    
    CMatrix4& operator =(const CMatrix4& m) {
        for(int i=0; i<MATRIX4x4_LENGTH; i++) arr[i] = m.Get(i);
        return (*this);
    }
    
    CMatrix4& operator =(float value) {
        for(int i=0; i<MATRIX4x4_LENGTH; i++) arr[i] = value;
        return (*this);
    }
    
    CMatrix4& operator *=(const CMatrix4& m) {
        return (*this = *this * m);
    }
    
    //	float Determinant() const {
    //		float result = 0.0f;
    //
    //		return result;
    //	}
    //
    //	/**
    //	 *	逆行列を返す関数
    //	 */
    //	CMatrix4 Inverse() const {
    //		CMatrix4 r;
    //
    //		return r;
    //	}
    
    //=======================================================
    // ここからstatic関数
    
    static CMatrix4 Orthof(float left, float right, float top, float bottom, float near, float far) {
        CMatrix4 r;
        r.Set(0, 2.0f/(right-left));
        r.Set(5, 2.0f/(top-bottom));
        r.Set(10, -2.0f/(far-near));
        
        r.Set(12, -(right+left)/(right-left));
        r.Set(13, -(top+bottom)/(top-bottom));
        r.Set(14, -(far+near)/(far-near));
        
        return r;
    }
    
    static CMatrix4 Frustum(float left, float right, float top, float bottom, float near, float far) {
        CMatrix4 r;
        float dx = right - left;
        float dy = top - bottom;
        float dz = far - near;
        
        r[0] = 2.0f*near/dx;
        r[5] = 2.0f*near/dy;
        r[10] = -(far+near)/dz;
        
        r[8] = (right+left)/dx;
        r[9] = (top+bottom)/dy;
        r[11] = -1.0f;
        r[14] = -2.0f*far*near/dz;
        
        r[15] = 0;
        
        return r;
    }
    
    /**
     *	透視投影の行列を返す関数
     */
    static CMatrix4 Perspective(float fovyDeg, float asp, float near, float far) {
        CMatrix4 r;
        float top = near * tanf(ToRad(fovyDeg)/2.0f);
        float right = top * asp;
        
        return Frustum(-right, right, top, -top, near, far);
    }
    
    static CMatrix4 LookAt(const Vector3& eye, const Vector3& target, const Vector3& up) {
        CMatrix4 r;
        
        Vector3 vz = eye - target;
        vz.Normalize();
        
        Vector3 vx = up.Cross(vz);
        vx.Normalize();
        
        Vector3 vy = vz.Cross(vx);
        vy.Normalize();
        
        r.Set(0, vx.X); r.Set(1, vy.X); r.Set(2, vz.X);
        //		r.Set(3, 0);
        r.Set(4, vx.Y); r.Set(5, vy.Y); r.Set(6, vz.Y);
        //		r.Set(7, 0);
        r.Set(8, vx.Z); r.Set(9, vy.Z); r.Set(10, vz.Z);
        //		r.Set(11, 0);
        r.Set(12, vx.Dot(-eye)); r.Set(13, vy.Dot(-eye)); r.Set(14, vz.Dot(-eye));
        //		r.Set(15, 1);
        
        return r;
    }
    
    static CMatrix4 Scale(const Vector3& scale) {
        return CMatrix4(
                        scale.X, 0, 0, 0,
                        0, scale.Y, 0, 0,
                        0, 0, scale.Z, 0,
                        0, 0, 0, 1
                        );
    }
    
    static CMatrix4 Rotation(const CQuaternion& q) {
        CMatrix4 r;
        float x2 = float(q.X * q.X) * 2.0f;
        float y2 = float(q.Y * q.Y) * 2.0f;
        float z2 = float(q.Z * q.Z) * 2.0f;
        float xy = float(q.X * q.Y) * 2.0f;
        float yz = float(q.Y * q.Z) * 2.0f;
        float zx = float(q.Z * q.X) * 2.0f;
        float xw = float(q.X * q.W) * 2.0f;
        float yw = float(q.Y * q.W) * 2.0f;
        float zw = float(q.Z * q.W) * 2.0f;
        
        r.arr[0] = 1.0f - y2 - z2;
        r.arr[4] = xy - zw;
        r.arr[8] = zx + yw;
        r.arr[3] = r.arr[7] = r.arr[11] = r.arr[12] = r.arr[13] = r.arr[14] = 0.0f;
        r.arr[1] = xy + zw;
        r.arr[5] = 1.0f - z2 - x2;
        r.arr[9] = yz - xw;
        r.arr[2] = zx - yw;
        r.arr[6] = yz + xw;
        r.arr[10] = 1.0f - x2 - y2;
        r.arr[15] = 1.0f;
        
        return r;
    }
    
    static CMatrix4 Translation(const Vector3& v) {
        CMatrix4 r;
        r.Set(12, v.X); r.Set(13, v.Y); r.Set(14, v.Z);
        return r;
    }
};
#undef MATRIX4x4_LENGTH

/**
 * クォータニオンの値を回転行列として計算し、配列に格納する
 * 条件：配列の長さは必ず16
 * @param arr 格納するための配列ポインタ
 * @param q 回転行列として入力するためのクォータニオン変数
 */
inline void GetArrayFromQuaternion(float arr[], const CQuaternion *q) {
    float x2 = float(q->X * q->X) * 2.0f;
    float y2 = float(q->Y * q->Y) * 2.0f;
    float z2 = float(q->Z * q->Z) * 2.0f;
    float xy = float(q->X * q->Y) * 2.0f;
    float yz = float(q->Y * q->Z) * 2.0f;
    float zx = float(q->Z * q->X) * 2.0f;
    float xw = float(q->X * q->W) * 2.0f;
    float yw = float(q->Y * q->W) * 2.0f;
    float zw = float(q->Z * q->W) * 2.0f;
    
    arr[0] = 1.0f - y2 - z2;
    arr[4] = xy - zw;
    arr[8] = zx + yw;
    arr[3] = arr[7] = arr[11] = arr[12] = arr[13] = arr[14] = 0.0f;
    arr[1] = xy + zw;
    arr[5] = 1.0f - z2 - x2;
    arr[9] = yz - xw;
    arr[2] = zx - yw;
    arr[6] = yz + xw;
    arr[10] = 1.0f - x2 - y2;
    arr[15] = 1.0f;
}

/**
 * 変換行列でベクトルを演算する。
 * @param transMatrix[16] 変換行列
 * @param vec[4] 4次元ベクトル
 */
inline void TransformVector(float transMatrix[], float vec[]) {
    float tmpVec[4];
    for(int i=0; i<4; i++) tmpVec[i]=vec[i];
    
    for(int i=0; i<4; i++) {
        vec[i] = 0;
        for(int j=0; j<4; j++) vec[i] += transMatrix[i + 4*j]*tmpVec[j];
    }
}

/**
 * 長方形を表すクラス
 */
class CRectangle {
    float _x, _y;				// 左下の座標を表すメンバ変数
    float _width, _height;		// 幅と高さを表すメンバ変数
public:
    /**
     *	 デフォルトコンストラクタ
     */
    CRectangle() : _x(0), _y(0), _width(1), _height(1) {}
    
    /**
     * コンストラクタ
     * @param centerX		長方形の中心(X座標)
     * @param centerY		長方形の中心(Y座標)
     * @param halfWidth		長方形の幅の半分
     * @param halfHeight	長方形の高さの半分
     */
    CRectangle(float centerX, float centerY, float halfWidth, float halfHeight) {
        _x = centerX - halfWidth; _y = centerY - halfHeight;
        _width = 2 * abs(halfWidth); _height = 2 * abs(halfHeight);
    }
    
    void SetXY(float x, float y) { _x = x; _y = y; }
    void SetSize(float width, float height) { _width = width; _height = height; }
    void SetBounds(float x, float y, float width, float height) {
        SetXY(x, y); SetSize(width, height);
    }
    
    float GetX() const { return _x; }
    float GetY() const { return _y; }
    float GetWidth() const { return _width; }
    float GetHeight() const { return _height; }
    float GetAspect() const { return _width/_height; }
    
    bool IsIntersect(const CRectangle& r) {
        return _x < r.GetX()+r.GetWidth() &&
        r.GetX() < _x + _width &&
        _y < r.GetY() + r.GetHeight() &&
        r.GetY() < _y + _height;
    }
    
    bool IsInside(float x, float y) {
        return _x <= x && x <= _x+_width && _y <= y && y <= _y + _height;
    }
};

#endif /* MATH_H_ */
