#include "c_json.h"


CJson::CJson(const char * json, const int & len)
{
	Parse(json, len);
}

CJson::CJson(const string & json)
{
	Parse(json);
}

CJson::CJson() :error_type_(CJson::NO_ERROR)
{

}

CJson::~CJson()
{
}
bool CJson::Parse(const char * json, const int & len)
{
	data_ = (char*)json;
	data_len_ = len;
	data_at_ = 0;
	if (!Next())
	{
		return false;
	}
	if (!NextInitial('{'))
	{
		return false;
	}
	if (!Key("id"))
	{
		return false;
	}
	Event event;
	if (!Value(scene_.id))
	{
		return false;
	}
	if (!NextInitial(','))
	{
		return false;
	}
	if (!Key("name"))
	{
		return false;
	}
	if (!Value(scene_.name))
	{
		return false;
	}
	if (!NextInitial(','))
	{
		return false;
	}
	if (!Key("background"))
	{
		return false;
	}
	if (!Value(scene_.background))
	{
		return false;
	}
	if (!NextInitial('}'))
	{
		return false;
	}
	while (NextNoError())
	{
		if (!NextInitial('{'))
		{
			return false;
		}
		if (!Key("id"))
		{
			return false;
		}
		Event event;
		if (!Value(event.id))
		{
			return false;
		}
		if (!NextInitial(','))
		{
			return false;
		}
		if (!Key("name"))
		{
			return false;
		}
		if (!Value(event.name))
		{
			return false;
		}
		if (!NextInitial(','))
		{
			return false;
		}
		if (!Key("type"))
		{
			return false;
		}
		if (!Value(event.type))
		{
			return false;
		}
		if (!NextInitial(','))
		{
			return false;
		}
		if (!Key("note"))
		{
			return false;
		}
		if (!Value())
		{
			return false;
		}
		if (!NextInitial(','))
		{
			return false;
		}
		if (!Key("list"))
		{
			return false;
		}
		if (!NextInitial('['))
		{
			return false;
		}
		if (!Next())
		{
			return false;
		}
		int list_at = 0;
		if (data_[data_at_] == '{')
		{
			data_at_++;
			if (!Key("code"))
			{
				return false;
			}
			Command command;
			if (!Value(command.code))
			{
				return false;
			}
			if (!NextInitial(','))
			{
				return false;
			}
			if (!Key("indent"))
			{
				return false;
			}
			if (!Value(command.indent))
			{
				return false;
			}
			if (!NextInitial(','))
			{
				return false;
			}
			if (!Key("parameters"))
			{
				return false;
			}
			if (!NextInitial('['))
			{
				return false;
			}
			if (!Next())
			{
				return false;
			}
			if (Value(command.parameters))
			{
				while (true)
				{
					if (data_[data_at_] == ',')
					{
						data_at_++;
						if (!Value(command.parameters))
						{
							return false;
						}
					}
					else if (data_[data_at_] == ']')
					{
						data_at_++;
						break;
					}
					else
					{
						error_type_ = CJson::ILLEGAL_VALUE;
						return false;
					}
				}
			}
			else if (data_[data_at_] == ']')
			{
				data_at_++;
			}
			else
			{
				error_type_ = CJson::ILLEGAL_VALUE;
				return false;
			}
			event.list.push_back(command);
			if (!Next())
			{
				return false;
			}
			if (!NextInitial('}'))
			{
				return false;
			}
			if (!Next())
			{
				return false;
			}
			while (true)
			{
				if (data_[data_at_] == ',')
				{
					data_at_++;
					if (!Next())
					{
						return false;
					}
					if (!NextInitial('{'))
					{
						return false;
					}
					if (!Key("code"))
					{
						return false;
					}
					Command command;
					if (!Value(command.code))
					{
						return false;
					}
					if (!NextInitial(','))
					{
						return false;
					}
					if (!Key("indent"))
					{
						return false;
					}
					if (!Value(command.indent))
					{
						return false;
					}
					if (!NextInitial(','))
					{
						return false;
					}
					if (!Key("parameters"))
					{
						return false;
					}
					if (!NextInitial('['))
					{
						return false;
					}
					if (!Next())
					{
						return false;
					}
					if (Value(command.parameters))
					{
						while (true)
						{
							if (data_[data_at_] == ',')
							{
								data_at_++;
								if (!Value(command.parameters))
								{
									return false;
								}
							}
							else if (data_[data_at_] == ']')
							{
								data_at_++;
								break;
							}
							else
							{
								error_type_ = CJson::ILLEGAL_VALUE;
								return false;
							}
						}
					}
					else if (data_[data_at_] == ']')
					{
						data_at_++;
					}
					else
					{
						error_type_ = CJson::ILLEGAL_VALUE;
						return false;
					}
					event.list.push_back(command);
					if (!Next())
					{
						return false;
					}
					if (!NextInitial('}'))
					{
						return false;
					}
					if (!Next())
					{
						return false;
					}
				}
				else if (NextInitial(']'))
				{
					break;
				}
				else
				{
					return false;
				}
			}
		}
		else if (data_[data_at_] == ']')
		{
			data_at_++;
		}
		else
		{
			error_type_ = CJson::ILLEGAL_VALUE;
			return false;
		}
		if (!Next())
		{
			return false;
		}
		if (!NextInitial('}'))
		{
			return false;
		}
		event_vector_.push_back(event);
	}
	return true;
}
bool CJson::Parse(const string & json)
{
	return Parse(json.c_str(), json.length());
}
CJson::ErrorType CJson::error_type() const
{
	return error_type_;
}
int CJson::error_at() const
{
	return data_at_;
}

