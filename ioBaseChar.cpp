#include "StdAfx.h"
#include "ioBaseChar.h"
#include "MemoryManager.h"
#include "ioSkill.h"
#include "SP2Packet.h"
#include "GameProcess.h"

ioBaseChar::ioBaseChar()
{

}

ioBaseChar::~ioBaseChar()
{

}

int(__stdcall* func_hook_payload)(int a, int b, int c, bool d, bool e) = reinterpret_cast<int(__stdcall*)(int a, int b, int c, bool d, bool e)>(0x017B16D0);
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

	//int(__thiscall * sub_175C6D0)(int pThis, unsigned int) = reinterpret_cast<int(__thiscall*)(int , unsigned int)>(0x175C6D0); //void ioBaseChar::SendChangeChar(int iArray)
	//sub_175C6D0((int)this, iArray);
	//Oridinal Use  IT

	SP2Packet kPacket(0x0017);
	kPacket << iArray;
	kPacket << true;
	kPacket << GetCharChangeUniqueIndex() + 1;
	g_GameMgr.SendToServer(kPacket);





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

float ioBaseChar::GetPositionHeight()
{
	DWORD Buf = g_Memory.RPM<DWORD>((DWORD)&m_pPosition);
	Buf = g_Memory.RPM<DWORD>(Buf + 0x8);
	return g_Memory.RPM<float>(Buf + 0x40);
}

float ioBaseChar::GetPositionRange()
{
	DWORD Buf = g_Memory.RPM<DWORD>((DWORD)&m_pPosition);
	Buf = g_Memory.RPM<DWORD>(Buf + 0x8);
	return g_Memory.RPM<float>(Buf + 0x40);
}

ioSkill* ioBaseChar::GetEquipedSkill(int iSkillNum)
{
	ioSkill*(__thiscall * GetEquipedSkill)(DWORD * pThis, unsigned int) = reinterpret_cast<ioSkill*(__thiscall*)(DWORD * pThis, unsigned int)>(g_GameMgr.m_dwGetEquipedSkillFunc); //55 8B EC 8B 55 08 83 FA 08 77 1F 8B 81 94 00 00 00 80 B8 24 03 00 00 00 75 08 8B 44 91 48 85 C0 75 22 8B 44 91 24 5D C2 04 00 8B 0D 68 33 41 02 52 68
	return GetEquipedSkill((DWORD*)this->m_pEquipSlot, iSkillNum);
}

bool ioBaseChar::IsOwnerChar() const
{
	return m_bOwnerChar;
}

int ioBaseChar::GetTeam() const
{
	return m_iTeam;
}

float ioBaseChar::GetHeightDiff(ioBaseChar* pChar)
{
	return abs(this->GetPositionHeight() - pChar->GetPositionHeight());
}

float ioBaseChar::GetRangeDiff(ioBaseChar* pChar)
{
	D3DXVECTOR3 kMyPos = this->GetPosition();
	D3DXVECTOR3 kEnemyPos = pChar->GetPosition();

	float fDistX = kMyPos.x - kEnemyPos.x;
	float fDistZ = kMyPos.z - kEnemyPos.z;

	return sqrt(fDistX * fDistX + fDistZ * fDistZ);
}