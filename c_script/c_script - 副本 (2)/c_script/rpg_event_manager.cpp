#include "rpg_event_manager.h"



RPGEventManager::RPGEventManager()
{
	void(*callback)(const int&, vector<CScriptValue>, void*) = AddEvent;
	script = new CScript(callback, this);
}


RPGEventManager::~RPGEventManager()
{
}

void RPGEventManager::Init()
{
	if (script->LoadFromFile("3.txt"))
	{
		script->set_run_event(0);
		script->Run();
	}
	_getch();
}

void RPGEventManager::AddEvent(int code, vector<CScriptValue> parameters)
{
	switch (code)
	{
	case 1:
		cout << "1";
		script->Run();
		break;
	case 2:
		cout << "2";
		script->Run();
		break;
	case 3:
		cout << "3";
		script->Run();
		break;
	case 4:
		cout << "4";
		script->Run();
		break;
	case 5:
		cout << parameters[0].ToString();
		script->Run();
		break;
	default:
		break;
	}
}

void RPGEventManager::AddEvent(const int &code, vector<CScriptValue> parameters, void * manager)
{
	((RPGEventManager*)manager)->AddEvent(code, parameters);
}
