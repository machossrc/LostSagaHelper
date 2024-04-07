#pragma once
#include "Singleton.h"
#include "SP2Packet.h"
class ioBaseChar;

class GameManager : public Singleton<GameManager>
{
private:
	DWORD m_dwApp;
public:
	void GetINIPath(char * szPath);

	void OnLoadINISetting();

	bool MemoryInit();

	void GameProcess();



public:
	void SetSystemMsg(const char* szSource, ...);
	void SendToServer(SP2Packet& rkPacket);
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