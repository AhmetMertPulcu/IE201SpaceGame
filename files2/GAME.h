#pragma once
#include"BAD.h"
class Game : public PixelGameEngine
{
	int nNONPlayer = 30;
	int nBONUS = 5;
	int nBAD = 10;


	vector<shared_ptr<PLAYER>> Players;
	vector<shared_ptr<OBJECT>> Others;
	vector<shared_ptr<BLACKHOLE>> BlackHoles;
	vector<shared_ptr<BOMB>> Bombs;

	bool gameActive;
	double gracePeriod = 0;
	double graceEvilPeriod = 0;

	double totalTime;
	double score;
	double base_vel = 100;

	bool OnUserCreate();

	bool CheckGameEnd();
	void RemovePlayer(shared_ptr<OBJECT> a, vector<shared_ptr<PLAYER>>& v);
	void RemoveObject(shared_ptr<OBJECT> a, vector<shared_ptr<OBJECT>>& v);
	void RemoveBH(shared_ptr<OBJECT> a, vector<shared_ptr<BLACKHOLE>>& v);
	void RemoveBOMB(shared_ptr<OBJECT> a, vector<shared_ptr<BOMB>>& v);

	void ScoreScreen();

	bool OnUserUpdate(float fElapsedTime);
	




};