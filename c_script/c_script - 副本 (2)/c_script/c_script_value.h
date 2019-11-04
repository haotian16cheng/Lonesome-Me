#pragma once
#include <string>
#include <vector>
#include<iostream>
using namespace std;



class CScriptValue
{
public:
	enum Type
	{
		INVALID,
		STRING,
		BOOL,
		INT,
		FLOAT
	};
	CScriptValue(const CScriptValue &value);
	CScriptValue(const string &value);
	CScriptValue(const char *value);
	CScriptValue(const bool &value);
	CScriptValue(const int &value);
	CScriptValue(const float &value);
	CScriptValue();
	~CScriptValue();
	void SetValue(const string &value);
	void SetValue(const char *value);
	void SetValue(const bool &value);
	void SetValue(const int &value);
	void SetValue(const float &value);
	bool IsNull() const;
	bool IsString() const;
	bool IsBool() const;
	bool IsInt() const;
	bool IsFloat() const;
	Type type() const;
	string ToString() const;
	const char *ToCString() const;
	bool ToBool() const;
	int ToInt() const;
	float ToFloat() const;
	void operator=(const CScriptValue &value);
	void operator=(const string &value);
	void operator=(const char *value);
	void operator=(const bool &value);
	void operator=(const int &value);
	void operator=(const float &value);
private:
	char *data_;
	Type type_;
	int len_;
};

