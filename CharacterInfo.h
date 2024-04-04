#pragma once

typedef struct tagAccessoryEquipInfo
{
	CEncrypt<int> m_iAccessoryIdx;
	CEncrypt<int> m_iAccessoryCode;
	CEncrypt<int> m_iRandomNumber;
	CEncrypt<int> m_iCompoundCode;
	CEncrypt<int> m_iCompoundValue;

}AccessoryEquipInfo;

typedef struct tagCostumeEquipInfo
{
	int m_CostumeIdx;
	int m_CostumeCode;
	DWORD m_Costume_Male_Custom;
	DWORD m_Costume_Female_Custom;

}CostumeEquipInfo;

struct CHARACTER
{
	CEncrypt<int>	m_class_type; // + 30 °ª
	CEncrypt<int>	m_kindred;
	CEncrypt<int>	m_sex;
	CEncrypt<int>	m_beard;
	CEncrypt<int>	m_face;
	CEncrypt<int>	m_hair;
	CEncrypt<int>	m_skin_color;
	CEncrypt<int>	m_hair_color;
	CEncrypt<int>	m_accessories;
	CEncrypt<int>   m_underwear;

	CEncrypt<int>   m_extra_item[4];

	int m_iSlotIndex;
	int m_iLimitSecond;

	short m_sLeaderType;
	short m_sRentalType;
	DWORD m_dwRentalMinute;
	int m_iPeriodType;

	bool m_bActive;
	byte m_chExerciseStyle;

	int m_iAwakeType;
	int m_iAwakeLimitTime;

	byte m_eCharPowerUpType;

	CostumeEquipInfo m_EquipCostume[4];
	AccessoryEquipInfo m_EquipAccessory[3];
};