Scene CJson::get_scene() const
{
	return scene_;
}
vector<Event> CJson::event_vector() const
{
	return event_vector_;
}
bool CJson::Next()
{
	while (data_at_ != data_len_)
	{
		if (data_[data_at_] == ' ' || data_[data_at_] == '\n' || data_[data_at_] == '\r' || data_[data_at_] == '\t')
		{
			data_at_++;
		}
		else
		{
			return true;
		}
	}
	error_type_ = CJson::ERROR_TERMINATION;
	return false;
}

bool CJson::NextNoError()
{
	while (data_at_ != data_len_)
	{
		if (data_[data_at_] == ' ' || data_[data_at_] == '\n' || data_[data_at_] == '\r' || data_[data_at_] == '\t')
		{
			data_at_++;
		}
		else
		{
			return true;
		}
	}
	error_type_ = CJson::NO_ERROR;
	return false;
}

bool CJson::NextLetter(const char & ch)
{
	if (data_at_ == data_len_)
	{
		error_type_ = CJson::ERROR_TERMINATION;
		return false;
	}
	if (data_[data_at_] == ch)
	{
		data_at_++;
		return true;
	}
	else
	{
		return false;
	}
}

bool CJson::NextInitial(const char & ch)
{
	if (data_[data_at_] == ch)
	{
		data_at_++;
		return true;
	}
	else
	{
		if (ch == '{')
		{
			error_type_ = CJson::MISSING_LEFT_BRACE;
		}
		else if (ch == '}')
		{
			error_type_ = CJson::MISSING_RIGHT_BRACE;
		}
		else if (ch == '[')
		{
			error_type_ = CJson::MISSING_LEFT_BRACKET;
		}
		else if (ch == ']')
		{
			error_type_ = CJson::MISSING_RIGHT_BRACKET;
		}
		else if (ch == ',')
		{
			error_type_ = CJson::MISSING_COMMA;
		}
		else if (ch == ':')
		{
			error_type_ = CJson::MISSING_COLON;
		}
		return false;
	}
}

bool CJson::Key(const string& value)
{
	if (!Next())
	{
		return false;
	}
	if (!NextInitial('"'))
	{
		error_type_ = CJson::MISSING_LEFT_DQM;
		return false;
	}
	int value_len = value.length();
	for (int i = 0; i < value_len; i++)
	{
		if (!NextLetter(value[i]))
		{
			error_type_ = CJson::ILLEGAL_KEY;
			return false;
		}
	}
	if (!NextLetter('"'))
	{
		error_type_ = CJson::MISSING_RIGHT_DQM;
		return false;
	}
	if (!Next())
	{
		return false;
	}
	if (!NextInitial(':'))
	{
		return false;
	}
	if (!Next())
	{
		return false;
	}
	return true;
}

bool CJson::Value(int & value)
{
	bool sign = false;
	value = 0;
	if (data_[data_at_] == '-')
	{
		sign = true;
	}
	else if (data_[data_at_] >= '0'&&data_[data_at_] <= '9')
	{
		value = value * 10 + data_[data_at_] - '0';
	}
	else if (data_[data_at_] != '+')
	{
		error_type_ = CJson::ILLEGAL_VALUE;
		return false;
	}
	data_at_++;
	if (data_at_ == data_len_)
	{
		error_type_ = CJson::ERROR_TERMINATION;
		return false;
	}
	while (true)
	{
		if (data_[data_at_] >= '0'&&data_[data_at_] <= '9')
		{
			value = value * 10 + data_[data_at_] - '0';
			data_at_++;
			if (data_at_ == data_len_)
			{
				error_type_ = CJson::ERROR_TERMINATION;
				return false;
			}
		}
		else if (data_[data_at_] == ' ' || data_[data_at_] == ',' || data_[data_at_] == ']' || data_[data_at_] == '}')
		{
			if (sign)
			{
				value *= -1;
			}
			break;
		}
		else
		{
			error_type_ = CJson::ILLEGAL_VALUE;
			return false;
		}
	}
	if (!Next())
	{
		return false;
	}
	return true;
}

