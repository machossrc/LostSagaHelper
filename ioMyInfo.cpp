#include "StdAfx.h"
#include "ioMyInfo.h"
#include "MemoryManager.h"
#include "Offset.h"

template<> ioMyInfo* Singleton<ioMyInfo>::ms_Singleton = 0;

ioMyInfo& ioMyInfo::GetSingleton()
{
	return Singleton<ioMyInfo>::GetSingleton();
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