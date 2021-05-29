#pragma once
#include "OBJECT.h"
class PLAYER : public OBJECT
{
public:
	PLAYER(PixelGameEngine* pIn);
	PLAYER(PixelGameEngine* pIn, double Xcoin, double Ycoin, double Massin);

	bool checkMass();

	double DistanceToMouse();
	void Divide(vector<shared_ptr<PLAYER>>& v);
	void IncreaseMass2(shared_ptr<PLAYER> p);
	void Move(double vel, double t);

	int MaxMass(vector<shared_ptr<PLAYER>> a);
	bool SelfCollision(shared_ptr<PLAYER> n);

	void Draw();
};
