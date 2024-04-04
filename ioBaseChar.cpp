#include "StdAfx.h"
#include "ioBaseChar.h"

ioBaseChar::ioBaseChar()
{

}

ioBaseChar::~ioBaseChar()
{

}

int ioBaseChar::GetState()
{
	return m_iCharState;
}

ioHashString ioBaseChar::GetPublicID()
{
	return m_szName;
}