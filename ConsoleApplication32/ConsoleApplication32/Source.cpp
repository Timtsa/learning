#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include<iostream>
#include <string>
#include<vector>
#include <list>
using namespace std;

class Shot
{
	float shotX;
	float shotY;
	float shotHigt = 15;
	float shotWeigt = 5;
public:
	Shot(float _shotX, float _shotY) : shotX(_shotX), shotY(_shotY)
	{};
	
	float GetX()
	{
		return shotX;
	}
	float GetY()
	{
		return shotY;
	}
	float GetShotWeigt()
	{
		return shotWeigt;
	}

	float GetShotHigt()
	{
		return shotHigt;
	}

	void SetY()
	{
		shotY -= 10.0f;
	}
};


class Unit
{
public:
	static int ident;
	Unit (float _sheapX,float _ShearY)
	{
		sheapX = _sheapX;
		sheapY = _ShearY;
		sheapDX = 10;
	}
	Unit()
	{
		sheapX = 0;
		sheapY = 0;
		sheapDX = 10;
		ident++;
	}
    virtual	float GetSheapX()
	{
		return Unit::sheapX;
	}
	virtual float GetsheapY()
	{
		return Unit::sheapY;
	}
	virtual float GetsheapDX()
	{
		return Unit::sheapDX;
	}
	virtual int GetId() { return -1; };
	
	virtual float GetSheapHigt() { return sheapHigt; }

	virtual float GetSheapWeigt() { return sheapWeigt; }

	virtual void SetSheapX(float _sheapX)
	{
		Unit::sheapX = _sheapX;
	}
	virtual void SetSheapY(float _sheapY)
	{
		Unit::sheapY = _sheapY;
	}
	virtual void SetSheapDX(float _sheapDX)
	{
		Unit::sheapDX = _sheapDX;
	}
	virtual bool CollisionCheck(float _shotX, float _shotY, float _shotWeigt, float _shotHigt)
	{
		return false;
	};

protected:
	
	float sheapX;
	float sheapY;
	float sheapDX;
	float sheapHigt =50;
	float sheapWeigt = 50;
};
int Unit::ident = -1;
class Sheap: public Unit
{
public:
	Sheap ():Unit (375,649)
	{	}
	float GetSheapX()
	{
		return Unit::sheapX;
    }
	float GetsheapY()
	{
		return Unit::sheapY;
	}
	
	virtual float GetsheapDX()
	{
		return Unit::sheapDX;
	}
	int GetId() { return -2; };
	void SetSheapX(float _sheapX)
	{
		Unit::sheapX = _sheapX;
	}


	void SetSheapY(float _sheapY)
	{
		Unit::sheapY = _sheapY;
	}
	virtual void SetSheapDX(float _sheapDX)
	{
		Unit::sheapDX = _sheapDX;
	}
    bool CollisionCheck(float _shotX, float _shotY)
	{  
		return false;
	};

};

class Enemy : public Unit
{
	int id;
public:
	Enemy() :Unit()
	{
		int line = 9;
		id = Unit::ident;
		int row = id/line;		
		float x =50;
		if(row<1)
		{
			x = x + 75 * id;
		}
		else
		{
			x = x + 75 * (id - (line * row));
		}
		
		float y = 30+(75*row);
		


		Unit::SetSheapX(x);
		Unit::SetSheapY(y);

	}
	float GetSheapX()
	{
		return Unit::sheapX;
	}
	float GetsheapY()
	{
		return Unit::sheapY;
	}
	int GetId() { return id; };
	
	virtual float GetsheapDX()
	{
		return Unit::sheapDX;
	}

	void SetSheapX(float _sheapX)
	{
		Unit::sheapX = _sheapX;
	}


	void SetSheapY(float _sheapY)
	{
		Unit::sheapY = _sheapY;
	}
	virtual void SetSheapDX(float _sheapDX)
	{
		Unit::sheapDX = _sheapDX;
	}
	
	
	bool CollisionCheck(float _shotX, float _shotY, float _shotWeigt, float _shotHigt)
	{ 
		
		if (this->GetSheapX() < _shotX + _shotWeigt &&
			this->GetSheapX() + this->GetSheapWeigt() > _shotX &&
			this->GetsheapY() < _shotY + _shotHigt &&
			this->GetsheapY() + this->GetSheapHigt() > _shotY)
		{
			return true;
		}


		//if ((this->GetsheapY()+50.0f) >= _shotY)
		//{
		//	/*cout << "Checking unit " << id << "Unit X: " << GetSheapX() << "Bullet X: " << _shotX <<  endl;
		//	cout << "X=" << _shotX << "::" << "Y=" << _shotY << endl;*/
		//		for (int j = 0; j < 4; j++)
		//		{
		//			cout << "Checking unit " << id << "Unit X: " << GetSheapX() << "Bullet X: " << _shotX << endl;
		//			cout << "!";
		//			if ((this->GetSheapX()>=_shotX+j)&&((this->GetSheapX()+50.0f)<=_shotX+j))
		//			{
		//				
		//				return true;
		//			}
		//			
		//		}
		//	
		//}
		//return false;
		return false;
	};

};


