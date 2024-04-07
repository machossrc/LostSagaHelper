#pragma once
#include "Singleton.h"
#include "INILoader.h"

class HeroSetting : public Singleton<HeroSetting>
{
private:
	struct sTimeGateToGhostArmor
	{
		int iClassType; //해당 장비를 가지고있는 캐릭터
		float fApplyRange;
		float fApplyUpHeight;
		float fApplyUnderHeight;
		
		
		sTimeGateToGhostArmor()
		{
			iClassType = 0;

			fApplyRange = 350.0f;
			fApplyUpHeight = 150.0f;
			fApplyUnderHeight = 150.0f;
		}
	};
	sTimeGateToGhostArmor m_TimeGateToGhostArmor;



public:
	void LoadTimeGateToGhostArmor(INILoader &rkLoader);
	bool IsTimeGateWeaponAttackMe(float fRange, float fHeight);

public:
	static HeroSetting& GetSingleton();
public:
	HeroSetting();
	~HeroSetting();
};

#define g_Setting HeroSetting::GetSingleton()