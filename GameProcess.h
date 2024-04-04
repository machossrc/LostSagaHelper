#pragma once
#include "Singleton.h"
class ioBaseChar;

class GameManager : public Singleton<GameManager>
{
public:
	void GameProcess();

public:
	ioBaseChar* GetBaseChar(int iOffset);

public:
	static GameManager& GetSingleton();
public:
	GameManager();
	~GameManager();
};

#define g_GameMgr GameManager::GetSingleton()