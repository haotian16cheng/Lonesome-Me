#pragma once
#include <string>
#include <vector>
#include "c_script_value.h"
using namespace std;

struct Scene
{
	string id;
	string name;
	string background;
};
struct Command
{
	int code;
	int indent;
	vector<CScriptValue> parameters;
};
struct Event
{
	string id;
	string name;
	int type;
	vector<Command> list;
};



class CJson
{
public:
	enum ErrorType
	{
		NO_ERROR,
		MISSING_LEFT_BRACE,
		MISSING_RIGHT_BRACE,
		MISSING_LEFT_BRACKET,
		MISSING_RIGHT_BRACKET,
		MISSING_LEFT_DQM,
		MISSING_RIGHT_DQM,
		MISSING_COMMA,
		MISSING_COLON,
		ERROR_TERMINATION,
		ILLEGAL_KEY,
		ILLEGAL_VALUE,
	};
	CJson(const char *json, const int &len);
	CJson(const string &json);
	CJson();
	~CJson();
	bool Parse(const char *json, const int &len);
	bool Parse(const string &json);
	ErrorType error_type() const;
	int error_at() const;
	Scene get_scene() const;
	vector<Event> event_vector() const;

private:
	char *data_;
	int data_len_;
	int data_at_;
	ErrorType error_type_;
	Scene scene_;
	vector<Event> event_vector_;
	bool Next();
	bool NextNoError();
	bool NextLetter(const char &ch);
	bool NextInitial(const char &ch);
	bool Key(const string& key);
	bool Value(int &value);
	bool Value(string &value);
	bool Value(bool &value);
	bool Value(vector<CScriptValue>&list);
	bool Value();
};

