#include "xmlwriter.h"
#include <stdio.h>

XMLWriter::XMLWriter ()
: _hasData(false), _data("<?xml version=\"1.0\"?>\n"), _indent(0), _justWroteData(false), _denyFlush(false)
{
}

XMLWriter::~XMLWriter ()
{
}

std::string XMLWriter::Escape ( const std::string& str )
{
	return str;
}

void XMLWriter::NewLine ()
{
	_data.push_back('\n');
	for (int i = 0; i < _indent; i++)
	{
		_data.push_back('\t');
	}
}

void XMLWriter::FlushTag ()
{
	if (_denyFlush)
		return;
	if (_tagStack.empty())
		return;
	std::string top = _tagStack.top();
	NewLine();
	if (_hasData)
	{
		_indent++;
	}
	_data.push_back('<');
	_data.append(top);
	for (std::map<std::string, std::string>::iterator iter = _attributes.begin();
													  iter != _attributes.end();
													  ++iter)
	{
		_data.push_back(' ');
		_data.append(iter->first);
		_data.push_back('=');
		_data.push_back('"');
		_data.append(Escape(iter->second));
		_data.push_back('"');
	}
	_attributes.clear();
	if (!_hasData)
	{
		_data.append(" />");
	}
	else
	{
		_data.append(">");
	}
}

static std::string MakeStringFromInt ( int i )
{
	char buf[16];
	sprintf(buf, "%d", i);
	return std::string(buf);
}

static std::string MakeStringFromFloat ( float f )
{
	char buf[24];
	sprintf(buf, "%f", f);
	return std::string(buf);
}

void XMLWriter::Open ( const std::string& tag )
{
	_hasData = true;
	FlushTag();
	_hasData = false;
	_tagStack.push(tag);
	_justWroteData = false;
	_denyFlush = false;
}

void XMLWriter::Attribute ( const std::string& name, const std::string& value )
{
	_attributes[name] = value;
}

void XMLWriter::Attribute ( const std::string& name, int value )
{
	Attribute(name, MakeStringFromInt(value));
}

void XMLWriter::Attribute ( const std::string& name, float value )
{
	Attribute(name, MakeStringFromFloat(value));
}

void XMLWriter::Close ()
{
	if (!_hasData)
	{
		FlushTag();
		_tagStack.pop();
	}
	else
	{
		_indent--;
		NewLine();
		_data.append("</" + _tagStack.top() + ">");
		_tagStack.pop();
		_denyFlush = true;
	}
	_hasData = true;
	_justWroteData = false;
}

void XMLWriter::Data ( const std::string& data )
{
	if (!_hasData)
	{
		_hasData = true;
		FlushTag();
	}
	if (!_justWroteData)
		NewLine();
	_justWroteData = true;
	_data.append(data);
	_denyFlush = false;
}

void XMLWriter::Data ( int data )
{
	Data(MakeStringFromInt(data));
}

void XMLWriter::Data ( float data )
{
	Data(MakeStringFromFloat(data));
}
