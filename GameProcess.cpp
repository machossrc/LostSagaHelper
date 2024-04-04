#include "StdAfx.h"
#include "GameProcess.h"
#include "ioBaseChar.h"
#include "Offset.h"

GameManager* GameManager::sg_Instance = NULL;

GameManager& GameManager::GetInstance()
{
	if (sg_Instance == NULL)
		sg_Instance = new GameManager;
	return *sg_Instance;
}

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

void GameManager::GameProcess()
{
	for (int i = 0; i < 32; i++)
	{
		ioBaseChar* pChar = GetBaseChar(i * 0x4);
		if (pChar)
		{

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