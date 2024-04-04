#pragma once

#include <MMSystem.h>
#include "ccddaabb.h"

#pragma warning( disable : 4800 4172 4018 )

template <class type>
class CEncrypt
{
public:
	enum { MAX_MEM_POOL = 12, MAX_ENCRYPT = 8, DEFAULT_ENCRYPT = 4 };

#ifdef _NOTUSE
public:
	type            m_value;
#endif

	unsigned short  m_MemPoolPos;
	unsigned short  m_ValueSize;
	char            m_EncryptSeed;
	ccddaabb        m_RC5;
	char            m_MemPool[MAX_MEM_POOL];
	char            m_TempMem[MAX_ENCRYPT];

	void  DecryptValueToPool2(char* value) // 더미
	{
		for (int i = 0; i < m_ValueSize; i++)
		{
			value[i] = m_MemPool[m_MemPoolPos + i] ^ 0xF1 ^ m_EncryptSeed;
		}
	}

	void   EncryptValueToPool2(const char* value) // 더미
	{
		for (int i = 0; i < m_ValueSize; i++)
		{
			m_MemPool[m_MemPoolPos + i] = value[i] ^ 0xF1 ^ m_EncryptSeed;
		}
	}

	void EncryptValueToPool(const char* value)
	{
		m_RC5.EncryptByte(value, m_MemPool, max(m_ValueSize, DEFAULT_ENCRYPT));

	}

	void Init()
	{
		DWORD pid = GetCurrentProcessId();
		DWORD tick = GetTickCount();
		m_ValueSize = sizeof(type);
		m_MemPoolPos = (unsigned short)(rand() + pid + tick) % (MAX_MEM_POOL - m_ValueSize);
		m_EncryptSeed = (char)(rand() + pid + tick) % 256;

		for (int i = 0; i < MAX_MEM_POOL; i++)
			m_MemPool[i] = (char)(rand() + pid + tick) % 256; // 더미

		m_RC5.Setup(NULL, pid, tick);

#ifdef _NOTUSE
		m_value = 0;
		EncryptValueToPool((char*)&m_value);
		Debug();
#endif
	}

#ifdef _NOTUSE
	void Debug()
	{
		type value;
		DecryptValueToPool(&value);
		if (m_value != value)
		{
			int k = 0; // 브레이크 포인트를 걸기 위해서 
		}
	}
#endif

public:
	CEncrypt()
	{
		Init();
	}

	CEncrypt(const type& inValue)        // 선언과 동시에 값을 대입하기 위해서
	{
		Init();
		*this = inValue;
	}

	CEncrypt(const CEncrypt<type>& inValue)   // 선언과 동시에 값을 대입하기 위해서
	{
		Init();
		*this = inValue;
	}

	virtual ~CEncrypt()
	{
	}

public:
	///// 공통 
	////////////////////////////////////////////////////////////////////////////////
	operator type()
	{
		type value;
		DecryptValueToPool(&value);

#ifdef _NOTUSE
		Debug();
#endif
		return value;
	}

	operator type() const
	{
		type value;
		CEncrypt<type>* pThis = const_cast<CEncrypt<type>*>(this);
		pThis->DecryptValueToPool(&value);

#ifdef _NOTUSE
		Debug();
#endif
		return value;
	}

	type operator++()
	{
		type value;
		DecryptValueToPool(&value);
		++value;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		++m_value;
		Debug();
#endif
		return value;
	}

	type operator--()
	{
		type value;
		DecryptValueToPool(&value);
		--value;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		--m_value;
		Debug();
#endif
		return value;
	}

	type operator++(int)
	{
		type value;
		DecryptValueToPool(&value);
		++value;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		++m_value;
		Debug();
#endif
		return value;
	}

	type operator--(int)
	{
		type value;
		DecryptValueToPool(&value);
		--value;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		--m_value;
		Debug();
#endif
		return value;
	}

	// bool
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	void  DecryptValueToPool(bool* value)
	{
		m_RC5.DecryptByte(m_MemPool, m_TempMem, 4);
		*value = *((bool*)m_TempMem);
	}

	bool operator=(bool inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	bool operator==(const bool& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value == inValue);
	}

