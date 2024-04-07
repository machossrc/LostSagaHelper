#include "StdAfx.h"
#include "MemoryManager.h"
#include <sstream>
#include <regex>
#include <capstone/capstone.h>
#include <TlHelp32.h>

CMemory* CMemory::sg_Instance = NULL;

CMemory& CMemory::GetInstance()
{
    if (sg_Instance == NULL)
        sg_Instance = new CMemory;
    return *sg_Instance;
}

CMemory::CMemory()
{

}

CMemory::~CMemory()
{

}

DWORD CMemory::GetProcessID(const char* procName)
{
    DWORD procID = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);
        if (Process32First(hSnap, &procEntry))
        {
            do
            {
                if (!_stricmp(procEntry.szExeFile, procName))
                {
                    procID = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procID;
}

DWORD CMemory::GetModuleBaseAddress(const char* modName, DWORD dwPID)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwPID);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (!_stricmp(modEntry.szModule, modName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

int CMemory::ChartoAob(const char szArrays[], BYTE b[], BOOL m[])
{
    int i, Hit = 0;
    for (i = 0; szArrays[i] != 0x00; i++)
    {
        if (szArrays[i] == 0x3F) { b[Hit] = 0x00; m[Hit / 2] = TRUE; Hit++; continue; }
        if (szArrays[i] >= 0x61 && szArrays[i] <= 0x66) { b[Hit] = szArrays[i] - 0x57; Hit++; }
        else if (szArrays[i] >= 0x41 && szArrays[i] <= 0x46) { b[Hit] = szArrays[i] - 0x37; Hit++; }
        else if (szArrays[i] >= 0x30 && szArrays[i] <= 0x39) { b[Hit] = szArrays[i] - 0x30; Hit++; }
    }

    if (Hit % 2 != 0) return -1;

    Hit = Hit / 2;

    for (i = 0; i < Hit; i++)
    {
        b[i] = b[i * 2] * 0x10 + b[i * 2 + 1];
    }

    return Hit;
}

DWORD CMemory::AobScan(const char szArrays[], DWORD dwStart, DWORD dwEnd, int iNext) //~¹øÀç²¨
{
    BYTE bByteCode[0x180];
    BOOL bMask[0x180] = { 0 };
    int hit, i;
    DWORD dwMemory;
    hit = ChartoAob(szArrays, bByteCode, bMask);

    int iFoundCount = 0;

    __try
    {
        for (dwMemory = dwStart; dwMemory < dwEnd; dwMemory++)
        {
            for (i = 0; i < hit; i++)
            {
                if (bMask[i] == TRUE)
                {
                    continue;
                }
                if (RPM<BYTE>(dwMemory + i) ^ bByteCode[i])
                {
                    break;
                }
            }
            if (i == hit)
            {
                iFoundCount++;
                if (iNext != 0)
                {
                    if (iNext == iFoundCount)
                    {
                        return dwMemory;
                    }
                    else
                    {
                        continue;
                    }
                }
                return dwMemory;
            }
        }

    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return 0;
    }
    return 0;
}

const char* CMemory::GetOperand(DWORD dwAddress, int iLine)
{
    csh handle;
    cs_insn* insn;
    size_t count;

    cs_open(CS_ARCH_X86, CS_MODE_32, &handle);

    DWORD oldProtect;
    VirtualProtectEx(GetCurrentProcess(), reinterpret_cast<void*>(dwAddress), sizeof(uint8_t), PAGE_EXECUTE_READWRITE, &oldProtect);

    BYTE opcode[16];
    ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPCVOID>(dwAddress), opcode, sizeof(opcode), nullptr);
    count = cs_disasm(handle, opcode, sizeof(opcode), dwAddress, 0, &insn);

    char szAssembly[1024];
    sprintf(szAssembly, "%s", insn[iLine].op_str);

    VirtualProtectEx(GetCurrentProcess(), reinterpret_cast<void*>(dwAddress), sizeof(uint8_t), oldProtect, &oldProtect);
    cs_free(insn, count);
    cs_close(&handle);

    return szAssembly;
}

const char* CMemory::GetArrayOfBytes(DWORD dwAddress, int iSize)
{
    BYTE opcode[16];
    SIZE_T bytesRead;
    ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPCVOID>(dwAddress), opcode, sizeof(opcode), &bytesRead);

    char szArray[1024] = "";
    if (iSize == 0)
    {
        for (SIZE_T i = 0; i < bytesRead; i++)
        {
            char szBuf[256];
            sprintf(szBuf, "0x%02X ", static_cast<int>(opcode[i]));
            strcat(szArray, szBuf);
        }
    }
    else
    {
        for (SIZE_T i = 0; i < iSize; i++)
        {
            char szBuf[256];
            sprintf(szBuf, "0x%02X ", static_cast<int>(opcode[i]));
            strcat(szArray, szBuf);
        }
    }

    return szArray;
}

const char* CMemory::GetAssemblyCode(DWORD dwAddress)
{

    csh handle;
    cs_insn* insn;
    size_t count;

    cs_open(CS_ARCH_X86, CS_MODE_32, &handle);

    DWORD oldProtect;
    VirtualProtectEx(GetCurrentProcess(), reinterpret_cast<void*>(dwAddress), sizeof(uint8_t), PAGE_EXECUTE_READWRITE, &oldProtect);

    BYTE opcode[16];
    ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPCVOID>(dwAddress), opcode, sizeof(opcode), nullptr);
    count = cs_disasm(handle, opcode, sizeof(opcode), dwAddress, 0, &insn);

    char szAssembly[1024];

    for (size_t i = 0; i < count; i++)
    {
        char szBuf[256];
        sprintf(szBuf, "%s %s\n", insn[i].mnemonic, insn[i].op_str);
        strcat(szAssembly, szBuf);
    }


    VirtualProtectEx(GetCurrentProcess(), reinterpret_cast<void*>(dwAddress), sizeof(uint8_t), oldProtect, &oldProtect);
    cs_free(insn, count);
    cs_close(&handle);

    return szAssembly;
}

DWORD CMemory::ParseOperand(std::string szData)
{
    size_t startPos = szData.find("[");

    DWORD dwFoundAddress = 0;
    if (startPos != std::string::npos)
    {
        size_t endPos = szData.find("]", startPos);
        if (endPos != std::string::npos)
        {
            std::string addressStr = szData.substr(startPos + 1, endPos - startPos - 1);
            char* endPtr;
            dwFoundAddress = std::strtoul(addressStr.c_str(), &endPtr, 16);
        }
    }
    return dwFoundAddress;
}

DWORD CMemory::ParseOperand2(std::string szData)
{
    std::istringstream iss(szData);
    std::string opcode, hexValue;

    iss >> opcode >> hexValue;

    std::stringstream converter;
    converter << std::hex << hexValue;
    DWORD value;
    converter >> value;

    return value;
}

std::string CMemory::ParseArray(std::string szData)
{
    std::regex pattern("(0x[0-9A-Fa-f]+)");
    std::string result = std::regex_replace(szData, pattern, ", $&");

    if (!result.empty() && result[0] == ',')
    {
        result = result.substr(2);
    }

    return result;
}