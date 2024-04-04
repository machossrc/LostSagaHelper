#pragma once
class ioBaseChar
{
private:
	char Buffer1[100]; //필요 없는 구조체의 크기 만큼 Buffer 의 크기를 증가 시킨다.

	DWORD aa; //필요한 정보를 가져오고

	char Buffer2[24]; //버퍼를 증가 시킨다

public:
	ioBaseChar();
	~ioBaseChar();
};