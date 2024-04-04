#include "StdAfx.h"
#include "Utils.h"

using namespace std;

template<> Utils* Singleton<Utils>::ms_Singleton = 0;

void Utils::OnConsole()
{
	if (AllocConsole())
	{
		freopen("CONIN$", "rb", stdin);
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);
		ios::sync_with_stdio();
	}
}

Utils& Utils::GetSingleton()
{
	return Singleton<Utils>::GetSingleton();
}

Utils::Utils()
{

}

Utils::~Utils()
{

}