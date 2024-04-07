#pragma once
#include "stdafx.h"

#define MAX_BUFFER		32768 * 2         //8192 * 4
#define MAX_SENDBUFFER	4096

enum PacketDefinition
{
	PK_ID_ADDR = 0,
	PK_SIZE_ADDR = 4,
	PK_CKSUM_ADDR = 8,
	PK_FSM_ADDR = 12,
	PK_HEADER_SIZE = 16,
};

class CPacket
{
protected:   //예약되어있는 패킷데이터 8 byte
	typedef struct tagHeader
	{
		DWORD* m_ID;
		DWORD* m_Size;
		DWORD* m_CheckSum;
		int* m_iState;
		tagHeader()
		{
			m_ID = m_Size = m_CheckSum = NULL;
			m_iState = NULL;
		}
	}PACKETHEADER;
	PACKETHEADER m_packet_header;                //PACKET ID

protected:
	int  m_currentPos;
	char m_pBuffer[MAX_BUFFER];
	bool m_bClear;

public:
	void Clear()
	{
		memset(m_pBuffer, 0, MAX_BUFFER);

		m_currentPos = 0;
		m_packet_header.m_ID = (DWORD*)&m_pBuffer[PK_ID_ADDR];
		m_packet_header.m_Size = (DWORD*)&m_pBuffer[PK_SIZE_ADDR];
		m_packet_header.m_CheckSum = (DWORD*)&m_pBuffer[PK_CKSUM_ADDR];
		m_packet_header.m_iState = (int*)&m_pBuffer[PK_FSM_ADDR];
		*m_packet_header.m_Size = sizeof(PACKETHEADER);
	}

	void SetDataAdd(char* pBuf, int size)
	{
		memcpy(&m_pBuffer[m_currentPos], pBuf, size);
		m_currentPos += size;
		*m_packet_header.m_Size = m_currentPos;
	}

	const char* GetData() const
	{
		return &m_pBuffer[0] + sizeof(PACKETHEADER);
	}

	int GetDataSize() const
	{
		return *m_packet_header.m_Size - sizeof(PACKETHEADER);
	}

public:
	void SetBufferCopy(const char* pBuf, int size)
	{
		Clear();
		memcpy(&m_pBuffer[0], pBuf, min(MAX_BUFFER, size));
		m_currentPos = sizeof(PACKETHEADER);
	}

	void SetBufferCopy(const char* pBuf, int size, int pos)
	{
		Clear();
		memcpy(&m_pBuffer[0], pBuf, min(MAX_BUFFER, size));
		m_currentPos = pos;
	}

	void SetCheckSum(DWORD dwSum)
	{
		*m_packet_header.m_CheckSum = dwSum;
	}

	void SetState(int iState)
	{
		*m_packet_header.m_iState = iState;
	}

public:
	char* GetBuffer() { return &m_pBuffer[0]; }
	int   GetBufferSize() { return *m_packet_header.m_Size; }
	DWORD GetPacketID() const { return *m_packet_header.m_ID; }
	DWORD GetCheckSum() { return *m_packet_header.m_CheckSum; }
	int   GetState() { return *m_packet_header.m_iState; }
	int   GetCurPos() { return m_currentPos; }

public:
	CPacket()
	{
		Clear();
	}

	CPacket(DWORD ID)
	{
		Clear();
		*m_packet_header.m_ID = ID;
		m_currentPos = sizeof(PACKETHEADER);
	}

	CPacket(char* buffer, int size)
	{
		Clear();
		memcpy(&m_pBuffer[0], buffer, min(MAX_BUFFER, size));
		m_currentPos = sizeof(PACKETHEADER);
	}

	~CPacket()
	{

	}

public:
	bool Write(const char* arg)
	{
		int nlen = lstrlen(arg) + 1;

		memcpy(&m_pBuffer[m_currentPos], arg, nlen);
		m_currentPos += nlen;
		*m_packet_header.m_Size = m_currentPos;
		return true;
	}

	bool Write(bool arg)
	{
		memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(bool));
		m_currentPos += sizeof(bool);
		*m_packet_header.m_Size = m_currentPos;
		return true;
	}

	bool Write(int arg)
	{
		memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(int));
		m_currentPos += sizeof(int);
		*m_packet_header.m_Size = m_currentPos;
		return true;
	}

	bool Write(LONG arg)
	{
		memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(LONG));
		m_currentPos += sizeof(LONG);
		*m_packet_header.m_Size = m_currentPos;
		return true;
	}

	bool Write(DWORD arg)
	{
		memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(DWORD));
		m_currentPos += sizeof(DWORD);
		*m_packet_header.m_Size = m_currentPos;
		return true;
	}

	bool Write(__int64 arg)
	{
		memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(__int64));
		m_currentPos += sizeof(__int64);
		*m_packet_header.m_Size = m_currentPos;
		return true;
	}

	bool Write(LPTSTR arg)
	{
		int nLen = lstrlen(arg) * sizeof(TCHAR) + sizeof(TCHAR);

		memcpy(&m_pBuffer[m_currentPos], arg, nLen);
		m_currentPos += nLen;
		*m_packet_header.m_Size = m_currentPos;
		return true;
	}

	bool Write(double arg)
	{
		memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(double));
		m_currentPos += sizeof(double);
		*m_packet_header.m_Size = m_currentPos;
		return true;
	}

	bool Write(float arg)
	{
		memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(float));
		m_currentPos += sizeof(float);
		*m_packet_header.m_Size = m_currentPos;
		return true;
	}


	bool Read(bool& arg)
	{
		memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(bool));
		m_currentPos += sizeof(bool);
		return true;
	}
	bool Read(int& arg)
	{
		memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(int));
		m_currentPos += sizeof(int);
		return true;
	}

	bool Read(LONG& arg)
	{
		memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(LONG));
		m_currentPos += sizeof(LONG);
		return true;
	}
	bool Read(DWORD& arg)
	{
		memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(DWORD));
		m_currentPos += sizeof(DWORD);
		return true;
	}

	bool Read(__int64& arg)
	{
		memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(__int64));
		m_currentPos += sizeof(__int64);
		return true;
	}

	bool Read(const int nLength, LPTSTR arg)
	{
		int nLen = lstrlen((LPTSTR)&m_pBuffer[m_currentPos]) * sizeof(TCHAR) + sizeof(TCHAR);
		if (nLen < nLength)
		{
			memcpy(arg, &m_pBuffer[m_currentPos], nLen);
			arg[nLen] = NULL;
			m_currentPos += nLen;
			return true;
		}
		return false;
	}
	bool Read(double& arg)
	{
		memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(double));
		m_currentPos += sizeof(double);
		return true;
	}

	bool Read(float& arg)
	{
		memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(float));
		m_currentPos += sizeof(float);
		return true;
	}
};
