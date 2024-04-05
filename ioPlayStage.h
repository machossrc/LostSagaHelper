#pragma once
#include <vector>

class ioBaseChar;

typedef std::vector<ioBaseChar*> BaseCharList;


class ioPlayStage
{
public:
	void* m_pSceneMgr;
	char Buffer[36];
	BaseCharList m_BaseCharList;

public:

	ioPlayStage();
	~ioPlayStage();
};