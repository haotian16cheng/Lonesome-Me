#include "c_script_value.h"



CScriptValue::CScriptValue(const CScriptValue & value):type_(value.type_),len_(value.len_)
{
	data_ = new char[len_];
	memcpy(data_, value.data_, len_);
}

CScriptValue::CScriptValue(const string & value) :type_(STRING)
{
	len_ = value.length() + 1;
	data_ = new char[len_];
	memcpy(data_, value.c_str(), len_);

}

CScriptValue::CScriptValue(const char * value) :type_(STRING)
{
	len_ = strlen(value) + 1;
	data_ = new char[len_];
	memcpy(data_, value, len_);
}

CScriptValue::CScriptValue(const bool & value) :type_(BOOL)
{
	len_ = sizeof(value);
	data_ = new char[len_];
	memcpy(data_, &value, len_);
}

CScriptValue::CScriptValue(const int & value) :type_(INT)
{
	len_ = sizeof(value);
	data_ = new char[len_];
	memcpy(data_, &value, len_);
}

CScriptValue::CScriptValue(const float & value) :type_(FLOAT)
{
	len_ = sizeof(value);
	data_ = new char[len_];
	memcpy(data_, &value, sizeof(value));
}

CScriptValue::CScriptValue() :data_(nullptr), type_(INVALID),len_(0)
{
}

CScriptValue::~CScriptValue()
{
	if (data_)
	{
		delete[] data_;
	}
}

void CScriptValue::SetValue(const string & value)
{
	type_ = STRING;
	int len =value.length() + 1;
	if (len_<len)
	{
		len_ = len;
		if (data_)
		{
			delete[] data_;
		}
		data_ = new char[len_];
	}
	memcpy(data_, value.c_str(), len);
}

void CScriptValue::SetValue(const char * value)
{
	type_ = STRING;
	int len = strlen(value) + 1;
	if (len_<len)
	{
		len_ = len;
		if (data_)
		{
			delete[] data_;
		}
		data_ = new char[len_];
	}
	memcpy(data_, value, len);
}

void CScriptValue::SetValue(const bool & value)
{
	type_ = BOOL;
	if (len_<sizeof(value))
	{
		len_ = sizeof(value);
		if (data_)
		{
			delete[] data_;
		}
		data_ = new char[sizeof(value)];
	}
	memcpy(data_, &value, sizeof(value));
}

void CScriptValue::SetValue(const int & value)
{
	type_ = INT;
	if (len_<sizeof(value))
	{
		len_ = sizeof(value);
		if (data_)
		{
			delete[] data_;
		}
		data_ = new char[sizeof(value)];
	}
	memcpy(data_, &value, sizeof(value));
}

void CScriptValue::SetValue(const float & value)
{
	type_ = FLOAT;
	if (len_<sizeof(value))
	{
		len_ = sizeof(value);
		if (data_)
		{
			delete[] data_;
		}
		data_ = new char[sizeof(value)];
	}
	memcpy(data_, &value, sizeof(value));
}

bool CScriptValue::IsNull() const
{
	return type_ == INVALID;
}

bool CScriptValue::IsString() const
{
	return type_ == STRING;
}

bool CScriptValue::IsBool() const
{
	return type_ == BOOL;
}

bool CScriptValue::IsInt() const
{
	return type_ == INT;
}

bool CScriptValue::IsFloat() const
{
	return type_ == FLOAT;
}

CScriptValue::Type CScriptValue::type() const
{
	return type_;
}

string CScriptValue::ToString() const
{
	return string(data_);
}

const char * CScriptValue::ToCString() const
{
	return data_;
}


bool CScriptValue::ToBool() const
{
	return *(bool*)data_;
}

int CScriptValue::ToInt() const
{
	return *(int*)data_;
}

float CScriptValue::ToFloat() const
{
	return *(float*)data_;
}

void CScriptValue::operator=(const CScriptValue & value)
{
	type_ = value.type_;
	if (len_ < value.len_)
	{
		len_ = value.len_;
		if (data_)
		{
			delete[] data_;
		}
		data_ = new char[len_];
	}
	memcpy(data_, value.data_, len_);
}

void CScriptValue::operator=(const string & value)
{
	type_ = STRING;
	int len = value.length() + 1;
	if (len_<len)
	{
		len_ = len;
		if (data_)
		{
			delete[] data_;
		}
		data_ = new char[len_];
	}
	memcpy(data_, value.c_str(), len);
}

void CScriptValue::operator=(const char * value)
{
	type_ = STRING;
	int len = strlen(value) + 1;
	if (len_<len)
	{
		len_ = len;
		if (data_)
		{
			delete[] data_;
		}
		data_ = new char[len_];
	}
	memcpy(data_, value, len);
}

void CScriptValue::operator=(const bool & value)
{
	type_ = BOOL;
	if (len_<sizeof(value))
	{
		len_ = sizeof(value);
		if (data_)
		{
			delete[] data_;
		}
		data_ = new char[sizeof(value)];
	}
	memcpy(data_, &value, sizeof(value));
}

void CScriptValue::operator=(const int & value)
{
	type_ = INT;
	if (len_<sizeof(value))
	{
		len_ = sizeof(value);
		if (data_)
		{
			delete[] data_;
		}
		data_ = new char[sizeof(value)];
	}
	memcpy(data_, &value, sizeof(value));
}

void CScriptValue::operator=(const float & value)
{
	type_ = FLOAT;
	if (len_<sizeof(value))
	{
		len_ = sizeof(value);
		if (data_)
		{ 
			delete[] data_;
		}
		data_ = new char[sizeof(value)];
	}
	memcpy(data_, &value, sizeof(value));
}



