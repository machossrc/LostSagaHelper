#include "StdAfx.h"
#include "Utils.h"

using namespace std;

Utils* Utils::sg_Instance = NULL;

Utils& Utils::GetInstance()
{
	if (sg_Instance == NULL)
		sg_Instance = new Utils;
	return *sg_Instance;
}

Utils::Utils()
{

}

Utils::~Utils()
{

}

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