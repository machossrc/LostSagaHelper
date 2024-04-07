#include "StdAfx.h"
#include "HeroSetting.h"

using namespace std;

template<> HeroSetting* Singleton<HeroSetting>::ms_Singleton = 0;

HeroSetting& HeroSetting::GetSingleton()
{
	return Singleton<HeroSetting>::GetSingleton();
}

HeroSetting::HeroSetting()
{
}

HeroSetting::~HeroSetting()
{
}

void HeroSetting::LoadTimeGateToGhostArmor(INILoader& rkLoader)
{
	m_TimeGateToGhostArmor.iClassType = rkLoader.LoadInt("ClassType", 0);
	m_TimeGateToGhostArmor.fApplyRange = rkLoader.LoadFloat("ApplyRange", 350.0f);
	m_TimeGateToGhostArmor.fApplyUpHeight = rkLoader.LoadFloat("ApplyUpHeight", 150.0f);
	m_TimeGateToGhostArmor.fApplyUnderHeight = rkLoader.LoadFloat("ApplyUnderHeight", 150.0f);
}

bool HeroSetting::IsTimeGateWeaponAttackMe(float fRange, float fHeight)
{
	if (fRange <= /*m_TimeGateToGhostArmor.fApplyRange*/350.0f && fHeight <= /*m_TimeGateToGhostArmor.fApplyUpHeight*/150.0f /*&& fHeight <= m_TimeGateToGhostArmor.fApplyUnderHeight*/)
	{
		return true;
	}
	return false;
}