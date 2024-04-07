#pragma once

class CMemory
{
public:
	int ChartoAob(const char szArrays[], BYTE b[], BOOL m[]);
	DWORD AobScan(const char szArrays[], DWORD dwStart, DWORD dwEnd, int iNext = 0);
	const char* GetOperand(DWORD dwAddress, int iLine);
	const char* GetAssemblyCode(DWORD dwAddress);
	const char* GetArrayOfBytes(DWORD dwAddress, int iSize);
	DWORD GetProcessID(const char* procName);
	DWORD GetModuleBaseAddress(const char* modName, DWORD dwPID);

	DWORD ParseOperand(std::string szData);
	DWORD ParseOperand2(std::string szData);
	std::string ParseArray(std::string szData);

	inline static bool IsValidPtr(uint32_t Address)
	{
		return !IsBadReadPtr((LPVOID)Address, 0x8);
	}

	template <typename T>
	inline static T RPM(uint32_t Address)
	{
		__try
		{
			if (IsValidPtr(Address))
			{
				return *(T*)Address;
			}
		}
		__except (1) {}
		return T{};
	}

	template <typename T>
	inline void static WPM(uint32_t Address, T Buffer)
	{
		__try
		{
			if (IsValidPtr(Address))
			{
				*(T*)Address = Buffer;
			}
		}
		__except (1) {}
	}

private:
	static CMemory* sg_Instance;
public:
	static CMemory& GetInstance();

public:
	CMemory();
	~CMemory();
};

#define g_Memory CMemory::GetInstance()