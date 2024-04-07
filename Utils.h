#pragma once
class Utils
{
public:
	void OnConsole();

private:
	static Utils* sg_Instance;
public:
	static Utils& GetInstance();

public:
	Utils();
	virtual ~Utils();
};

#define g_Utils Utils::GetInstance()