class Exemple : public olc::PixelGameEngine
{
public:
	list < Unit*> SomeUnit;
	Unit* Player;
	vector <Shot*> SomeShot;
	float fTimeSinceStart = 0.0f;
	olc::Sprite defender;
	olc::Sprite sheap;
	Exemple()
	{
		sAppName = "Exemple";
	};
public:

	bool OnUserCreate() override
	{

		for (int i = 0; i < 27; i++)
		{
			SomeUnit.push_back(new Enemy());
			

		}
		cout << endl;
		Player = new Sheap();
		defender.LoadFromFile(string("1.png"));
		sheap.LoadFromFile((string("2.png")));
		
		return true;

	}

	bool OnUserUpdate(float	fElapsedTime) override
	{
		for (auto Shot : SomeShot)
		{
			Shot->SetY();
		}


		FillRect(0, 0, ScreenWidth(), ScreenHeight() - 1, olc::BLACK);

		if (IsFocused())
		{
			if (GetKey(olc::Key::LEFT).bHeld)
			{
				if (Player->GetSheapX() > 0)
				{
					Player->SetSheapX(Player->GetSheapX() - 100.0f*fElapsedTime);
				}

			}
			if (GetKey(olc::Key::RIGHT).bHeld)
			{
				if (Player->GetSheapX() < ScreenWidth() - 50)
				{
					Player->SetSheapX(Player->GetSheapX() + 100.0f*fElapsedTime);
				}

			}
			if (GetKey(olc::Key::SPACE).bPressed)
				SomeShot.push_back(new Shot((Player->GetSheapX() + 21), (Player->GetsheapY() + 5)));                                      /* (Shot((Player->GetSheapX() + 0), (Player->GetsheapY()+5)));*/

		}


		if (SomeShot.capacity() > 0)
		{
			for (auto Shot : SomeShot)
			{
				DrawRect(Shot->GetX(), Shot->GetY(), 5, 15);

			}
		}

	/*	if (SomeShot.capacity() > 0)
		{
			auto it = SomeShot.begin();
			while (it != SomeShot.end())
			{
				if ((*it)->GetY() < 0)
				{
					it = SomeShot.erase(it);
				}
				else
				{
					++it;
				}

			}

		}*/

			/*if (SomeShot.capacity() > 0)
			{
				for (auto Shot : SomeShot)
				{
					cout << "shot Get X  " << Shot->GetX() << "shot Get Y  " << Shot->GetY() << endl;

				}


			}
*/


			DrawSprite(Player->GetSheapX(), Player->GetsheapY(), &defender, 1);
			if (SomeShot.capacity() > 0)
			{
				auto it = SomeShot.begin();
				while (it != SomeShot.end())
				{
					for (int j = 0; j< SomeUnit.size(); j++)
				    {
						
						
						
						if (SomeUnit.operator= != nullptr&& Unit CollisionCheck((*it)->GetX(), (*it)->GetY(), (*it)->GetShotWeigt(), (*it)->GetShotHigt()))
						
							{
								SomeUnit[j] = nullptr;
								it = SomeShot.erase(it);
							}
						
						else
						{
						j++;
						++it;
						}
						
					}
					
				}
			

			}
			
			
			
			
			//if (SomeShot.capacity() > 0)
			//{
			//	for (int i=0;i< SomeShot.size();i++)
			//	{
			//		
			//		//auto it = SomeUnit.begin();                        // Два Варианта цикла на проверку столкновения и удаления спрайта и оба не рабочие((
			//		//while (it != SomeUnit.end())                // two types of loop for colision chek and dleting sprite. And no one of them not working((
			//		for (int j=0;j< SomeUnit.size();j++)
			//		{
			//			if (SomeUnit[j] != nullptr)
			//			{
			//				if (SomeUnit[j]->CollisionCheck(SomeShot[i]->GetX(), SomeShot[i]->GetY(), SomeShot[i]->GetShotWeigt(), SomeShot[i]->GetShotHigt()))
			//					/*if ((*it)->CollisionCheck(SomeShot[i]->GetX(), SomeShot[i]->GetY(), SomeShot[i]->GetShotWeigt(), SomeShot[i]->GetShotHigt()))*/
			//				{
			//					/*SomeShot.erase(SomeShot.begin() + i);*/
			//					SomeUnit[j] = nullptr;

			//					/**it = nullptr;*/
			//					/*SomeUnit.erase(it);*/
			//					/*SomeUnit.erase(SomeUnit.begin() + j);*/

			//					/*	SomeShot.erase(SomeShot.begin() + i);*/

			//					/*cout << "Uvin id" << SomeUnit[j]->GetId() <<"  i::"<<i<<"  j::"<<j << "::";*/
			//					cout << "BOOM!" << endl;
			//				}
			//			}
			//			else
			//			{
			//				j++;
			//			}

			//		
			//			

			//		}
			//	}
			//}

			
			for (auto Unit : SomeUnit)
			{
				if (Unit!=nullptr)
				DrawSprite(Unit->GetSheapX(), Unit->GetsheapY(), &sheap, 1);
			}





			return true;
		}

};


int main()
{
	Exemple Demo;
	if (Demo.Construct(800,700,1,1))
			Demo.Start();
	
	return 0;
}
