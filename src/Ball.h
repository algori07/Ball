#pragma once

#include "Vector.h"

#include <numbers>

class Ball
{
	using _vector = Vector<double, 2>;
public:
	Ball(double radius, _vector pos, _vector vel = { 0,0 }, _vector acc = { 0,0 }, int colorR = 127, int colorG = 127, int colorB = 127)
		:radius(radius), pos(pos), vel(vel), acc(acc), colorR(colorR), colorG(colorG), colorB(colorB) {}
	_vector pos; // vi tri
	_vector vel; // van toc
	_vector acc; // gia toc
	int colorR;
	int colorG;
	int colorB;
	double radius;
	double mass()
	{
		return radius * radius * std::numbers::pi;
	}
};