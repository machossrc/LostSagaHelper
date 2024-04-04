#pragma once

typedef struct tagAccessoryEquipInfo
{
	CEncrypt<int> m_iAccessoryIdx;
	CEncrypt<int> m_iAccessoryCode;
	CEncrypt<int> m_iRandomNumber;
	CEncrypt<int> m_iCompoundCode;
	CEncrypt<int> m_iCompoundValue;

	void Init()
	{
		m_iAccessoryIdx = 0;
		m_iAccessoryCode = 0;
		m_iRandomNumber = 0;
		m_iCompoundCode = 0;
		m_iCompoundValue = 0;
	}

	tagAccessoryEquipInfo()
	{
		Init();
	}

	tagAccessoryEquipInfo(const tagAccessoryEquipInfo& rhs)
	{
		m_iAccessoryIdx = rhs.m_iAccessoryIdx;
		m_iAccessoryCode = rhs.m_iAccessoryCode;
		m_iRandomNumber = rhs.m_iRandomNumber;
		m_iCompoundCode = rhs.m_iCompoundCode;
		m_iCompoundValue = rhs.m_iCompoundValue;
	}

	bool operator=(const tagAccessoryEquipInfo& rhs)
	{
		m_iAccessoryIdx = rhs.m_iAccessoryIdx;
		m_iAccessoryCode = rhs.m_iAccessoryCode;
		m_iRandomNumber = rhs.m_iRandomNumber;
		m_iCompoundCode = rhs.m_iCompoundCode;
		m_iCompoundValue = rhs.m_iCompoundValue;

		return true;
	}

	bool operator==(const tagAccessoryEquipInfo& rhs) const
	{
		if (m_iAccessoryIdx != rhs.m_iAccessoryIdx)
			return false;
		if (m_iAccessoryCode != rhs.m_iAccessoryCode)
			return false;
		if (m_iRandomNumber != rhs.m_iRandomNumber)
			return false;
		if (m_iCompoundCode != rhs.m_iCompoundCode)
			return false;
		if (m_iCompoundValue != rhs.m_iCompoundValue)
			return false;

		return true;
	}

	bool operator!=(const tagAccessoryEquipInfo& rhs) const
	{
		if (*this == rhs)
			return false;

		return true;
	}

}AccessoryEquipInfo;

typedef struct tagCostumeEquipInfo
{
	int m_CostumeIdx;
	int m_CostumeCode;
	DWORD m_Costume_Male_Custom;
	DWORD m_Costume_Female_Custom;

	void Init()
	{
		m_CostumeIdx = 0;
		m_CostumeCode = 0;
		m_Costume_Male_Custom = 0;
		m_Costume_Female_Custom = 0;
	}

	tagCostumeEquipInfo()
	{
		Init();
	}

	tagCostumeEquipInfo(const tagCostumeEquipInfo& rhs)
	{
		m_CostumeIdx = rhs.m_CostumeIdx;
		m_CostumeCode = rhs.m_CostumeCode;
		m_Costume_Male_Custom = rhs.m_Costume_Male_Custom;
		m_Costume_Female_Custom = rhs.m_Costume_Female_Custom;
	}

	bool operator==(const tagCostumeEquipInfo& rhs) const
	{
		if (m_CostumeIdx != rhs.m_CostumeIdx)
			return false;
		if (m_CostumeCode != rhs.m_CostumeCode)
			return false;
		if (m_Costume_Male_Custom != rhs.m_Costume_Male_Custom)
			return false;
		if (m_Costume_Female_Custom != rhs.m_Costume_Female_Custom)
			return false;

		return true;
	}

	bool operator!=(const tagCostumeEquipInfo& rhs) const
	{
		if (*this == rhs)
			return false;

		return true;
	}

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