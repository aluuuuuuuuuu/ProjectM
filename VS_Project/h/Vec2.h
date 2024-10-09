#pragma once
#include <cmath>
#include "DxLib.h"

class Vec2
{
public:
	float x;
	float y;
private:
	Vec2() :
		x(0.0f),
		y(0.0f)
	{

	}

	Vec2(float X, float Y) :
		x(X),
		y(Y)
	{

	}

	Vec2(int X, int Y) :
		x(static_cast<float>(X)),
		y(static_cast<float>(Y))
	{

	}

	Vec2(int num) :
		x(static_cast<float>(num)),
		y(static_cast<float>(num))
	{

	}

	Vec2(float num) :
		x(num),
		y(num)
	{

	}

	// int�^�ɃL���X�g���ĕԂ�
	int intX() const {
		return static_cast<int>(x);
	}

	int intY() const {
		return static_cast<int>(y);
	}

	////*���Z�q�̃I�[�o�[���[�h*////
	Vec2 operator =(float num) {
		x = num;
		y = num;
		return *this;
	}

	Vec2 operator =(int num) {
		x = static_cast<float>(num);
		y = static_cast<float>(num);
		return *this;
	}

	// �����Z

	Vec2 operator +() const {
		return *this;
	}

	Vec2 operator +(Vec2 vec) const {
		return Vec2{ x + vec.x,y + vec.y };
	}

	Vec2 operator +=(Vec2 vec) {
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vec2 operator +(float num) const {
		return Vec2{ x + num,y + num };
	}

	Vec2 operator +(int num) const {
		return Vec2{ x + static_cast<float>(num),y + static_cast<float>(num) };
	}

	Vec2 operator +=(float num) {
		x += num;
		y += num;
		return *this;
	}

	Vec2 operator +=(int num) {
		x += static_cast<float>(num);
		y += static_cast<float>(num);
		return *this;
	}

	//�����Z

	Vec2 operator -() const {
		return Vec2{ -x,-y };
	}

	Vec2 operator -(Vec2 vec) const {
		return Vec2{ x - vec.x,y - vec.y };
	}

	Vec2 operator -=(Vec2 vec) {
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vec2 operator -(float num) const {
		return Vec2{ x - num,y - num };
	}

	Vec2 operator -(int num) const {
		return Vec2{ x - static_cast<float>(num),y - static_cast<float>(num) };
	}

	Vec2 operator -=(float num) {
		x -= num;
		y -= num;
		return *this;
	}

	Vec2 operator -=(int num) {
		x -= static_cast<float>(num);
		y -= static_cast<float>(num);
		return *this;
	}

	//�|���Z
	Vec2 operator *(float num) const {
		return Vec2{ x * num,y * num };
	}

	Vec2 operator *(int num) const {
		return Vec2{ x * static_cast<float>(num),y * static_cast<float>(num) };
	}

	Vec2 operator *=(float num) {
		x *= num;
		y *= num;
		return *this;
	}

	Vec2 operator *=(int num) {
		x *= static_cast<float>(num);
		y *= static_cast<float>(num);
		return *this;
	}

	//����Z
	Vec2 operator /(float num) const {
		return Vec2{ x / num,y / num };
	}

	Vec2 operator /(int num) const {
		return Vec2{ x / static_cast<float>(num),y / static_cast<float>(num) };
	}

	Vec2 operator /=(float num) {
		x /= num;
		y /= num;
		return *this;
	}

	Vec2 operator /=(int num) {
		x /= static_cast<float>(num);
		y /= static_cast<float>(num);
		return *this;
	}

	//�x�N�g���̒����̓������߂�
	float SqLength() const {
		return x * x + y * y;
	}

	//�x�N�g���̒��������߂�
	float Length() const {
		return sqrtf(SqLength());
	}

	//���g�̐��K�����s��
	void Normalize() {
		float len = Length();

		//����0�ȉ��Ȃ珈�����s��Ȃ�
		if (len <= 0.0f) return;

		x /= len;
		y /= len;
	}

	//���M�𐳋K�������x�N�g�����擾����
	Vec2 GetNormalized() const {
		float len = Length();

		//����0�ȉ��Ȃ�(0,0)��Ԃ�
		//��������ɂ��Ă��闝�R
		//�����Ȃ��R���X�g���N�^�̏C���ɋ������邽��
		if (len <= 0.0f) return Vec2{ 0.0f,0.0f };

		return Vec2{ x / len,y / len };
	}

	// ���g�⑼�̃x�N�g���Ƃ̓��ς��Ƃ�
	float dot(const Vec2& other) const {
		return x * other.x + y * other.y ;
	}

	// 2�̃x�N�g���̓��ς����߂�
	float dot(const Vec2& a, const Vec2& b) const {
		return a.x * b.x + a.y * b.y;
	}
};