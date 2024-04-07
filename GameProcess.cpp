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

GameManager* GameManager::sg_Instance = NULL;

GameManager& GameManager::GetInstance()
{
	if (sg_Instance == NULL)
		sg_Instance = new GameManager;
	return *sg_Instance;
}

GameManager::GameManager()
{
	m_dwApp = 0;
	m_dwMyInfo = 0;

	m_dwSetSystemMsgFunc = 0;
	m_dwSendToServerFunc = 0;
	m_dwGetEquipedSkillFunc = 0;
	m_dwGetCharCountFunc = 0;
	m_dwGetClassArrayFunc = 0;
}

GameManager::~GameManager()
{

}

void GameManager::GetINIPath(char* szPath)
{
	char szBuf[MAX_PATH];
	SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, szBuf);
	strcat(szBuf, "\\LSHelper.ini");
	strcpy(szPath, szBuf);
}

void GameManager::OnLoadINISetting()
{
	char szPath[MAX_PATH];
	GetINIPath(szPath);

	//cout << "INIPath : " << szPath << endl;

	INILoader kLoader(szPath);
	kLoader.SetTitle("TimeGateToGhostArmor");
	g_Setting.LoadTimeGateToGhostArmor(kLoader);

	//더 추가
}

bool GameManager::MemoryInit()
{
	OnLoadINISetting();

	DWORD dwMemoryInitTime = GetTickCount();
	while (true)
	{
		DWORD dwAddress = 0;
		dwAddress = g_Memory.AobScan("8D 4E 20 88 5D FC E8 ?? ?? ?? ?? 89 1D ?? ?? ?? ?? 8B 4D F4 64 89 0D 00 00 00 00 59 5F 5E 5B", 0x01200000, 0x01500000) + 0xB;
		string szOperand = g_Memory.GetOperand(dwAddress, 0);
		m_dwApp = g_Memory.ParseOperand(szOperand);

		m_dwSetSystemMsgFunc = g_Memory.AobScan("55 8B EC 80 3D DD 54 80 02 00 75 6F 57 8B 7D 08 6A 02 8B CF E8 27 AD FF FF FF 15 A4 4C 41 02 84 C0 74 39 8B 4D 0C 56 8D 45 10 50 51 8D 77 3C 68 FF 03", 0x01D00000, 0x01E00000);
		m_dwSendToServerFunc = g_Memory.AobScan("55 8B EC 8B 45 08 50 E8 74 32 3D FF 8B C8 E8 AD 38 3D FF 5D C3 CC CC CC CC CC CC CC CC CC CC CC 55 8B EC 8B 45 08 50 E8 54 32 3D FF 8B C8 E8 4D 21 40", 0x02070000, 0x02080000);
		m_dwGetEquipedSkillFunc = g_Memory.AobScan("55 8B EC 8B 55 08 83 FA 08 77 1F 8B 81 94 00 00 00 80 B8 24 03 00 00 00 75 08 8B 44 91 48 85 C0 75 22 8B 44 91 24 5D C2 04 00 8B 0D 68 33 41 02 52 68", 0x01910000, 0x01920000);

		m_dwGetCharCountFunc = g_Memory.AobScan("8B 81 EC 00 00 00 8B 48 04 2B 08 B8 11 F0 FE 10 F7 E9 C1 FA 07 8B C2 C1 E8 1F 03 C2 C3 CC CC CC 55 8B EC 51 56 8D 45 FC 8B F1 8B 4D 08 50 C7 45 FC FF", 0x014E0000, 0x014F0000);
		m_dwGetClassArrayFunc = g_Memory.AobScan("55 8B EC 51 53 56 57 8B F9 89 7D FC 33 DB E8 5D AC FF FF 85 C0 7E 5D 33 F6 EB 08 EB 03 8D 49 00 8B 7D FC 8B 87 EC 00 00 00 8B 08 8B 50 04 2B D1 B8 11", 0x014E0000, 0x014F0000);


		if (m_dwApp != 0 && m_dwSetSystemMsgFunc != 0 && m_dwSendToServerFunc != 0 && m_dwGetEquipedSkillFunc != 0 && m_dwGetCharCountFunc != 0 && m_dwGetClassArrayFunc != 0)
		{
			m_dwMyInfo = m_dwApp + 0x3F0;
			printf("AppBase : %p\n", m_dwApp);
			printf("MyInfoBase : %p\n", m_dwMyInfo);
			printf("SetSystemMsgFunc : %p\n", m_dwSetSystemMsgFunc);
			printf("SendToServerFunc : %p\n", m_dwSendToServerFunc);
			printf("GetEquipedSkillFunc : %p\n", m_dwGetEquipedSkillFunc);
			printf("GetCharCountFunc : %p\n", m_dwGetCharCountFunc);
			printf("GetEquipedSkillFunc : %p\n", m_dwGetClassArrayFunc);
			break;
		}


		DWORD dwGapTime = GetTickCount() - dwMemoryInitTime;
		if (dwGapTime > 10000) //10초이상 값을 못찾을 경우
		{
			dwMemoryInitTime = GetTickCount();
			return false;
		}

		Sleep(100);
	}

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
			OnLoadINISetting();

			//cout << g_MyInfo.GetClassArray(6) << endl;
			//cout << g_MyInfo.GetClassArray(162) << endl;

			//cout << "6 : " << g_MyInfo.GetCharIndex(g_MyInfo.GetClassArray(6)) << endl;
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
						const DWORD TempWaitTime = pSkill->GetSkillWaitTime();
						if (pSkill->IsTimeGateWeaponSkill())
						{
							printf("티메가테 무기스킬.\n");
							const float fRange = pOwner->GetRangeDiff(pChar);
							const float fHeight = pOwner->GetHeightDiff(pChar);

							printf("Range : %f, Height : %f\n",fRange,fHeight);

							if (g_Setting.IsTimeGateWeaponAttackMe(fRange, fHeight))
							{
								printf("티메가테 무기스킬 좌표 체크 ok.\n");

								int iClassArray = g_MyInfo.GetClassArray(g_Setting.GetTimeGateToGhostArmorClassType());
								if (iClassArray != -1)
								{
									pOwner->SendChangeChar(iClassArray);
								}
							}
							Sleep(TempWaitTime);
						}
						break;
						/*else
						{
							SetSystemMsg("%s 스킬 사용.", pSkill->m_Name.c_str());
							Sleep(TempWaitTime);
						}*/
					}
				}
			}
		}
	}
}

