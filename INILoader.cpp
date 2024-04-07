#include "stdafx.h"
#include "INILoader.h"
#include <strsafe.h>

INILoader::INILoader()
{
	ZeroMemory(m_szFileName, MAX_PATH);
	ZeroMemory(m_szTitle, MAX_PATH);

	// 	m_pParser = NULL;
}

INILoader::INILoader(const char* szFileName)
{
	StringCbCopy(m_szFileName, sizeof(m_szFileName), szFileName);
	ZeroMemory(m_szTitle, MAX_PATH);
}

INILoader::INILoader(const char* szPath, const char* szFileName)
{
	StringCbPrintf(m_szFileName, sizeof(m_szFileName), "%s/%s", szPath, szFileName);
	ZeroMemory(m_szTitle, MAX_PATH);
}

INILoader::~INILoader()
{

}

void INILoader::SetFileName(const char* szFileName)
{
	StringCbCopy(m_szFileName, sizeof(m_szFileName), szFileName);
}

void INILoader::SetTitle(const char* szTitle)
{
	StringCbCopy(m_szTitle, sizeof(m_szTitle), szTitle);
}

bool INILoader::DoMemoryParsing()
{
	return false;
}

bool INILoader::LoadBool(const char* szTitle, const char* szKeyName, bool bDefault)
{
	int iValue = 0;
	if (bDefault)
	{
		iValue = 1;
	}

	iValue = GetPrivateProfileInt(szTitle, szKeyName, iValue, m_szFileName);

	if (iValue != 0)
	{
		return true;
	}

	return false;

}

int INILoader::LoadInt(const char* szTitle, const char* szKeyName, int iDefault)
{
	int iValue = iDefault;
	iValue = GetPrivateProfileInt(szTitle, szKeyName, iDefault, m_szFileName);

	return iValue;
}

float INILoader::LoadFloat(const char* szTitle, const char* szKeyName, float fDefault)
{
	float fValue = fDefault;

	char szBuf[MAX_PATH];
	GetPrivateProfileString(szTitle, szKeyName, "", szBuf, MAX_PATH, m_szFileName);
	if (strcmp(szBuf, ""))
	{
		fValue = (float)atof(szBuf);
	}

	return fValue;
}

void INILoader::LoadString(const char* szTitle, const char* szKeyName, const char* szDefault, char* szBuf, int iBufLen)
{
	GetPrivateProfileString(szTitle, szKeyName, szDefault, szBuf, iBufLen, m_szFileName);
}

bool INILoader::LoadBool(const char* szKeyName, bool bDefault)
{
	return LoadBool(m_szTitle, szKeyName, bDefault);
}

int INILoader::LoadInt(const char* szKeyName, int iDefault)
{
	return LoadInt(m_szTitle, szKeyName, iDefault);
}

float INILoader::LoadFloat(const char* szKeyName, float fDefault)
{
	return LoadFloat(m_szTitle, szKeyName, fDefault);
}

void INILoader::LoadString(const char* szKeyName,
	const char* szDefault,
	char* szBuf,
	int iBufLen)
{
	LoadString(m_szTitle, szKeyName, szDefault, szBuf, iBufLen);
}

void INILoader::SaveString(const char* szTitle, const char* szKeyName, const char* szBuf)
{
	WritePrivateProfileString(szTitle, szKeyName, szBuf, m_szFileName);
}

void INILoader::SaveInt(const char* szTitle, const char* szKeyName, int iValue)
{
	char szBuf[MAX_PATH];
	StringCbPrintf(szBuf, sizeof(szBuf), "%d", iValue);

	WritePrivateProfileString(szTitle, szKeyName, szBuf, m_szFileName);
}

void INILoader::SaveFloat(const char* szTitle, const char* szKeyName, float fValue, bool bNoLimit)
{
	char szBuf[MAX_PATH];

	if (bNoLimit)
	{
		StringCbPrintf(szBuf, sizeof(szBuf), "%f", fValue);
	}
	else
	{
		StringCbPrintf(szBuf, sizeof(szBuf), "%.2f", fValue);
	}

	WritePrivateProfileString(szTitle, szKeyName, szBuf, m_szFileName);
}

void INILoader::SaveBool(const char* szTitle, const char* szKeyName, bool bValue)
{
	if (bValue)
	{
		WritePrivateProfileString(szTitle, szKeyName, "1", m_szFileName);
	}
	else
	{
		WritePrivateProfileString(szTitle, szKeyName, "0", m_szFileName);
	}
}

void INILoader::SaveString(const char* szKeyName, const char* szBuf)
{
	SaveString(m_szTitle, szKeyName, szBuf);
}

void INILoader::SaveInt(const char* szKeyName, int iValue)
{
	SaveInt(m_szTitle, szKeyName, iValue);
}

void INILoader::SaveFloat(const char* szKeyName, float fValue, bool bNoLimit)
{
	SaveFloat(m_szTitle, szKeyName, fValue, bNoLimit);
}

void INILoader::SaveBool(const char* szKeyName, bool bValue)
{
	SaveBool(m_szTitle, szKeyName, bValue);
}