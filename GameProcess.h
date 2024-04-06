#pragma once
#include "Singleton.h"
class ioBaseChar;

class GameManager : public Singleton<GameManager>
{
private:
	DWORD m_dwApp;
public:
	bool MemoryInit();

	void GameProcess();

public:


	ioBaseChar* GetBaseChar(int iOffset);
	ioBaseChar* GetOwnerChar();
	ioBaseChar* GetBaseChar(const char * szName);
	int GetBaseCharSize();
public:
	static GameManager& GetSingleton();
public:
	GameManager();
	~GameManager();
};

#define g_GameMgr GameManager::GetSingleton()