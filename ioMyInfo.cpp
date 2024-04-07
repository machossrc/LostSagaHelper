#include "StdAfx.h"
#include "ioMyInfo.h"
#include "MemoryManager.h"
#include "GameProcess.h"
#include "Offset.h"

ioMyInfo* ioMyInfo::sg_Instance = NULL;


ioMyInfo& ioMyInfo::GetInstance()
{
	if (sg_Instance == NULL)
		sg_Instance = new ioMyInfo;
	return *sg_Instance;
}

void ioMyInfo::InitMyInfo()
{
	/*ms_Singleton = g_Memory.RPM<ioMyInfo*>(MyInfoBase);
	printf("Init MyInfo : %p", ms_Singleton);
	printf("PublicID : %s\n", m_public_id.c_str());*/
}

ioMyInfo::ioMyInfo()
{

}

ioMyInfo::~ioMyInfo()
{

}

int ioMyInfo::GetCharCount()
{
	int(__thiscall * _GetCharCount)(DWORD * pThis) = reinterpret_cast<int(__thiscall*)(DWORD * pThis)>(g_GameMgr.m_dwGetCharCountFunc); //8B 81 EC 00 00 00 8B 48 04 2B 08 B8 11 F0 FE 10 F7 E9 C1 FA 07 8B C2 C1 E8 1F 03 C2 C3 CC CC CC 55 8B EC 51 56 8D 45 FC 8B F1 8B 4D 08 50 C7 45 FC FF
	
	DWORD MyInfo = g_Memory.RPM<DWORD>(MyInfoBase);
	if (MyInfo)
	{
		return _GetCharCount((DWORD*)MyInfo);
	}
}

int ioMyInfo::GetClassArray(int iClassType) // -1을 반환한다면
{
	DWORD MyInfo = g_Memory.RPM<DWORD>(MyInfoBase);
	int(__thiscall * _GetClassArray)(DWORD * pThis, int) = reinterpret_cast<int(__thiscall*)(DWORD * pThis, int)>(g_GameMgr.m_dwGetClassArrayFunc); //55 8B EC 51 53 56 57 8B F9 89 7D FC 33 DB E8 5D AC FF FF 85 C0 7E 5D 33 F6 EB 08 EB 03 8D 49 00 8B 7D FC 8B 87 EC 00 00 00 8B 08 8B 50 04 2B D1 B8 11
	return _GetClassArray((DWORD*)MyInfo, iClassType);
}