#include "StdAfx.h"
#include "ioMyInfo.h"
#include "MemoryManager.h"
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
	int(__thiscall * _GetCharCount)(DWORD * pThis) = reinterpret_cast<int(__thiscall*)(DWORD * pThis)>(0x14E9070);
	
	DWORD MyInfo = g_Memory.RPM<DWORD>(MyInfoBase);
	if (MyInfo)
	{
		return _GetCharCount((DWORD*)MyInfo);
	}
}

int ioMyInfo::GetClassArray(int iClassType) // -1을 반환한다면
{
	DWORD MyInfo = g_Memory.RPM<DWORD>(MyInfoBase);
	int(__thiscall * _GetClassArray)(DWORD * pThis, int) = reinterpret_cast<int(__thiscall*)(DWORD * pThis, int)>(0x14EE400);
	return _GetClassArray((DWORD*)MyInfo, iClassType);
}

//int ioMyInfo::GetCharIndex(int array)
//{
//	DWORD MyInfo = g_Memory.RPM<DWORD>(MyInfoBase);
//	int(__thiscall * _GetCharIndex)(DWORD * pThis, int) = reinterpret_cast<int(__thiscall*)(DWORD * pThis, int)>(0x14EE270);
//	return _GetCharIndex((DWORD*)MyInfo, array);
//}
