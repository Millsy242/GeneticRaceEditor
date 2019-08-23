#ifndef __XML_WRITER__
#define __XML_WRITER__

#include <string>
#include <map>
#include <stack>

class XMLWriter
{
private:
	std::string _data;
	std::stack<std::string> _tagStack;
	std::map<std::string, std::string> _attributes;
	int _indent;
	bool _hasData;
	bool _justWroteData;
	bool _denyFlush;
	void FlushTag ();
	std::string Escape ( const std::string& str );
	void NewLine ();
public:
	XMLWriter ();
	~XMLWriter ();
	
	const std::string& GetString () const { return _data; }
	
	void Open ( const std::string& tag );
	void Attribute ( const std::string& name, const std::string& value );
	void Attribute ( const std::string& name, int value );
	void Attribute ( const std::string& name, float value );
	void Close ();
	void Data ( const std::string& data );
	void Data ( int data );
	void Data ( float data );
};

#endif
