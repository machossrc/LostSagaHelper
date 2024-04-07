

#ifndef _INILoader_h_
#define _INILoader_h_

class INILoader
{
private:
	char m_szFileName[260];
	char m_szTitle[260];

public:
	void SetFileName(const char* szFileName);
	void SetTitle(const char* szTitle);

	bool DoMemoryParsing();

public:
	const char* GetFileName() const { return m_szFileName; }
	const char* GetTitle() const { return m_szTitle; }

public:
	bool LoadBool(const char* szTitle, const char* szKeyName, bool bDefault);
	int  LoadInt(const char* szTitle, const char* szKeyName, int iDefault);
	float LoadFloat(const char* szTitle, const char* szKeyName, float fDefault);
	void LoadString(const char* szTitle,
		const char* szKeyName,
		const char* szDefault,
		char* szBuf,
		int iBufLen);

public:
	bool LoadBool(const char* szKeyName, bool bDefault);
	int  LoadInt(const char* szKeyName, int iDefault);
	float LoadFloat(const char* szKeyName, float fDefault);
	void LoadString(const char* szKeyName,
		const char* szDefault,
		char* szBuf,
		int iBufLen);

public:
	void SaveString(const char* szTitle, const char* szKeyName, const char* szBuf);
	void SaveInt(const char* szTitle, const char* szKeyName, int iValue);
	void SaveFloat(const char* szTitle, const char* szKeyName, float fValue, bool bNoLimit = false);
	void SaveBool(const char* szTitle, const char* szKeyName, bool bValue);

public:
	void SaveString(const char* szKeyName, const char* szBuf);
	void SaveInt(const char* szKeyName, int iValue);
	void SaveFloat(const char* szKeyName, float fValue, bool bNoLimit = false);
	void SaveBool(const char* szKeyName, bool bValue);

public:
	INILoader();
	INILoader(const char* szFileName);
	INILoader(const char* szPath, const char* szFileName);
	~INILoader();
};

#endif