	bool operator!=(const bool& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value != inValue);
	}

	// char
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	type operator=(char inValue)
	{

		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	type operator-(const char& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value - inValue;
	}

	type operator+(const char& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value + inValue;
	}

	type operator*(const char& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value * inValue;
	}

	type operator/(const char& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value / inValue;
	}

	type operator%(const char& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value % inValue;
	}

	///////////////////////////////////////////////
	type& operator+= (const char& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value += inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value += inValue;
		Debug();
#endif
		return value;
	}

	type& operator-= (const char& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value -= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value -= inValue;
		Debug();
#endif
		return value;
	}

	type& operator*= (const char& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value *= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value *= inValue;
		Debug();
#endif
		return value;
	}

	type& operator/= (const char& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value /= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value /= inValue;
		Debug();
#endif
		return value;
	}

	type& operator%= (const char& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value %= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value %= inValue;
		Debug();
#endif
		return value;
	}
	/////////////////////////////////////////////
	bool operator==(const char& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value == inValue);
	}

	bool operator< (const char& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value < inValue);
	}
	bool operator!=(const char& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value != inValue);
	}
	bool operator> (const char& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value > inValue);
	}
	bool operator<=(const char& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value <= inValue);
	}
	bool operator>=(const char& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value >= inValue);
	}


	// BYTE
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	void  DecryptValueToPool(BYTE* value)
	{
		m_RC5.DecryptByte(m_MemPool, m_TempMem, 4);
		*value = *((BYTE*)m_TempMem);
	}

	type operator=(BYTE inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	type operator-(const BYTE& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value - inValue;
	}

	type operator+(const BYTE& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value + inValue;
	}

	type operator*(const BYTE& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value * inValue;
	}

	type operator/(const BYTE& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value / inValue;
	}

	type operator%(const BYTE& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value % inValue;
	}
	///////////////////////////////////////////////
	type& operator+= (const BYTE& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value += inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value += inValue;
		Debug();
#endif
		return value;
	}

	type& operator-= (const BYTE& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value -= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value -= inValue;
		Debug();
#endif
		return value;
	}

	type& operator*= (const BYTE& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value *= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value *= inValue;
		Debug();
#endif
		return value;
	}

	type& operator/= (const BYTE& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value /= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value /= inValue;
		Debug();
#endif
		return value;
	}

	type& operator%= (const BYTE& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value %= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value %= inValue;
		Debug();
#endif
		return value;
	}

	/////////////////////////////////////////////
	bool operator==(const BYTE& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value == inValue);
	}

	bool operator< (const BYTE& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value < inValue);
	}

	bool operator!=(const BYTE& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value != inValue);
	}

	bool operator> (const BYTE& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value > inValue);
	}

	bool operator<=(const BYTE& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value <= inValue);
	}

	bool operator>=(const BYTE& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value >= inValue);
	}

	// WORD
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	void  DecryptValueToPool(WORD* value)
	{
		m_RC5.DecryptByte(m_MemPool, m_TempMem, 4);
		*value = *((WORD*)m_TempMem);
	}

	type operator=(WORD inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	type operator-(const WORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value - inValue;
	}

	type operator+(const WORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value + inValue;
	}

	type operator*(const WORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value * inValue;
	}

	type operator/(const WORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value / inValue;
	}

	type operator%(const WORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value % inValue;
	}
	///////////////////////////////////////////////
	type& operator+= (const WORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value += inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value += inValue;
		Debug();
#endif
		return value;
	}

	type& operator-= (const WORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value -= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value -= inValue;
		Debug();
#endif
		return value;
	}

	type& operator*= (const WORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value *= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value *= inValue;
		Debug();
#endif
		return value;
	}

	type& operator/= (const WORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value /= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value /= inValue;
		Debug();
#endif
		return value;
	}

	type& operator%= (const WORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value %= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value %= inValue;
		Debug();
#endif
		return value;
	}
	/////////////////////////////////////////////
	bool operator==(const WORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value == inValue);
	}

	bool operator< (const WORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value < inValue);
	}

	bool operator!=(const WORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value != inValue);
	}

	bool operator> (const WORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value > inValue);
	}

	bool operator<=(const WORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value <= inValue);
	}

	bool operator>=(const WORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value >= inValue);
	}

	// int
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	void  DecryptValueToPool(int* value)
	{
		m_RC5.DecryptByte(m_MemPool, m_TempMem, 4);
		*value = *((int*)m_TempMem);
	}

	type operator=(int inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	type operator-(const int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value - inValue;
	}

	type operator+(const int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value + inValue;
	}

	type operator*(const int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value * inValue;
	}

	type operator/(const int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value / inValue;
	}

	type operator%(const int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value % inValue;
	}

	///////////////////////////////////////////////
	type& operator+= (const int& inValue)
	{

		type value;
		DecryptValueToPool(&value);
		value += inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value += inValue;
		Debug();
#endif
		return value;
	}

	type& operator-= (const int& inValue)
	{

		type value;
		DecryptValueToPool(&value);
		value -= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value -= inValue;
		Debug();
#endif
		return value;
	}

	type& operator*= (const int& inValue)
	{

		type value;
		DecryptValueToPool(&value);
		value *= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value *= inValue;
		Debug();
#endif
		return value;
	}

	type& operator/= (const int& inValue)
	{

		type value;
		DecryptValueToPool(&value);
		value /= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value /= inValue;
		Debug();
#endif
		return value;
	}

	type& operator%= (const int& inValue)
	{

		type value;
		DecryptValueToPool(&value);
		value %= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value %= inValue;
		Debug();
#endif
		return value;
	}

	/////////////////////////////////////////////
	bool operator==(const int& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value == inValue);
	}

	bool operator< (const int& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value < inValue);
	}

	bool operator!=(const int& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value != inValue);
	}

	bool operator> (const int& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value > inValue);
	}

	bool operator<=(const int& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value <= inValue);
	}

	bool operator>=(const int& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value >= inValue);
	}

	// long
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	void  DecryptValueToPool(long* value)
	{
		m_RC5.DecryptByte(m_MemPool, m_TempMem, 4);
		*value = *((long*)m_TempMem);
	}

	type operator=(long inValue)
	{

		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	type operator-(const long& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value - inValue;
	}

	type operator+(const long& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value + inValue;
	}

	type operator*(const long& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value * inValue;
	}

	type operator/(const long& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value / inValue;
	}

	type operator%(const long& inValue)
	{

		type value;
		DecryptValueToPool(&value);
		return value % inValue;
	}

	///////////////////////////////////////////////
	type& operator+= (const long& inValue)
	{

		type value;
		DecryptValueToPool(&value);
		value += inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value += inValue;
		Debug();
#endif
		return value;
	}

	type& operator-= (const long& inValue)
	{

		type value;
		DecryptValueToPool(&value);
		value -= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value -= inValue;
		Debug();
#endif
		return value;
	}

	type& operator*= (const long& inValue)
	{

		type value;
		DecryptValueToPool(&value);
		value *= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value *= inValue;
		Debug();
#endif
		return value;
	}

	type& operator/= (const long& inValue)
	{

		type value;
		DecryptValueToPool(&value);
		value /= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value /= inValue;
		Debug();
#endif
		return value;
	}

	type& operator%= (const long& inValue)
	{

		type value;
		DecryptValueToPool(&value);
		value %= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value %= inValue;
		Debug();
#endif
		return value;
	}

	/////////////////////////////////////////////
	bool operator==(const long& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value == inValue);
	}

	bool operator< (const long& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value < inValue);
	}

	bool operator!=(const long& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value != inValue);
	}

	bool operator> (const long& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value > inValue);
	}

	bool operator<=(const long& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value <= inValue);
	}

	bool operator>=(const long& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value >= inValue);
	}

	// DWORD
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	void  DecryptValueToPool(DWORD* value)
	{
		m_RC5.DecryptByte(m_MemPool, m_TempMem, 4);
		*value = *((DWORD*)m_TempMem);
	}

	type operator=(DWORD inValue)
	{

		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	type operator-(const DWORD& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value - inValue;
	}

	type operator+(const DWORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value + inValue;
	}

	type operator*(const DWORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value * inValue;
	}

	type operator/(const DWORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value / inValue;
	}

	type operator%(const DWORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value % inValue;
	}
	///////////////////////////////////////////////
	type& operator+= (const DWORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value += inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value += inValue;
		Debug();
#endif
		return value;
	}

	type& operator-= (const DWORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value -= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value -= inValue;
		Debug();
#endif
		return value;
	}

	type& operator*= (const DWORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value *= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value *= inValue;
		Debug();
#endif
		return value;
	}

	type& operator/= (const DWORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value /= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value /= inValue;
		Debug();
#endif
		return value;
	}

	type& operator%= (const DWORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value %= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value %= inValue;
		Debug();
#endif
		return value;
	}

	/////////////////////////////////////////////
	bool operator==(const DWORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value == inValue);
	}

	bool operator< (const DWORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value < inValue);
	}

	bool operator!=(const DWORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value != inValue);
	}

	bool operator> (const DWORD& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value > inValue);
	}

	bool operator<=(const DWORD& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value <= inValue);
	}

	bool operator>=(const DWORD& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value >= inValue);
	}

	// unsigned int
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	type operator=(unsigned int inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	type operator-(const unsigned int& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value - inValue;
	}

	type operator+(const unsigned int& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value + inValue;
	}

	type operator*(const unsigned int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value * inValue;
	}

	type operator/(const unsigned int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value / inValue;
	}

	type operator%(const unsigned int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value % inValue;
	}

	///////////////////////////////////////////////
	type& operator+= (const unsigned int& inValue)
	{

		type value;
		DecryptValueToPool(&value);
		value += inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value += inValue;
		Debug();
#endif
		return value;
	}

	type& operator-= (const unsigned int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value -= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value -= inValue;
		Debug();
#endif
		return value;
	}

	type& operator*= (const unsigned int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value *= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value *= inValue;
		Debug();
#endif
		return value;
	}

	type& operator/= (const unsigned int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value /= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value /= inValue;
		Debug();
#endif
		return value;
	}

	type& operator%= (const unsigned int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value %= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value %= inValue;
		Debug();
#endif
		return value;
	}
	/////////////////////////////////////////////
	bool operator==(const unsigned int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value == inValue);
	}

	bool operator< (const unsigned int& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value < inValue);
	}

	bool operator!=(const unsigned int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value != inValue);
	}

	bool operator> (const unsigned int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value > inValue);
	}
	bool operator<=(const unsigned int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value <= inValue);
	}
	bool operator>=(const unsigned int& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value >= inValue);
	}

	// float
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	void  DecryptValueToPool(float* value)
	{
		m_RC5.DecryptByte(m_MemPool, m_TempMem, 4);
		*value = *((float*)m_TempMem);
	}

	type operator=(float inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	type operator-(const float& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value - inValue;
	}

	type operator+(const float& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value + inValue;
	}

	type operator*(const float& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value * inValue;
	}

	type operator/(const float& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value / inValue;
	}

	type operator%(const float& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value % inValue;
	}
	///////////////////////////////////////////////
	type& operator+= (const float& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value += inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value += inValue;
		Debug();
#endif
		return value;
	}

	type& operator-= (const float& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value -= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value -= inValue;
		Debug();
#endif
		return value;
	}

	type& operator*= (const float& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value *= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value *= inValue;
		Debug();
#endif
		return value;
	}

	type& operator/= (const float& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value /= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value /= inValue;
		Debug();
#endif
		return value;
	}

	type& operator%= (const float& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value %= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value %= inValue;
		Debug();
#endif
		return value;
	}

	/////////////////////////////////////////////
	bool operator==(const float& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value == inValue);
	}

	bool operator< (const float& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value < inValue);
	}

	bool operator!=(const float& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value != inValue);
	}

	bool operator> (const float& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value > inValue);
	}

	bool operator<=(const float& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value <= inValue);
	}

	bool operator>=(const float& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value >= inValue);
	}

	// double
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	void  DecryptValueToPool(double* value)
	{
		m_RC5.DecryptByte(m_MemPool, m_TempMem, 8);
		*value = *((double*)m_TempMem);
	}

	type operator=(double inValue)
	{
		type value = (type)inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	type operator-(const double& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value - inValue;
	}

	type operator+(const double& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value + inValue;
	}

	type operator*(const double& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value * inValue;
	}

	type operator/(const double& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value / inValue;
	}

	type operator%(const double& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value % inValue;
	}
	///////////////////////////////////////////////
	type& operator+= (const double& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value += inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value += inValue;
		Debug();
#endif
		return value;
	}

	type& operator-= (const double& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value -= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value -= inValue;
		Debug();
#endif
		return value;
	}

	type& operator*= (const double& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value *= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value *= inValue;
		Debug();
#endif
		return value;
	}

	type& operator/= (const double& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value /= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value /= inValue;
		Debug();
#endif
		return value;
	}

	type& operator%= (const double& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value %= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value %= inValue;
		Debug();
#endif
		return value;
	}
	/////////////////////////////////////////////
	bool operator==(const double& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value == inValue);
	}

	bool operator< (const double& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value < inValue);
	}
	bool operator!=(const double& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value != inValue);
	}
	bool operator> (const double& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value > inValue);
	}
	bool operator<=(const double& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value <= inValue);
	}
	bool operator>=(const double& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value >= inValue);
	}

	// __int64
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	void  DecryptValueToPool(__int64* value)
	{
		m_RC5.DecryptByte(m_MemPool, m_TempMem, 8);
		*value = *((__int64*)m_TempMem);
	}

	type operator=(__int64 inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	type operator-(const __int64& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value - inValue;
	}

	type operator+(const __int64& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value + inValue;
	}

	type operator*(const __int64& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value * inValue;
	}

	type operator/(const __int64& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value / inValue;
	}

	type operator%(const __int64& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return value % inValue;
	}

	///////////////////////////////////////////////
	type& operator+= (const __int64& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value += inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value += inValue;
		Debug();
#endif
		return value;
	}

	type& operator-= (const __int64& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value -= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value -= inValue;
		Debug();
#endif
		return value;
	}

	type& operator*= (const __int64& inValue)
	{

		type value;
		DecryptValueToPool(&value);
		value *= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value *= inValue;
		Debug();
#endif
		return value;
	}

	type& operator/= (const __int64& inValue)
	{
		type value;
		DecryptValueToPool(&value);
		value /= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value /= inValue;
		Debug();
#endif
		return value;
	}

	type& operator%= (const __int64& inValue)
	{

		type value;
		DecryptValueToPool(&value);
		value %= inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value %= inValue;
		Debug();
#endif
		return value;
	}

	/////////////////////////////////////////////
	bool operator==(const __int64& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value == inValue);
	}

	bool operator< (const __int64& inValue)
	{

		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value < inValue);
	}
	bool operator!=(const __int64& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value != inValue);
	}

	bool operator> (const __int64& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value > inValue);
	}

	bool operator<=(const __int64& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value <= inValue);
	}

	bool operator>=(const __int64& inValue)
	{
		type value;
		DecryptValueToPool(&value);
#ifdef _NOTUSE
		Debug();
#endif
		return (value >= inValue);
	}

	// 명시적으로 선언해 주어야 함. 아니면 전체 맴버 변수가 복사됨. //////////////////////////////////

	// CEncrypt<bool>
	//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	bool operator=(CEncrypt<bool>& inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	// CEncrypt<BYTE>
	//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	bool operator=(CEncrypt<BYTE>& inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	// CEncrypt<char>
	//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	bool operator=(CEncrypt<char>& inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	// CEncrypt<WORD>
	//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	bool operator=(CEncrypt<WORD>& inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	// CEncrypt<long>
	//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	bool operator=(CEncrypt<long>& inValue)
	{

		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	// CEncrypt<int>
	//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	bool operator=(CEncrypt<int>& inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	// CEncrypt<unsigend int>
	//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	bool operator=(CEncrypt<unsigned int>& inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	// CEncrypt<DWORD>
	//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	bool operator=(CEncrypt<DWORD>& inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	// CEncrypt<float>
	//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	bool operator=(CEncrypt<float>& inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	// CEncrypt<double>
	//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	bool operator=(CEncrypt<double>& inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}

	// CEncrypt<__int64>
	//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	bool operator=(CEncrypt<__int64>& inValue)
	{
		type value = inValue;
		EncryptValueToPool((char*)&value);
#ifdef _NOTUSE
		m_value = inValue;
		Debug();
#endif
		return value;
	}
};

#pragma warning( default : 4800 4172 4018 )

