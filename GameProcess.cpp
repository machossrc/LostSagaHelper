#include "StdAfx.h"
#include "GameProcess.h"
#include "MemoryManager.h"
#include "ioBaseChar.h"
#include "ioMyInfo.h"
#include "ioSkill.h"
#include "Offset.h"
#include "HeroSetting.h"
#include <ShlObj.h>

using namespace std;

template<> GameManager* Singleton<GameManager>::ms_Singleton = 0;

GameManager& GameManager::GetSingleton()
{
	return Singleton<GameManager>::GetSingleton();
}

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

void GameManager::GetINIPath(char* szPath)
{
	char szBuf[MAX_PATH];
	SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, szBuf);
	strcat(szBuf, "\\GAME.ini");
	strcpy(szPath, szBuf);
}

void GameManager::OnLoadINISetting()
{
	char szPath[MAX_PATH];
	GetINIPath(szPath);

	INILoader kLoader(szPath);
	kLoader.SetTitle("TimeGateToGhostArmor");
	g_Setting.LoadTimeGateToGhostArmor(kLoader);

	//더 추가
}

bool GameManager::MemoryInit()
{

	//DWORD dwMemoryInitTime = GetTickCount();
	//while (true)
	//{
	//	DWORD dwAddress = 0;
	//	dwAddress = g_Memory.AobScan("8D 4E 20 88 5D FC E8 ?? ?? ?? ?? 89 1D ?? ?? ?? ?? 8B 4D F4 64 89 0D 00 00 00 00 59 5F 5E 5B", 0x01200000, 0x01500000) + 0xB;
	//	string szOperand = g_Memory.GetOperand(dwAddress, 0);
	//	m_dwApp = g_Memory.ParseOperand(szOperand);

	//	if (m_dwApp != 0)
	//	{
	//		break;
	//	}

	//	DWORD dwGapTime = GetTickCount() - dwMemoryInitTime;
	//	if (dwGapTime > 10000) //10초이상 값을 못찾을 경우
	//	{
	//		dwMemoryInitTime = GetTickCount();
	//		return false;
	//	}

	//	Sleep(100);
	//}

	return true;
}

void GameManager::GameProcess()
{
	bool InitMyInventoryData = false;

	while (true)
	{
		Sleep(10);

		/*if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			ioBaseChar* pOwner = GetOwnerChar();
			if (pOwner)
			{
				ioSkill* pSkill = pOwner->GetEquipedSkill(0);
				if (pSkill)
				{
					printf("GroupName : %s\n", pSkill->m_GroupName.c_str());
					printf("SkillName : %s\n", pSkill->m_Name.c_str());
					printf("m_DescName : %s\n", pSkill->m_DescName.c_str());

					printf("SkillUseType : %d, PTR : %p\n",pSkill->m_SkillUseType, &pSkill->m_SkillUseType);
					printf("SkillMotionName : %s, PTR : %p\n",pSkill->m_SkillMotionName.c_str(), &pSkill->m_SkillMotionName);
					printf("AnimationTimeRate : %f, PTR : %p\n",pSkill->m_fAnimationTimeRate, &pSkill->m_fAnimationTimeRate);
					printf("PreDelayAnimation : %s, PTR : %p\n",pSkill->m_PreDelayAnimation.c_str(), &pSkill->m_PreDelayAnimation);
					printf("PreDelayOwnerEffect : %s, PTR : %p\n",pSkill->m_PreDelayOwnerEffect.c_str(), &pSkill->m_PreDelayOwnerEffect);
					printf("DownSkillMotionName : %s, PTR : %p\n",pSkill->m_DownSkillMotionName.c_str(), &pSkill->m_DownSkillMotionName);
					printf("IconName : %s, PTR : %p\n",pSkill->m_IconName.c_str(), &pSkill->m_IconName);
					
					printf("PreDelayStartTime : %d, PTR : %p\n",pSkill->m_dwPreDelayStartTime, &pSkill->m_dwPreDelayStartTime);
					printf("m_dwMotionStartTime : %d, PTR : %p\n",pSkill->m_dwMotionStartTime, &pSkill->m_dwMotionStartTime);
					
				}
			}
		}*/

		if (GetAsyncKeyState(VK_INSERT) & 1)
		{

		}


		ioBaseChar* pOwner = GetOwnerChar();
		if (!pOwner)
		{
			continue;
		}

		for (int i = 0; i < 32; i++)
		{
			ioBaseChar* pChar = GetBaseChar(i * 0x4);
			if (pChar && pChar->GetState() == 7 && (pOwner != pChar) && (pOwner->GetTeam() != pChar->GetTeam()))
			{
				for (int j = 0; j < 4; j++)
				{
					ioSkill* pSkill = pChar->GetEquipedSkill(j);
					if (pSkill && pSkill->IsSkillStart()) //스킬 시전중
					{
						if (pSkill->IsTimeGateWeaponSkill())
						{
							float fRange = pOwner->GetRangeDiff(pChar);
							float fHeight = pOwner->GetHeightDiff(pChar);
							if (g_Setting.IsTimeGateWeaponAttackMe(fRange, fHeight))
							{
								printf("티메가테 무기스킬.\n");
								pOwner->SendChangeChar(1);
								Sleep(pSkill->GetSkillWaitTime());
							}
						}
					}
				}
			}
		}
	}
}

