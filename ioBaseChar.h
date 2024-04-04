#pragma once
#include "ioHashString.h"
#include "EncryptValue.h"
#include "CharacterInfo.h"

class ioBaseChar
{
public:
	char Buffer1[728];
	DWORD m_dwIndex;
	int m_iLevel;
	int m_iClassLevel;
	ioHashString m_szName; //16 byte
	ioHashString m_szViewName;

	DWORD m_dwNPCIndex;
	DWORD m_dwUserIndex;

	int m_iCharState;
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

public:

	int GetState(); //¸ð¼Ç
	ioHashString GetPublicID();

public:
	ioBaseChar();
	~ioBaseChar();
};