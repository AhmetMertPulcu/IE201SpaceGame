#include"GAME.h"

bool Game::OnUserCreate()
{
	gameActive = true;
	score = 0;
	totalTime = 0;
	Players.push_back(make_shared<PLAYER>(this));
	for (int i = 0; i < nNONPlayer; i++)
		Others.push_back(make_shared<NONPlayer>(this, totalTime));
	for (int i = nNONPlayer; i < nNONPlayer + nBONUS; i++)
		Others.push_back(make_shared<BONUS>(this, totalTime));
	for (int i = nNONPlayer + nBONUS; i < nNONPlayer + nBONUS + nBAD; i++)
		Others.push_back(make_shared<BAD>(this, totalTime));
	return true;
}

bool Game::CheckGameEnd()
{
	bool flagEnd = true;
	for (int i = 0; i < Players.size(); i++) {
		if (Players[i]->checkMass())
			Players.erase(Players.begin() + i);
	}
	if (Players.size() != 0)
		flagEnd = false;
	return flagEnd;
}
void Game:: RemovePlayer(shared_ptr<OBJECT> a, vector<shared_ptr<PLAYER>>& v)
{
	v.erase(find(v.begin(), v.end(), a));
}
void Game::RemoveObject(shared_ptr<OBJECT> a, vector<shared_ptr<OBJECT>>& v)
{
	v.erase(find(v.begin(), v.end(), a));
}
void Game::RemoveBH(shared_ptr<OBJECT> a, vector<shared_ptr<BLACKHOLE>>& v)
{
	v.erase(find(v.begin(), v.end(), a));
}
void Game::RemoveBOMB(shared_ptr<OBJECT> a, vector<shared_ptr<BOMB>>& v)
{
	v.erase(find(v.begin(), v.end(), a));
}

void Game::ScoreScreen()
{
	Clear(BLACK);
	DrawString(ScreenWidth() / 2 - 50, ScreenHeight() / 2, "GAME OVER");
	DrawString(ScreenWidth() / 2 - 50, ScreenHeight() / 2 + 10, "SCORE = " + to_string((int)score));
	DrawString(ScreenWidth() / 2 - 50, ScreenHeight() / 2 + 20, "Play again ?");
	DrawString(ScreenWidth() / 2 - 50, ScreenHeight() / 2 + 30, "Y / N");
	if (GetKey(Y).bPressed)
	{
		gameActive = true;
		OnUserCreate();
	}
	if (GetKey(N).bPressed)
	{
		bAtomActive = false;
	}
}

