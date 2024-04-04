#pragma once
class GameManager
{
private:
	static GameManager* sg_Instance;
public:
	static GameManager& GetInstance();
public:
	GameManager();
	~GameManager();
};

#define g_GameMgr GameManager::GetInstance()