bool CJson::Value(string & value)
{
	if (!NextInitial('"'))
	{
		error_type_ = CJson::MISSING_LEFT_DQM;
		return false;
	}
	value = "";
	while (true)
	{
		if (NextLetter('\\'))
		{
			if (data_at_ == data_len_)
			{
				error_type_ = CJson::ERROR_TERMINATION;
				return false;
			}
			if (data_[data_at_] == 'n')
			{
				value.push_back('\n');
				data_at_++;
			}
			else if (data_[data_at_] == 'r')
			{
				value.push_back('\r');
				data_at_++;
			}
			else if (data_[data_at_] == 't')
			{
				value.push_back('\t');
				data_at_++;
			}
			else if (data_[data_at_] == '"')
			{
				value.push_back('"');
				data_at_++;
			}
			else
			{
				value.push_back('\\');
			}
		}
		else if (NextLetter('"'))
		{
			break;
		}
		else
		{
			value.push_back(data_[data_at_]);
			data_at_++;
			if (data_at_ == data_len_)
			{
				error_type_ = CJson::ERROR_TERMINATION;
				return false;
			}
		}
	}
	if (!Next())
	{
		return false;
	}
	return true;
}

bool CJson::Value(bool & value)
{
	return false;
}

bool CJson::Value(vector<CScriptValue>&list)
{
	CScriptValue value;
	if (data_[data_at_] == '"')
	{
		data_at_++;
		string str_value="";
		while (true)
		{
			if (NextLetter('\\'))
			{
				if (data_at_ == data_len_)
				{
					error_type_ = CJson::ERROR_TERMINATION;
					return false;
				}
				if (data_[data_at_] == 'n')
				{
					str_value.push_back('\n');
					data_at_++;
				}
				else if (data_[data_at_] == 'r')
				{
					str_value.push_back('\r');
					data_at_++;
				}
				else if (data_[data_at_] == 't')
				{
					str_value.push_back('\t');
					data_at_++;
				}
				else if (data_[data_at_] == '"')
				{
					str_value.push_back('"');
					data_at_++;
				}
				else if (data_[data_at_] == '\\')
				{
					str_value.push_back('\\');
					data_at_++;
				}
				else
				{
					str_value.push_back(data_[data_at_]);
					data_at_++;
				}
			}
			else if (NextLetter('"'))
			{
				value = str_value;
				break;
			}
			else
			{
				str_value.push_back(data_[data_at_]);
				data_at_++;
				if (data_at_ == data_len_)
				{
					error_type_ = CJson::ERROR_TERMINATION;
					return false;
				}
			}
		}
	}
	else if ((data_[data_at_] >= '0'&&data_[data_at_] <= '9') || data_[data_at_] == '-' || data_[data_at_] == '+')
	{
		int int_value;
		if (!Value(int_value))
		{
			return false;
		}
		value = int_value;
	}
	else if (data_[data_at_] == 't')
	{
		data_at_++;
		if (!NextLetter('r'))
		{
			error_type_ = CJson::ILLEGAL_VALUE;
			return false;
		}
		if (!NextLetter('u'))
		{
			error_type_ = CJson::ILLEGAL_VALUE;
			return false;
		}
		if (!NextLetter('e'))
		{
			error_type_ = CJson::ILLEGAL_VALUE;
			return false;
		}
		value = true;
	}
	else if (data_[data_at_] == 'f')
	{
		data_at_++;
		if (!NextLetter('a'))
		{
			error_type_ = CJson::ILLEGAL_VALUE;
			return false;
		}
		if (!NextLetter('l'))
		{
			error_type_ = CJson::ILLEGAL_VALUE;
			return false;
		}
		if (!NextLetter('s'))
		{
			error_type_ = CJson::ILLEGAL_VALUE;
			return false;
		}
		if (!NextLetter('e'))
		{
			error_type_ = CJson::ILLEGAL_VALUE;
			return false;
		}
		value = false;
	}
	else
	{
		return false;
	}
	if (!Next())
	{
		return false;
	}
	list.push_back(value);
	return true;
}

bool CJson::Value()
{
	if (!NextInitial('"'))
	{
		error_type_ = CJson::MISSING_LEFT_DQM;
		return false;
	}
	while (!NextLetter('"'))
	{
		data_at_++;
	}
	if (!Next())
	{
		return false;
	}
	return true;
}

