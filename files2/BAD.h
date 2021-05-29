#pragma once
#include"BONUS.h"
class BAD : public OBJECT
{
public:
	BAD(PixelGameEngine* pIn, double t);
	void Draw();

	bool PlayerCollision(shared_ptr<PLAYER> p, double& score, vector<shared_ptr<PLAYER>>& v, vector<shared_ptr<OBJECT>>& v2, double t, int j, double& g);
	void Reincarnation(vector<shared_ptr<OBJECT>>& v, int j, double t);
};
