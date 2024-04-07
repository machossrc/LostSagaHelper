#pragma once
#include "ioHashString.h"

class ioMyInfo
{
public:
	//DWORD m_user_idx;
	//ioHashString m_private_id;
	//ioHashString m_public_id;
	//int m_cash;
	//__int64	m_money;
	//int m_connect_count;
	//DWORD m_connect_date;
	//int m_user_state;
	//int m_grade_level;
	//int m_grade_exp;
	//int m_fishing_level;
	//int m_fishing_exp;
	//int m_user_event_type;
	//int m_user_rank;
	//int m_eEntryType;
	//int m_camp_position;
	//int m_ladder_point;
	//int m_camp_rank;
	//int m_eChannelingType;
	//ioHashString m_szChannelingUserNo;
	//ioHashString m_szChannelingUserID;
	//int m_iChannelingCash;
	//int m_eBlockType;
	//DWORD m_dwBlockYearMonthDay;
	//DWORD m_dwBlockHourMinute;
	//int m_refill_data;
	//int m_purchased_cash;
	//int m_iExcavationLevel;
	//int m_iExcavationExp;
	//int m_iAccrueHeroExpert;
	//int m_iHeroExpert;
	//int m_iBonusCash;
public:
	int GetCharCount();

	int GetClassArray(int iClassType);

private:
	static ioMyInfo* sg_Instance;
public:
	static ioMyInfo& GetInstance();
public:
	void InitMyInfo();
	ioMyInfo();
	~ioMyInfo();
};

#define g_MyInfo ioMyInfo::GetInstance()