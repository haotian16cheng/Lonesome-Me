#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include "c_script.h"
using namespace std;
class RPGEventManager
{
private:
	CScript *script;
public:
	RPGEventManager();
	~RPGEventManager();
	void Init();
	void AddEvent(int code, vector<CScriptValue> parameters);
	static void AddEvent(const int &code, vector<CScriptValue> parameters, void *manager);
};

