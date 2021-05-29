#include"BLACKHOLE.h"



	BLACKHOLE::BLACKHOLE(PixelGameEngine* pIn, double Xcoin, double Ycoin, double t) : OBJECT(pIn, Xcoin, Ycoin, 15, BLACK, t + 30) {}
	bool BLACKHOLE::CountDown(double t)
	{

		if (LifeTime - t <= 0)
			return true;
		else
			return false;
	}
	void BLACKHOLE::ShowCount(double t) {
		int x = LifeTime - t;
		p->DrawString(Xco, Yco, to_string(x), WHITE, 1);

	}
	void BLACKHOLE::Draw()
	{
		for (int i = Mass; i > 0; i--)
		{
			if (i % 2 == 0)
				p->FillCircle(Xco, Yco, i, WHITE);
			else
				p->FillCircle(Xco, Yco, i, BLACK);
		}
	}
