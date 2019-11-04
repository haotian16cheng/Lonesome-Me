#include "c_script.h"
#include <iostream>
#include <fstream>

CScript::CScript(void(*callback)(const int&, vector<CScriptValue>, void*), void *manager) :callback_(callback), manager_(manager), run_event_(0), list_at_(0),json_error_type_(CJson::NO_ERROR),json_error_at_(-1)
{
	memset(variable_, 0, sizeof(variable_));
	memset(on_off_, 0, sizeof(on_off_));
}

CScript::~CScript()
{
}
bool CScript::LoadFromFile(const string &file_name)
{
	if (!event_vector_.empty())
	{
		event_vector_.clear();
	}
	FILE *file = fopen(file_name.c_str(), "rb");
	if (file == NULL)
	{
		return false;
	}
	fseek(file, 0, SEEK_END);
	int file_len = ftell(file);
	rewind(file);
	char *data = new char[file_len];
	if (fread(data, 1, file_len, file) != file_len)
	{
		fclose(file);
		return false;
	}
	fclose(file);
	if (!LoadFromData(data, file_len))
	{
		delete data;
		return false;
	}
	delete data;
	return true;
}

bool CScript::LoadFromData(const string & data)
{
	return LoadFromData(data.c_str(), data.length());
}

bool CScript::LoadFromData(const char * data, const int &len)
{
	CJson json(data, len);
	json_error_type_ = json.error_type();
	if (json_error_type_ == CJson::NO_ERROR)
	{
		scene_ = json.get_scene();
		event_vector_ = json.event_vector();
		return true;
	}
	json_error_at_ = json.error_at();
	cout<<"error code:"<< json.error_type()<<endl;
	cout << json.error_at()<<endl;
	return false;

}

string CScript::scene_id() const
{
	return scene_.id;
}

string CScript::scene_name() const
{
	return scene_.name;
}

string CScript::scene_background() const
{
	return scene_.background;
}

int CScript::event_len() const
{
	return event_vector_.size();
}

string CScript::event_id(const int & at) const
{
	return event_vector_[at].id;
}

string CScript::event_name(const int & at) const
{
	return event_vector_[at].name;
}

int CScript::event_type(const int & at) const
{
	return event_vector_[at].type;
}

int CScript::variable(const int & at) const
{
	return variable_[at];
}

int CScript::on_off(const int & at) const
{
	return on_off_[at];
}

void CScript::set_variable(const int & id, const int & value)
{
	variable_[id] = value;
}

void CScript::set_on_off(const int & id, const bool & value)
{
	on_off_[id] = value;
}

void CScript::set_run_event(const int & run_event)
{
	run_event_ = run_event;
	list_at_ = 0;
}

CJson::ErrorType CScript::json_error_type() const
{
	return json_error_type_;
}

int CScript::json_error_at() const
{
	return json_error_at_;
}

void CScript::Run()
{
	vector<Command> &run_list = event_vector_[run_event_].list;
	if (list_at_ == run_list.size())
	{
		return;
	}
	switch (run_list[list_at_].code)
	{
	case 103:
		Option();
		break;
	case 202:
		list_at_++;
		Run();
		break;
	case 203:
		set_on_off(run_list[list_at_].parameters);
		break;
	case 204:
		set_variable(run_list[list_at_].parameters);
		break;
	case 301:
		If();
		break;
	case 302:
		Else();
		break;
	case 303:
		Elif();
		break;
	default:
		list_at_++;
		callback_(run_list[list_at_ - 1].code, run_list[list_at_ - 1].parameters, manager_);
		break;
	}
}

void CScript::Run(const int & option_id, const string & option_name)
{
	option_id_ = option_id;
	option_name_ = option_name;
	Run();
}

