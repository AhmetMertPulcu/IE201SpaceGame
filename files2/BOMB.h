#pragma once
#include "BLACKHOLE.h"

class BOMB :public OBJECT {
public:
	BOMB(PixelGameEngine* pIn, double Xcoin, double Ycoin, double t);
	bool CountDown(double t);
	void Draw();
	void ShowCount(double t);
	void Detonate();
	bool PlayerCollision(shared_ptr<PLAYER> p, double& score, vector<shared_ptr<PLAYER>>& v, vector<shared_ptr<OBJECT>>& v2, double t, int j, double& g);
};