#include "StdAfx.h"
#include "HeroSetting.h"

using namespace std;

HeroSetting* HeroSetting::sg_Instance = NULL;

HeroSetting& HeroSetting::GetInstance()
{
	if (sg_Instance == NULL)
		sg_Instance = new HeroSetting;
	return *sg_Instance;
}

HeroSetting::HeroSetting()
{
	//m_iTimeGateToGhostArmorClassType = 0;
}

HeroSetting::~HeroSetting()
{
}

void HeroSetting::LoadTimeGateToGhostArmor(INILoader& rkLoader)
{
	rkLoader.SetTitle("TimeGateToGhostArmor");

	m_iTimeGateToGhostArmorClassType = rkLoader.LoadInt("ClassType", 0);

	printf("TimeGateToGhostArmorClassType : %d\n", m_iTimeGateToGhostArmorClassType);
	
}

bool HeroSetting::IsTimeGateWeaponAttackMe(float fRange, float fHeight)
{
	if (fRange <= /*m_TimeGateToGhostArmor.fApplyRange*/350.0f && fHeight <= /*m_TimeGateToGhostArmor.fApplyUpHeight*/150.0f /*&& fHeight <= m_TimeGateToGhostArmor.fApplyUnderHeight*/)
	{
		return true;
	}
	return false;
}