bool Game::OnUserUpdate(float fElapsedTime)
{
	if (!gameActive)
	{
		ScoreScreen();
		return true;
	}

	if (CheckGameEnd())
	{
		gameActive = false;
		while (Others.size() != 0)
			Others.pop_back();
		while (Players.size() != 0)
			Players.pop_back();
		while (BlackHoles.size() != 0)
			BlackHoles.pop_back();
		while (Bombs.size() != 0)
			Bombs.pop_back();
		return true;
	}

	totalTime += fElapsedTime;

	if (gracePeriod > 0)
		gracePeriod -= fElapsedTime;
	if (gracePeriod < 0)
		gracePeriod = 0;

	if (graceEvilPeriod > 0)
		graceEvilPeriod -= fElapsedTime;
	if (graceEvilPeriod < 0)
		graceEvilPeriod = 0;
	// 1.1 Player collision
	for (int i = 0; i < Players.size() - 1; i++) {
		for (int j = i + 1; j < Players.size(); j++) {
			if (Players[i]->CheckCollision(Players[j]) && gracePeriod == 0) {
				if (Players[i]->SelfCollision(Players[j])) {
					RemovePlayer(Players[j], Players);
				}
				else if (Players[j]->SelfCollision(Players[i])) {
					RemovePlayer(Players[i], Players);
				}

			}
		}
	}
	//1.2 Collision Check

	for (int j = 0; j < Others.size(); j++) {
		for (int i = 0; i < Players.size(); i++) {

			if (Players[i]->CheckCollision(Others[j]) && gracePeriod == 0) {
				if (Others[j]->PlayerCollision(Players[i], score, Players, Others, totalTime, j, graceEvilPeriod))
				{

					RemovePlayer(Players[i], Players);
				}

				/*if (Players.size() < i + 1)
					break;*/
			}
		}
	}
	//1.3 OthersCollision
	for (int i = 0; i < Others.size() - 1; i++) {
		for (int j = i + 1; j < Others.size(); j++) {
			if (Others[i]->CheckCollision(Others[j])) {
				if (Others[i]->OthersCollision(Others[j]) == true) {
					Others[j]->Reincarnation(Others, j, totalTime);
				}
				else {
					Others[j]->IncreaseMass(Others[i]);
					Others[i]->Reincarnation(Others, i, totalTime);
				}
			}
		}
	}

	//1.4 BlackHoleCollision
	for (auto a : BlackHoles)
	{
		for (int i = 0; i < Others.size(); i++)
		{
			if (a->CheckCollision(Others[i]))
			{
				Others[i]->Reincarnation(Others, i, totalTime);
			}

		}
		for (auto c : Players)
		{
			if (a->CheckCollision(c))
				RemovePlayer(c, Players);
		}
	}
	//1.5 BombCollision
	for (int i = 0; i < Players.size(); i++) {
		for (int j = 0; j < Bombs.size(); j++) {
			if (Players[i]->CheckCollision(Bombs[j])) {
				if (Bombs[j]->PlayerCollision(Players[i], score, Players, Others, totalTime, j, graceEvilPeriod)) {
					RemovePlayer(Players[i], Players);
				}
				else {
					Players[i]->IncreaseMass(Bombs[j]);
					RemoveBOMB(Bombs[j], Bombs);
					Others.push_back(make_shared<NONPlayer>(this, totalTime));
				}
			}
		}
	}
	//2 Detonation Check
	if (Bombs.size() >= 1) {
		for (int i = 0; i < Bombs.size(); i++) {
			if (Bombs[i]->CountDown(totalTime)) {
				Bombs[i]->Detonate();
				for (int j = 0; j < Others.size(); j++) {
					if (Others[j]->WillIDetonate(Bombs[i])) {
						Others[j]->Reincarnation(Others, j, totalTime);
					}
				}
				for (int j = 0; j < Players.size(); j++) {
					if (Players[j]->WillIDetonate(Bombs[i])) {
						RemovePlayer(Players[j], Players);
					}
				}
				RemoveBOMB(Bombs[i], Bombs);
				Others.push_back(make_shared<NONPlayer>(this, totalTime));
			}
		}
	}
	//2 division check
	if (GetKey(SPACE).bPressed && gracePeriod == 0)
	{
		Players[Players[0]->MaxMass(Players)]->Divide(Players);
	}

	//3 Life Check
	for (int i = 0; i < Others.size(); i++)
	{
		if (Others[i]->CountDown(totalTime)) {
			if (rand() % 2 == 0) {
				shared_ptr<OBJECT> temp = Others[i];
				RemoveObject(Others[i], Others);
				temp->CreateBH(BlackHoles, totalTime);

			}
			else {
				shared_ptr<OBJECT> temp1 = Others[i];
				RemoveObject(Others[i], Others);

				temp1->CreateBOMB(Bombs, totalTime);

			}
		}
	}
	//4 Grow
	if (totalTime <= 25) {
		for (auto a : Others)
		{
			a->Grow(fElapsedTime);
		}
	}
	else {
		for (auto a : Others) {
			a->Grow(fElapsedTime / 2);
		}
	}
	//5 player Move
	for (auto a : Players)
	{
		if (a->DistanceToMouse() > (double)1)
		{
			a->Move(base_vel, fElapsedTime);
		}
	}

	//6 BlackHoleMove
	for (auto a : BlackHoles)
	{
		for (auto b : Others)
			b->BlackMove(fElapsedTime, a);
		for (auto c : Players)
			c->BlackMove(fElapsedTime, a);
		for (auto d : Bombs)
			d->BlackMove(fElapsedTime, a);
	}
	//Remove BlackHoles

	for (int i = 0; i < BlackHoles.size(); i++) {
		if (BlackHoles[i]->CountDown(totalTime)) {
			RemoveBH(BlackHoles[i], BlackHoles);
			Others.push_back(make_shared<NONPlayer>(this, totalTime));
		}
	}



	Clear(olc::BLACK);

	DrawCircle(GetMouseX(), GetMouseY(), 10, olc::VERY_DARK_RED);
	for (auto a : Players)
		a->Draw();
	for (auto b : Others)
		b->Draw();
	for (auto c : BlackHoles)
		c->Draw();
	for (auto d : Bombs)
		d->Draw();
	for (int i = 0; i < Others.size(); i++)
		Others[i]->ShowCount(totalTime);
	for (int i = 0; i < Bombs.size(); i++)
		Bombs[i]->ShowCount(totalTime);
	for (int i = 0; i < BlackHoles.size(); i++)
		BlackHoles[i]->ShowCount(totalTime);


	DrawString(ScreenWidth() - 200, 5, "SCORE = " + to_string((int)score));

	return true;

}