#include "BAD.h"
BAD::BAD(PixelGameEngine* pIn, double t) :OBJECT(pIn, (double)rand() / RAND_MAX * pIn->ScreenWidth(), (double)rand() / RAND_MAX * pIn->ScreenHeight(), 5 + t / 2, Pixel(rand() % 200, rand() % 200, rand() % 200), INT_MAX) {}
void BAD::Draw()
{
	p->FillRect(Xco - Mass, Yco - Mass, 2 * Mass, 2 * Mass, color);
}

bool BAD::PlayerCollision(shared_ptr<PLAYER> p, double& score, vector<shared_ptr<PLAYER>>& v, vector<shared_ptr<OBJECT>>& v2, double t, int j, double& g) {
	if (g == 0) {
		if (CompareMass(p) == true) {

			return true;
		}
		else {
			BadCollision(p);
			p->Divide(v);
			g = 0.5;
			return false;
		}

	}

}
void BAD::Reincarnation(vector<shared_ptr<OBJECT>>& v, int j, double t) {
	v[j] = make_shared<BAD>(p, t);
}
