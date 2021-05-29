#pragma once
#include <iostream>
#include<vector>
#include<algorithm>
#include"olcSimpleEngine.h"


using namespace std;
using namespace olc;

class PLAYER;
class BLACKHOLE;
class BOMB;
class NONPlayer;

class OBJECT
{
protected:

	double Xco;
	double Yco;
	double Mass;
	Pixel color;
	double LifeTime;
	PixelGameEngine* p;
public:

	OBJECT(PixelGameEngine* pIn, double Xcoin, double Ycoin, double Massin, Pixel colorin, double LifeTimeIn);

	virtual bool CountDown(double t);
	virtual void Reincarnation(vector<shared_ptr<OBJECT>>& v, int j, double t);

	bool DidIHitYou(double X, double Y, double M);
	bool CheckCollision(shared_ptr<OBJECT> o);
	virtual bool PlayerCollision(shared_ptr<PLAYER> o, double& score, vector<shared_ptr<PLAYER>>& v, vector<shared_ptr<OBJECT>>& v2, double t, int j, double& g);

	void Grow(double x);
	bool OthersCollision(shared_ptr<OBJECT> o);

	virtual void Draw();
	virtual void ShowCount(double t);
	bool AmIInRange(double X, double Y);
	bool WillIDetonate(shared_ptr<OBJECT>o);


	void IncreaseMass(shared_ptr<OBJECT> a);

	void BadCollision(shared_ptr<OBJECT> a);
	double IncreaseScore(double x, shared_ptr<OBJECT> a);
	bool CompareMass(shared_ptr<OBJECT> a);

	void CreateBH(vector<shared_ptr<BLACKHOLE>>& v, double t);
	void CreateBOMB(vector<shared_ptr<BOMB>>& v, double t);
	void BlackMove(double t, shared_ptr<OBJECT> a);

}; 
