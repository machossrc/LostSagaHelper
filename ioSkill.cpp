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
	if (m_dwPreDelayStartTime == 0)
	{
		return 3000;
	}
	else
	{
		return m_dwPreDelayStartTime;
	}
}

bool ioSkill::IsTimeGateWeaponSkill()
{
	if (this->m_Name == "211MS_SD")
	{
		return true;
	}
	return false;
}
