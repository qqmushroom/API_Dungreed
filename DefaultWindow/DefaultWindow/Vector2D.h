#pragma once

#include "stdafx.h"
#include "Define.h"

struct Vector2D
{
public:
	float fX, fY;

public:
	Vector2D() : fX(0), fY(0) {}
	Vector2D(float _fX, float _fY) : fX(_fX), fY(_fY) {}

	Vector2D	operator+(const Vector2D& _Value) const
	{
		Vector2D temp;

		temp.fX = fX + _Value.fX;
		temp.fY = fY + _Value.fY;

		return temp;
	}

	Vector2D	operator+(const INFO& _Value) const
	{
		Vector2D temp;

		temp.fX = fX + _Value.fX;
		temp.fY = fY + _Value.fY;

		return temp;
	}

	Vector2D	operator-(const Vector2D& _Value) const
	{
		Vector2D temp;

		temp.fX = fX - _Value.fX;
		temp.fY = fY - _Value.fY;

		return temp;
	}

	Vector2D	operator-(const INFO& _Value) const
	{
		Vector2D temp;

		temp.fX = fX - _Value.fX;
		temp.fY = fY - _Value.fY;

		return temp;
	}

	void operator+=(const Vector2D& _Value)
	{
		fX += _Value.fX;
		fY += _Value.fY;
	}

	void operator+=(const INFO& _Value)
	{
		fX += _Value.fX;
		fY += _Value.fY;
	}

	void operator-=(const Vector2D& _Value)
	{
		fX -= _Value.fX;
		fY -= _Value.fY;
	}

	void operator-=(const INFO& _Value)
	{
		fX -= _Value.fX;
		fY -= _Value.fY;
	}

	float		Length()
	{
		return (float)sqrt((fX * fX) + (fY * fY));
	}

	Vector2D	Normalized()
	{
		float len = this->Length();

		return Vector2D{ fX / len, fY / len };
	}
}; 
