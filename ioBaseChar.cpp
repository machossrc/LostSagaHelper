#include "StdAfx.h"
#include "ioBaseChar.h"
#include "MemoryManager.h"

ioBaseChar::ioBaseChar()
{

}

ioBaseChar::~ioBaseChar()
{

}

int ioBaseChar::GetState()
{
	return m_iCharState;
}

ioHashString ioBaseChar::GetPublicID()
{
	return m_szName;
}

bool ioBaseChar::HasSkill(int iIndex)
{
	return GetMaxSkillByIndex(iIndex) > 0 ? GetMaxSkillByIndex(iIndex) <= GetCurSkillByIndex(iIndex) : false;
}

float ioBaseChar::GetCurSkillByIndex(int iIndex)
{
	DWORD Buf = g_Memory.RPM<DWORD>((DWORD)&m_pEquipSlot);
	Buf = g_Memory.RPM<DWORD>(Buf + iIndex * 0x4);
	return g_Memory.RPM<float>(Buf + 0x41C);
}

float ioBaseChar::GetMaxSkillByIndex(int iIndex)
{
	DWORD Buf = g_Memory.RPM<DWORD>((DWORD)&m_pEquipSlot);
	Buf = g_Memory.RPM<DWORD>(Buf + iIndex * 0x4);
	return g_Memory.RPM<float>(Buf + 0x41C - sizeof(CEncrypt<float>));
}

D3DXVECTOR3 ioBaseChar::GetPosition()
{
	DWORD Buf = g_Memory.RPM<DWORD>((DWORD) & m_pPosition);
	Buf = g_Memory.RPM<DWORD>(Buf + 0x8);

	D3DXVECTOR3 k(g_Memory.RPM<float>(Buf + 0x3C), g_Memory.RPM<float>(Buf + 0x40), g_Memory.RPM<float>(Buf + 0x44));
	return k;
}

bool ioBaseChar::IsOwnerChar() const
{
	return m_bOwnerChar;
}