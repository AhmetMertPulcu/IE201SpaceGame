#include"NONPlayer.h"
NONPlayer::NONPlayer(PixelGameEngine* pIn, double t) : OBJECT(pIn, (double)rand() / RAND_MAX * pIn->ScreenWidth(), (double)rand() / RAND_MAX * pIn->ScreenHeight(), 5 + (t * 2) / 3, Pixel(rand() % 200, rand() % 200, rand() % 200), t + 20 + rand() % 100) {}
//NONPlayer(PixelGameEngine* pIn, double Xcoin, double Ycoin, double Massin, Pixel colorin) : OBJECT(pIn, Xcoin, Ycoin, Massin, colorin, 20 + rand()%100) {}

bool NONPlayer::CountDown(double t)
{

	if (LifeTime - t <= 0)
		return true;
	else
		return false;
}
bool NONPlayer::PlayerCollision(shared_ptr<PLAYER> p, double& score, vector<shared_ptr<PLAYER>>& v, vector<shared_ptr<OBJECT>>& v2, double t, int j, double& g)
{
	if (CompareMass(p) == true) {
		IncreaseMass(p);
		return true;
	}
	else {
		p->IncreaseMass(v2[j]);
		Reincarnation(v2, j, t);
		return false;
	}
}
void NONPlayer::Reincarnation(vector<shared_ptr<OBJECT>>& v, int j, double t) {
	v[j] = make_shared<NONPlayer>(p, t);
}
void NONPlayer::ShowCount(double t) {
	int x = LifeTime - t;
	p->DrawString(Xco, Yco, to_string(x), WHITE, 1);

}

void NONPlayer::Draw()
{
	p->FillCircle(Xco, Yco, Mass, color);
}

