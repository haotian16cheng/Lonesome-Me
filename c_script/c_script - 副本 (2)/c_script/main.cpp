#include <iostream>
#include <string>
#include <conio.h>
#include "c_script.h"
#include "rpg_event_manager.h"

using namespace std;
void main()
{
	//cout << *((int*)a)<<endl;
	RPGEventManager *manager = new RPGEventManager;
	manager->Init();
}