#pragma once
#include "Singleton.h"
class Utils : public Singleton<Utils>
{
public:
	void OnConsole();

public:
	static Utils& GetSingleton();
public:
	Utils();
	virtual ~Utils();
};

#define g_Utils Utils::GetSingleton()