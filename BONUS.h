#pragma once
#include"NONPlayer.h"
class BONUS : public OBJECT
{
public:
	BONUS(PixelGameEngine* pIn, double t);
	void Draw();
	void Reincarnation(vector<shared_ptr<OBJECT>>& v, int j, double t);

	bool PlayerCollision(shared_ptr<PLAYER> p, double& score, vector<shared_ptr<PLAYER>>& v, vector<shared_ptr<OBJECT>>& v2, double t, int j, double& g);
};