ioBaseChar* GameManager::GetBaseChar(int iOffset)
{
	DWORD c_C = NULL;

	if (IsBadReadPtr((PDWORD)PlayerBase, DM_PROMPT) == NULL)
	{
		c_C = *(PDWORD)((DWORD)(PlayerBase)) + OFS_USERBASE_1;
		if (IsBadReadPtr((PDWORD)c_C, DM_PROMPT) == NULL)
		{
			c_C = *(PDWORD)((DWORD)(c_C)) + OFS_USERBASE_2;
			if (IsBadReadPtr((PDWORD)c_C, DM_PROMPT) == NULL)
			{
				c_C = *(PDWORD)((DWORD)(c_C)) + iOffset;
				if (IsBadReadPtr((PDWORD)c_C, DM_PROMPT) == NULL)
				{
					c_C = *(PDWORD)((DWORD)(c_C)) + OFS_USERBASE_4;
					if (IsBadReadPtr((PDWORD)c_C, DM_PROMPT) == NULL)
					{
						c_C = *(PDWORD)((DWORD)(c_C)) + OFS_USERBASE_5;
						if (IsBadReadPtr((PDWORD)c_C, DM_PROMPT) == NULL)
						{
							c_C = *(PDWORD)((DWORD)(c_C)) + 0;
							if (IsBadReadPtr((PDWORD)c_C, DM_PROMPT) == NULL)
							{
								return (ioBaseChar*)c_C;
							}
						}
					}
				}
			}
		}
	}

	return nullptr;
}

ioBaseChar* GameManager::GetOwnerChar()
{
	for (int i = 0; i < 32; i++)
	{
		ioBaseChar* pChar = GetBaseChar(i * 0x4);
		if (pChar && pChar->IsOwnerChar())
		{
			return pChar;
		}
	}
	return nullptr;
}

ioBaseChar* GameManager::GetBaseChar(const char* szName)
{
	for (int i = 0; i < 32; i++)
	{
		ioBaseChar* pChar = GetBaseChar(i * 0x4);
		if (pChar && pChar->GetPublicID() == szName)
		{
			return pChar;
		}
	}
	return nullptr;
}

int GameManager::GetBaseCharSize()
{
	int iCnt = 0;

	ioBaseChar* pOwner = GetOwnerChar();
	if (pOwner)
	{
		ioPlayStage* pStage = pOwner->m_pCreator;
		if (pStage)
		{
			BaseCharList::iterator iter = pStage->m_BaseCharList.begin();

			for (; iter != pStage->m_BaseCharList.end(); ++iter)
			{
				iCnt++;
			}
		}

	}

	return iCnt;
}