void CScript::If()
{
	vector<Command> &run_list = event_vector_[run_event_].list;
	bool flag;
	switch (run_list[list_at_].parameters[0].ToInt())
	{
	case 0:
		if (on_off_[run_list[list_at_].parameters[1].ToInt()] == run_list[list_at_].parameters[2].ToBool())
		{
			flag = true;
		}
		else
		{
			flag = false;
		}
		break;
	case 1:
	{
		int value;
		switch (run_list[list_at_].parameters[2].ToInt())
		{
		case 0:
			value = run_list[list_at_].parameters[4].ToInt();
			break;
		case 1:
			value = variable_[run_list[list_at_].parameters[4].ToInt()];
			break;
		}
		switch (run_list[list_at_].parameters[3].ToInt())
		{
		case 0:
			if (variable_[run_list[list_at_].parameters[1].ToInt()] == value)
			{
				flag = true;
			}
			else
			{
				flag = false;
			}
			break;
		case 1:
			if (variable_[run_list[list_at_].parameters[1].ToInt()] > value)
			{
				flag = true;
			}
			else
			{
				flag = false;
			}
			break;
		case 2:
			if (variable_[run_list[list_at_].parameters[1].ToInt()] < value)
			{
				flag = true;
			}
			else
			{
				flag = false;
			}
			break;
		case 3:
			if (variable_[run_list[list_at_].parameters[1].ToInt()] >= value)
			{
				flag = true;
			}
			else
			{
				flag = false;
			}
			break;
		case 4:
			if (variable_[run_list[list_at_].parameters[1].ToInt()] <= value)
			{
				flag = true;
			}
			else
			{
				flag = false;
			}
			break;
		case 5:
			if (variable_[run_list[list_at_].parameters[1].ToInt()] != value)
			{
				flag = true;
			}
			else
			{
				flag = false;
			}
			break;
		}
		break;
	}
	}
	if (flag)
	{
		indent_at_ = run_list[list_at_].indent + 1;
		list_at_++;
		Run();
	}
	else
	{
		indent_at_ = run_list[list_at_].indent;
		do
		{
			list_at_++;
			if (list_at_ == run_list.size())
			{
				return;
			}
		} while (run_list[list_at_].indent > indent_at_);
		Run();
	}
}
void CScript::Else()
{
	vector<Command> &run_list = event_vector_[run_event_].list;
	if (run_list[list_at_].indent != indent_at_)
	{
		indent_at_ = run_list[list_at_].indent;
		do
		{
			list_at_++;
			if (list_at_ == run_list.size())
			{
				return;
			}
		} while (run_list[list_at_].indent > indent_at_);
	}
	else
	{
		list_at_++;
	}
	Run();
}
void CScript::Elif()
{
	vector<Command> &run_list = event_vector_[run_event_].list;
	if (run_list[list_at_].indent != indent_at_)
	{
		indent_at_ = run_list[list_at_].indent;
		do
		{
			list_at_++;
			if (list_at_ == run_list.size())
			{
				return;
			}
		} while (run_list[list_at_].indent > indent_at_||(run_list[list_at_].indent==indent_at_&&(run_list[list_at_].code==302|| run_list[list_at_].code == 303)));
		Run();
	}
	else
	{
		If();
	}
}

void CScript::Option()
{
	vector<Command> &run_list = event_vector_[run_event_].list;
	if (run_list[run_event_].parameters[0].ToInt() == option_id_&&run_list[run_event_].parameters[1].ToString() == option_name_)
	{
		indent_at_ = run_list[list_at_].indent + 1;
		list_at_++;
		Run();
	}
	else
	{
		indent_at_ = run_list[list_at_].indent;
		do
		{
			list_at_++;
			if (list_at_ == run_list.size())
			{
				return;
			}
		} while (run_list[list_at_].indent > indent_at_);
		Run();
	}
}

void CScript::set_variable(const vector<CScriptValue>& parameters)
{
	int value;
	switch (parameters[3].ToInt())
	{
	case 0:
		value = parameters[4].ToInt();
		break;
	case 1:
		value = variable_[parameters[4].ToInt()];
		break;
	case 2:
	{
		srand(clock());
		int min_value = parameters[4].ToInt();
		int max_value = parameters[5].ToInt();
		value = rand() % (max_value - min_value + 1) + min_value;
		break;
	}
	}
	int max_id = parameters[1].ToInt();
	for (int i = parameters[0].ToInt(); i < max_id; i++)
	{
		switch (parameters[2].ToInt())
		{
		case 0:
			variable_[i] = value;
			break;
		case 1:
			variable_[i] += value;
			break;
		case 2:
			variable_[i] -= value;
			break;
		case 3:
			variable_[i] *= value;
			break;
		case 4:
			variable_[i] /= value;
			break;
		case 5:
			variable_[i] %= value;
			break;
		}
	}
	list_at_++;
	Run();
}

void CScript::set_on_off(const vector<CScriptValue>& parameters)
{
	int max_id = parameters[1].ToInt();
	bool value = parameters[2].ToBool();
	for (int i = parameters[0].ToInt(); i < max_id; i++)
	{
		on_off_[i] = value;
	}
	list_at_++;
	Run();
}
