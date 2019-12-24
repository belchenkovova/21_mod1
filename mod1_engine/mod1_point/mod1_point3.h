#pragma once

#include "mod1_error.h"

template				<typename t1>
class					mod1_point3
{
public :
	t1					x = 0;
	t1					y = 0;
	t1					z = 0;

						mod1_point3() = default;
	explicit			mod1_point3(t1 value)
	{
		this->x = value;
		this->y = value;
		this->z = value;
	}
						mod1_point3(t1 x, t1 y, t1 z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
						~mod1_point3() = default;

	mod1_point3<t1>		operator + (const mod1_point3<t1> &other) const
	{
		return (mod1_point3<t1>(this->x + other.x, this->y + other.y, this->z + other.z));
	}

	mod1_point3<t1>		operator - (const mod1_point3<t1> &other) const
	{
		return (mod1_point3<t1>(this->x - other.x, this->y - other.y, this->z - other.z));
	}

	mod1_point3<t1>		operator * (const mod1_point3<t1> &other) const
	{
		return (mod1_point3<t1>(this->x * other.x, this->y * other.y, this->z * other.z));
	}

	template 			<typename t2>
	mod1_point3<t1>		operator * (const t2 &other) const
	{
		return (mod1_point3<t1>(this->x * other, this->y * other, this->z * other));
	}

	mod1_point3<t1>		operator / (const mod1_point3<t1> &other) const
	{
		return (mod1_point3<t1>(this->x / other.x, this->y / other.y, this->z / other.z));
	}

	template 			<typename t2>
	mod1_point3<t1>		operator / (const t2 &other) const
	{
		return (mod1_point3<t1>(this->x / other, this->y / other, this->z / other));
	}

	void				operator += (const mod1_point3<t1> &other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
	}

	void				operator -= (const mod1_point3<t1> &other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z += other.z;
	}

	void				operator *= (const mod1_point3<t1> &other)
	{
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
	}

	template 			<typename t2>
	void				operator *= (const t2 &other)
	{
		this->x *= other;
		this->y *= other;
		this->z *= other;
	}

	void				operator /= (const mod1_point3<t1> &other)
	{
		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;
	}

	template 			<typename t2>
	void				operator /= (const t2 &other)
	{
		this->x /= other;
		this->y /= other;
		this->z /= other;
	}

	t1				&operator [] (int i)
	{
		switch (i)
		{
			case 0 :
				return (x);
			case 1 :
				return (y);
			case 2 :
				return (z);
			default :
				global_error->raise_warning("Point3 : Incorrect index");
		}
		return (x);
	}

	const t1			&operator [] (int i) const
	{
		switch (i)
		{
			case 0 :
				return (x);
			case 1 :
				return (y);
			case 2 :
				return (z);
			default :
				global_error->raise_warning("Point3 : Incorrect index");
		}
		return (x);
	}

	template 			<class p2>
	mod1_point3<t1>		&operator = (const p2 &point2)
	{
		this->x = point2.x;
		this->y = point2.y;
		return (*this);
	}

	bool				operator == (const mod1_point3<t1> &other)
	{
		if (this->x != other.x)
			return (false);
		if (this->y != other.y)
			return (false);
		if (this->z != other.z)
			return (false);
		return (true);
	}
};