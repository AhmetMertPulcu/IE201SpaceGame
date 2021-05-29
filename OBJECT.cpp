#include"OBJECT.h"
#include"GAME.h"
OBJECT::OBJECT(PixelGameEngine* pIn, double Xcoin, double Ycoin, double Massin, Pixel colorin, double LifeTimeIn) : p(pIn), Xco(Xcoin), Yco(Ycoin), Mass(Massin), color(colorin), LifeTime(LifeTimeIn) {}

bool OBJECT::CountDown(double t)
{
	return false;
}
void OBJECT::Reincarnation(vector<shared_ptr<OBJECT>>& v, int j, double t) {}

bool OBJECT::DidIHitYou(double X, double Y, double M)
{
	if (sqrt(pow(Xco - X, 2) + pow(Yco - Y, 2)) < (Mass + M)) {
		return true;
	}
	else
		return false;
}
bool OBJECT::CheckCollision(shared_ptr<OBJECT> o) {
	return (o->DidIHitYou(Xco, Yco, Mass));
}
bool OBJECT::PlayerCollision(shared_ptr<PLAYER> o, double& score, vector<shared_ptr<PLAYER>>& v, vector<shared_ptr<OBJECT>>& v2, double t, int j, double& g) { return false; }

void OBJECT::Grow(double x)
{
	Mass += (0.7 * x);
}
bool OBJECT::OthersCollision(shared_ptr<OBJECT> o) {
	if (CompareMass(o) == true) {
		IncreaseMass(o);
		return true;
	}
	else {
		return false;
	}
}

void OBJECT::Draw()
{}
void OBJECT::ShowCount(double t) {}
bool OBJECT::AmIInRange(double X, double Y) {
	if (sqrt(pow(Xco - X, 2) + pow(Yco - Y, 2)) < (3 * Mass)) {
		return true;
	}
	else {
		return false;
	}
}
bool OBJECT::WillIDetonate(shared_ptr<OBJECT>o) {
	return(o->AmIInRange(Xco, Yco));
}



void OBJECT::IncreaseMass(shared_ptr<OBJECT> a)
{
	Mass += a->Mass / 4;
}

void OBJECT::BadCollision(shared_ptr<OBJECT> a)
{
	a->Mass -= Mass / 10;
	Mass += a->Mass / 20;
}
double OBJECT::IncreaseScore(double x, shared_ptr<OBJECT> a)
{
	return	x += a->Mass;
}
bool OBJECT::CompareMass(shared_ptr<OBJECT> a)
{
	return(Mass >= a->Mass);
}

void OBJECT::CreateBH(vector<shared_ptr<BLACKHOLE>>& v,double t)
{
	auto a = make_shared<BLACKHOLE>(p, Xco, Yco,t);
	v.push_back(a);
}
void OBJECT::CreateBOMB(vector<shared_ptr<BOMB>>& v, double t) {
	auto a = make_shared<BOMB>(p, Xco, Yco, t);
	v.push_back(a);
}
void OBJECT::BlackMove(double t, shared_ptr<OBJECT> a)
{
	Xco -= ((double)(Xco - a->Xco) / (2*Mass)) * t;
	Yco -= ((double)(Yco - a->Yco) / (2*Mass)) * t;
}