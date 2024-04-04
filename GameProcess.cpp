#include "StdAfx.h"

#include "GameProcess.h"

GameManager* GameManager::sg_Instance = NULL;

GameManager& GameManager::GetInstance()
{
	if (sg_Instance == NULL)
		sg_Instance = new GameManager;
	return *sg_Instance;
}

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}