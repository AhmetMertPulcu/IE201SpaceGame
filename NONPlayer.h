#pragma once
#include"BOMB.h"
class  NONPlayer : public OBJECT
{
public:
	NONPlayer(PixelGameEngine* pIn, double t);
	//NONPlayer(PixelGameEngine* pIn, double Xcoin, double Ycoin, double Massin, Pixel colorin) : OBJECT(pIn, Xcoin, Ycoin, Massin, colorin, 20 + rand()%100) {}

	bool CountDown(double t);
	
	bool PlayerCollision(shared_ptr<PLAYER> p, double& score, vector<shared_ptr<PLAYER>>& v, vector<shared_ptr<OBJECT>>& v2, double t, int j, double& g);
	void Reincarnation(vector<shared_ptr<OBJECT>>& v, int j, double t);
	void ShowCount(double t);

	void Draw();

};
