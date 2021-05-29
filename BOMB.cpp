#include"BOMB.h"
BOMB::BOMB(PixelGameEngine* pIn, double Xcoin, double Ycoin, double t) :OBJECT(pIn, Xcoin, Ycoin, 15, RED, t + 10) {}
bool BOMB::CountDown(double t) {
	if (LifeTime - t < 0) {
		return true;
	}
	else
		return false;
}
void BOMB::Draw() {
	for (int i = Mass; i > 0; i--) {
		if (i % 2 == 0)
			p->FillCircle(Xco, Yco, i, RED);
		else
			p->FillCircle(Xco, Yco, i, BLUE);
	}
	p->DrawCircle(Xco, Yco, 3 * Mass, BLUE);
}
void BOMB::ShowCount(double t) {
	int x = LifeTime - t;
	p->DrawString(Xco, Yco, to_string(x), WHITE, 1);

}
void BOMB::Detonate() {
	p->FillCircle(Xco, Yco, 3 * Mass, RED);
}
bool BOMB::PlayerCollision(shared_ptr<PLAYER> p, double& score, vector<shared_ptr<PLAYER>>& v, vector<shared_ptr<OBJECT>>& v2, double t, int j, double& g) {
	if (CompareMass(p)) {
		return true;
	}
	else
		return false;
}