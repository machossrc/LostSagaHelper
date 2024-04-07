#include "StdAfx.h"
#include "SP2Packet.h"

SP2Packet::SP2Packet()
{

}

SP2Packet::SP2Packet(SP2Packet& rhs)
{
	Clear();
	memcpy(m_pBuffer, rhs.GetBuffer(), rhs.GetBufferSize());
	m_currentPos = rhs.m_currentPos;
}

SP2Packet::SP2Packet(DWORD ID) : CPacket(ID)
{
}

SP2Packet::SP2Packet(char* szIP, DWORD dwPort, DWORD dwUserIndex, int iIndex, const SP2Packet& rhs)
{
	Clear();

	*m_packet_header.m_ID = rhs.GetPacketID();
	m_currentPos = sizeof(PACKETHEADER);

	*this << StrToDwordIP(szIP) << dwPort << dwUserIndex << iIndex;

	SetDataAdd((char*)rhs.GetData(), rhs.GetDataSize());
}

SP2Packet::SP2Packet(char* buffer, int size) : CPacket(buffer, size)
{
}

SP2Packet::~SP2Packet()
{

}

void SP2Packet::MovePointer(DWORD dwMoveBytes)
{
	m_currentPos += dwMoveBytes;
	m_currentPos = min(m_currentPos, GetBufferSize());
}

DWORD SP2Packet::StrToDwordIP(char* iip)
{
	int  count = 0;
	int  cut_ip = 0;
	char szCut_ip[4][4];
	memset(szCut_ip, 0, sizeof(szCut_ip));
	int  len = strlen(iip);
	for (int i = 0; i < len; i++)
	{
		if (iip[i] == '.')
		{
			count = 0;
			cut_ip++;
		}
		else
			szCut_ip[cut_ip][count++] = iip[i];
	}
	return (DWORD)(atoi(szCut_ip[0]) << 24) | (DWORD)(atoi(szCut_ip[1]) << 16) | (DWORD)(atoi(szCut_ip[2]) << 8) | atoi(szCut_ip[3]);
}

void SP2Packet::DwordToStrIP(DWORD dwIP, char* iip)
{
	sprintf(iip, "%d.%d.%d.%d", (dwIP & 0xff000000) >> 24, (dwIP & 0x00ff0000) >> 16, (dwIP & 0x0000ff00) >> 8, (dwIP & 0xff));
}

void SP2Packet::InitCurPos()
{
	m_currentPos = sizeof(PACKETHEADER);
}

//operator
SP2Packet& SP2Packet::operator = (SP2Packet& packet)
{
	Clear();
	memcpy(m_pBuffer, packet.GetBuffer(), packet.GetBufferSize());
	m_currentPos = packet.m_currentPos;

	return *this;
}

SP2Packet& SP2Packet::operator << (BYTE arg)
{
	memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(BYTE));
	m_currentPos += sizeof(BYTE);
	*m_packet_header.m_Size = m_currentPos;
	return *this;
}

SP2Packet& SP2Packet::operator << (bool arg)
{
	memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(bool));
	m_currentPos += sizeof(bool);
	*m_packet_header.m_Size = m_currentPos;
	return *this;
}

SP2Packet& SP2Packet::operator << (int arg)
{
	memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(int));
	m_currentPos += sizeof(int);
	*m_packet_header.m_Size = m_currentPos;
	return *this;
}

SP2Packet& SP2Packet::operator << (LONG arg)
{
	memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(LONG));
	m_currentPos += sizeof(LONG);
	*m_packet_header.m_Size = m_currentPos;
	return *this;
}

SP2Packet& SP2Packet::operator << (WORD arg)
{
	memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(WORD));
	m_currentPos += sizeof(WORD);
	*m_packet_header.m_Size = m_currentPos;
	return *this;
}

SP2Packet& SP2Packet::operator << (DWORD arg)
{
	memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(DWORD));
	m_currentPos += sizeof(DWORD);
	*m_packet_header.m_Size = m_currentPos;
	return *this;
}

SP2Packet& SP2Packet::operator << (__int64 arg)
{
	memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(__int64));
	m_currentPos += sizeof(__int64);
	*m_packet_header.m_Size = m_currentPos;
	return *this;
}

SP2Packet& SP2Packet::operator << (LPTSTR arg)
{
	int nlen = lstrlen(arg) * sizeof(TCHAR) + sizeof(TCHAR);

	memcpy(&m_pBuffer[m_currentPos], arg, nlen);
	m_currentPos += nlen;
	*m_packet_header.m_Size = m_currentPos;
	return *this;
}

SP2Packet& SP2Packet::operator << (double arg)
{
	memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(double));
	m_currentPos += sizeof(double);
	*m_packet_header.m_Size = m_currentPos;
	return *this;
}

SP2Packet& SP2Packet::operator << (float arg)
{
	memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(float));
	m_currentPos += sizeof(float);
	*m_packet_header.m_Size = m_currentPos;
	return *this;
}

SP2Packet& SP2Packet::operator << (short arg)
{
	memcpy(&m_pBuffer[m_currentPos], &arg, sizeof(short));
	m_currentPos += sizeof(short);
	*m_packet_header.m_Size = m_currentPos;
	return *this;
}

SP2Packet& SP2Packet::operator << (const char* arg)
{
	int nlen = lstrlen(arg) + 1;

	memcpy(&m_pBuffer[m_currentPos], arg, nlen);
	m_currentPos += nlen;
	*m_packet_header.m_Size = m_currentPos;

	return *this;
}

SP2Packet& SP2Packet::operator >> (BYTE& arg)
{
	memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(BYTE));
	m_currentPos += sizeof(BYTE);

	return *this;
}

SP2Packet& SP2Packet::operator >> (bool& arg)
{
	memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(bool));
	m_currentPos += sizeof(bool);

	return *this;
}

SP2Packet& SP2Packet::operator >> (int& arg)
{
	memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(int));
	m_currentPos += sizeof(int);

	return *this;
}

SP2Packet& SP2Packet::operator >> (LONG& arg)
{
	memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(LONG));
	m_currentPos += sizeof(LONG);

	return *this;
}

SP2Packet& SP2Packet::operator >> (WORD& arg)
{
	memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(WORD));
	m_currentPos += sizeof(WORD);

	return *this;
}

SP2Packet& SP2Packet::operator >> (DWORD& arg)
{
	memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(DWORD));
	m_currentPos += sizeof(DWORD);

	return *this;
}

SP2Packet& SP2Packet::operator >> (__int64& arg)
{
	memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(__int64));
	m_currentPos += sizeof(__int64);

	return *this;
}

SP2Packet& SP2Packet::operator >> (LPTSTR arg)
{
	int nlen = lstrlen((LPTSTR)&m_pBuffer[m_currentPos]) * sizeof(TCHAR) + sizeof(TCHAR);

	memcpy(arg, &m_pBuffer[m_currentPos], nlen);
	m_currentPos += nlen;

	return *this;
}

SP2Packet& SP2Packet::operator >> (double& arg)
{
	memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(double));
	m_currentPos += sizeof(double);

	return *this;
}

SP2Packet& SP2Packet::operator >> (float& arg)
{
	memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(float));
	m_currentPos += sizeof(float);

	return *this;
}

SP2Packet& SP2Packet::operator >> (short& arg)
{
	memcpy(&arg, &m_pBuffer[m_currentPos], sizeof(short));
	m_currentPos += sizeof(short);

	return *this;
}