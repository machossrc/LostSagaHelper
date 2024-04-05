#pragma once
#include "ioHashString.h"
#include "EncryptValue.h"
#include "CharacterInfo.h"

//2432
class ioBaseChar
{
public:
	char Buffer0[464];
	//좌표읽기
	DWORD m_pPosition;
	char Buffer1[260];
	DWORD m_dwIndex;
	int m_iLevel;
	int m_iClassLevel;
	ioHashString m_szName; //16 byte
	ioHashString m_szViewName;

	DWORD m_dwNPCIndex;
	DWORD m_dwUserIndex;

	int m_iCharState; //0x308 776
	int m_iPreCharState;
	int m_iNextCharState;

	char Buffer2[4];

	int m_iLandType;

	int m_iRaceType;

	bool m_bMale;

	int m_iSelectCharArray;

	char Buffer3[24];

	bool m_bJumpAttackEnable;

	char Buffer4[20];

	//CHARACTER
	CHARACTER m_CharInfo;

	char Buffer5[40];


	D3DXQUATERNION m_qtTargetRot;
	D3DXVECTOR3	   m_vMoveDir;
	D3DXVECTOR3	   m_vInputDir;

public:

	int GetState(); //모션
	ioHashString GetPublicID();

	D3DXVECTOR3 GetPosition();

public:
	ioBaseChar();
	~ioBaseChar();
};