void GameManager::SetSystemMsg(const char* szSource, ...)
{
	DWORD buf = g_Memory.RPM<DWORD>(ChatBase);
	void (*sub_1D789B0)(DWORD*, const char*, ...) = reinterpret_cast<void (*)(DWORD*, const char*, ...)>(g_GameMgr.m_dwSetSystemMsgFunc); //55 8B EC 80 3D DD 54 80 02 00 75 6F 57 8B 7D 08 6A 02 8B CF E8 27 AD FF FF FF 15 A4 4C 41 02 84 C0 74 39 8B 4D 0C 56 8D 45 10 50 51 8D 77 3C 68 FF 03
	sub_1D789B0((DWORD*)buf, szSource);
}

void GameManager::SendToServer(SP2Packet& rkPacket)
{
	void(__cdecl * sub_207E890)(SP2Packet& a1) = reinterpret_cast<void(__cdecl*)(SP2Packet & a1)>(g_GameMgr.m_dwSendToServerFunc); //55 8B EC 8B 45 08 50 E8 74 32 3D FF 8B C8 E8 AD 38 3D FF 5D C3 CC CC CC CC CC CC CC CC CC CC CC 55 8B EC 8B 45 08 50 E8 54 32 3D FF 8B C8 E8 4D 21 40
	sub_207E890(rkPacket);
}

ioBaseChar* GameManager::GetBaseChar(int iOffset)
{
	DWORD c_C = NULL;

	if (IsBadReadPtr((PDWORD)m_dwApp, DM_PROMPT) == NULL)
	{
		c_C = *(PDWORD)((DWORD)(m_dwApp)) + OFS_USERBASE_1;
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
