#include "PLAYER.h"

	PLAYER::PLAYER(PixelGameEngine* pIn) : OBJECT(pIn, pIn->ScreenWidth() / 2, pIn->ScreenHeight() / 2, 10, VERY_DARK_YELLOW, INT_MAX) {}
	PLAYER::PLAYER(PixelGameEngine* pIn, double Xcoin, double Ycoin, double Massin) : OBJECT(pIn, Xcoin, Ycoin, Massin, VERY_DARK_YELLOW, INT_MAX) {}

	bool PLAYER::checkMass()
	{
		if (Mass < 5)
			return true;
		else
			return false;
	}

	double PLAYER::DistanceToMouse()
	{
		return sqrt(pow(Xco - p->GetMouseX(), 2) + pow(Yco - p->GetMouseY(), 2));
	}
	void PLAYER::Divide(vector<shared_ptr<PLAYER>>& v)
	{
		shared_ptr<PLAYER> a = make_shared<PLAYER>(p, p->GetMouseX(), p->GetMouseY(), Mass / 2);
		v.push_back(a);
		Mass = Mass / 2;

	}
	void PLAYER::IncreaseMass2(shared_ptr<PLAYER> p) {
		Mass += p->Mass;
	}
	void PLAYER::Move(double vel, double t)
	{
		double NoiseX = max<int>(abs(p->GetMouseX() - Xco), 10) * (rand() % 1000 / (double)1000 - 0.5);
		double NoiseY = max<int>(abs(p->GetMouseY() - Yco), 10) * (rand() % 1000 / (double)1000 - 0.5);
		Xco -= ((vel / pow(Mass, 0.2)) * ((double)(Xco - p->GetMouseX()) / DistanceToMouse()) + NoiseX) * t;
		Yco -= ((vel / pow(Mass, 0.2)) * ((double)(Yco - p->GetMouseY()) / DistanceToMouse()) + NoiseY) * t;
	}

	int PLAYER::MaxMass(vector<shared_ptr<PLAYER>> a)
	{
		auto x = a[0];
		int index = 0;
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i]->CompareMass(x))
			{
				x = a[i];
				index = i;
			}
		}
		return index;
	}
	bool PLAYER::SelfCollision(shared_ptr<PLAYER> n) {
		if (CompareMass(n) == true) {
			IncreaseMass2(n);
			return true;
		}
		else {

			return false;
		}
	}

	void PLAYER::Draw()
	{
		p->FillCircle(Xco, Yco, Mass, color);
	}

