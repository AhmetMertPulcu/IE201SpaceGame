#pragma once
#include"PLAYER.h"

class BLACKHOLE : public OBJECT
{
public:
	BLACKHOLE(PixelGameEngine* pIn, double Xcoin, double Ycoin, double t);
	bool CountDown(double t);
	void ShowCount(double t);
	void Draw();

};
