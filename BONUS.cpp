#include"BONUS.h"
BONUS::BONUS(PixelGameEngine* pIn, double t) :OBJECT(pIn, (double)rand() / RAND_MAX * pIn->ScreenWidth(), (double)rand() / RAND_MAX * pIn->ScreenHeight(), 5 + t / 2, Pixel(rand() % 200, rand() % 200, rand() % 200), INT_MAX) {}
void BONUS::Draw()
{
	p->FillTriangle(Xco, Yco - Mass, Xco - Mass, Yco + Mass, Xco + Mass, Yco + Mass, color);
}
void BONUS::Reincarnation(vector<shared_ptr<OBJECT>>& v, int j, double t) {
	v[j] = make_shared<BONUS>(p, t);
}
bool BONUS::PlayerCollision(shared_ptr<PLAYER> p, double& score, vector<shared_ptr<PLAYER>>& v, vector<shared_ptr<OBJECT>>& v2, double t, int j, double& g) {
	if (CompareMass(p) == true) {
		IncreaseMass(p);
		return true;
	}
	else {
		score += Mass;
		p->IncreaseMass(v2[j]);
		Reincarnation(v2, j, t);
		return false;

	}

}