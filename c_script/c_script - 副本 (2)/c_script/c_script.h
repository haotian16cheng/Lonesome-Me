#pragma once
#include <string>
#include <vector>
#include <time.h>
#include "c_json.h"
using namespace std;


class CScript
{
public:
	CScript(void(*callback)(const int&, vector<CScriptValue>, void*), void *manager);
	~CScript();
	bool LoadFromFile(const string &file_name);
	bool LoadFromData(const string &data);
	bool LoadFromData(const char *data, const int &len);
	string scene_id() const;
	string scene_name() const;
	string scene_background() const;
	int event_len() const;
	string event_id(const int &at) const;
	string event_name(const int &at) const;
	int event_type(const int &at) const;
	int variable(const int &id) const;
	int on_off(const int &id) const;
	void set_variable(const int &id, const int &value);
	void set_on_off(const int &id, const bool &value);
	void set_run_event(const int &run_event);
	CJson::ErrorType json_error_type() const;
	int json_error_at() const;
	void Run();
	void Run(const int &option_id,const string &option_name);

private:
	void(*callback_)(const int&, vector<CScriptValue>, void*);
	void *manager_;
	Scene scene_;
	vector<Event> event_vector_;
	int run_event_;
	int list_at_;
	int indent_at_;
	int option_id_;
	string option_name_;
	CJson::ErrorType json_error_type_;
	int json_error_at_;
	int variable_[1000];
	bool on_off_[1000];
	void If();
	void Else();
	void Elif();
	void Option();
	void set_variable(const vector<CScriptValue> &parameters);
	void set_on_off(const vector<CScriptValue> &parameters);
};

