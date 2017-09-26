#pragma once

class Vector
{
public:
	float x;
	float y;

	Vector(float x = 0, float y = 0) : x(x),
		y(y)
	{
	}

	Vector operator+(const Vector& vIn) const
	{
		Vector vOut;
		vOut.x = x + vIn.x;
		vOut.y = y + vIn.y;
		return vOut;
	}
	Vector operator-(const Vector& vIn) const
	{
		Vector vOut;
		vOut.x = x - vIn.x;
		vOut.y = y - vIn.y;
		return vOut;
	}
	Vector operator*(float value) const
	{
		Vector vOut;
		vOut.x = x * value;
		vOut.y = y * value;
		return vOut;
	}
	Vector operator/(float value) const
	{
		Vector vOut;
		vOut.x = x / value;
		vOut.y = y / value;
		return vOut;
	}
	Vector& operator+=(const Vector& vIn)
	{
		x += vIn.x;
		y += vIn.y;
		return *this;
	}
	friend Vector operator*(float value, const Vector& vIn)
	{
		return vIn * value;
	}

	static float Length(const Vector& v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}
	static Vector Normalize(const Vector& v)
	{
		float len = Length(v);
		if (len != 0)
		{
			return v / len;
		}
		return v;
	}
};