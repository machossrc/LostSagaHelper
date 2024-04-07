#pragma once
#include "SP2Packet.h"
class ioBaseChar;

class GameManager
{
public:
	DWORD m_dwApp;
	DWORD m_dwMyInfo;
	DWORD m_dwSetSystemMsgFunc;
	DWORD m_dwSendToServerFunc;
	DWORD m_dwGetEquipedSkillFunc;
	DWORD m_dwGetCharCountFunc;
	DWORD m_dwGetClassArrayFunc;
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

private:
	static GameManager* sg_Instance;
public:
	static GameManager& GetInstance();
public:
	GameManager();
	~GameManager();
};

#define g_GameMgr GameManager::GetInstance()