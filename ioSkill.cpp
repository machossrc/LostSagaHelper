#include "StdAfx.h"
#include "ioSkill.h"

using namespace std;

bool ioSkill::IsSkillStart()
{
	if (m_dwPreDelayStartTime > 0)
	{
		return true;
	}
	return false;
}

DWORD ioSkill::GetSkillWaitTime()
{
	return m_dwPreDelayTime;
}

bool ioSkill::IsTimeGateWeaponSkill()
{
	if (this->m_Name == "211MS_SD")
	{
		return true;
	}
	return false;
}

bool ioSkill::IsBrujoHelmetSkill()
{
	if (this->m_Name == "055ES_brujo_ad_powerup_02") //±Ã±ØÁøÈ­
	{
		return true;
	}
	return false;
}