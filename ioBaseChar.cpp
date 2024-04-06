#include "StdAfx.h"
#include "ioBaseChar.h"
#include "MemoryManager.h"
#include "ioSkill.h"

ioBaseChar::ioBaseChar()
{

}

ioBaseChar::~ioBaseChar()
{

}

int(__stdcall* func_hook_payload)(int a, int b, int c, bool d, bool e) = reinterpret_cast<int(__stdcall*)(int a, int b, int c, bool d, bool e)>(0x17B16D0);
__declspec(naked) void func_hook(int a, int b, int c, bool d, bool e)
{
	__asm {
		push ebp
		mov ebp, esp
		mov ecx, [b] // b
		mov eax, [a] // a
		push byte ptr[e] // e
		push byte ptr[d] // d
		push dword ptr[c] // c
		call func_hook_payload
		leave
		ret
	}
}

void ioBaseChar::SendChangeChar(int iArray, bool bSend)
{

	//func_hook((int)this, (int)this, iArray, bSend, false);

	if (m_iSelectCharArray == iArray)
	{
		return;
	}

	int(__thiscall * sub_175C6D0)(int pThis, unsigned int) = reinterpret_cast<int(__thiscall*)(int , unsigned int)>(0x175C6D0); //void ioBaseChar::SendChangeChar(int iArray)
	sub_175C6D0((int)this, iArray);
	//ioBaseChar, ioGameEntity, 


	//double (__userpurge *sub_17B16D0@)<st0>(int a1@<ecx>, int a2@<edi>, double result@<st0>, int a4@<ebx>, unsigned int a5, char a6, char a7)

	/*int(__thiscall * sub_15E0A30)(ioBaseChar * pBaseChar, int, bool) = reinterpret_cast<int(__thiscall*)(ioBaseChar*, int, bool)>(0x17B16D0);
	sub_15E0A30(this, iArray, bSend);*/


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

ioSkill* ioBaseChar::GetEquipedSkill(int iSkillNum)
{
	ioSkill*(__thiscall * GetEquipedSkill)(DWORD * pThis, unsigned int) = reinterpret_cast<ioSkill*(__thiscall*)(DWORD * pThis, unsigned int)>(0x01913ED0);
	return GetEquipedSkill((DWORD*)this->m_pEquipSlot, iSkillNum);
}

bool ioBaseChar::IsOwnerChar() const
{
	return m_bOwnerChar;
}