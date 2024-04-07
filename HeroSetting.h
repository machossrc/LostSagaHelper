#pragma once
#include "INILoader.h"

class HeroSetting
{
private:
	int m_iTimeGateToGhostArmorClassType;

public:
	void LoadTimeGateToGhostArmor(INILoader &rkLoader);

	inline int GetTimeGateToGhostArmorClassType() { return m_iTimeGateToGhostArmorClassType; };
	bool IsTimeGateWeaponAttackMe(float fRange, float fHeight);

private:
	static HeroSetting* sg_Instance;
public:
	static HeroSetting& GetInstance();

public:
	HeroSetting();
	~HeroSetting();
};

#define g_Setting HeroSetting::GetInstance()