#pragma once

class ioBaseChar;

class GameManager
{
public:
	void GameProcess();

public:
	ioBaseChar* GetBaseChar(int iOffset);

private:
	static GameManager* sg_Instance;
public:
	static GameManager& GetInstance();
public:
	GameManager();
	~GameManager();
};

#define g_GameMgr GameManager::GetInstance()