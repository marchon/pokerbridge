/* LICENSE NOTICE
	Copyright (c) 2008, Frederick Emmott <mail@fredemmott.co.uk>

	Permission to use, copy, modify, and/or distribute this software for any
	purpose with or without fee is hereby granted, provided that the above
	copyright notice and this permission notice appear in all copies.

	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
	WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
	MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
	ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
	WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
	ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
	OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#include "stdafx.h"
#include "json.h"


#define FAIL(x) throw JsonParseException(*m_sym, x, remaining())


///// JsonParseException
JsonParseException::JsonParseException(const QString& got, const QString& expected, const QString& remaining) throw()
	:
		m_got(got),
		m_expected(expected),
		m_remaining(remaining)
{
}

JsonParseException::~JsonParseException() throw(){}

const char* JsonParseException::what() const throw()
{
	return qPrintable(m_text=QObject::tr("A parsing error occurred:\n\tGot: '%1'\n\tExpected: '%2'\n\tAt: '%3'").arg(m_got).arg(m_expected).arg(m_remaining));
}

QString JsonParseException::got() { return m_got; }
QString JsonParseException::expected() { return m_expected; }
QString JsonParseException::remaining() { return m_remaining; }

QString JsonParseException::m_text;


///// JSonToVariant


JsonToVariant::JsonToVariant(){}

QVariant JsonToVariant::parse(const QString& json) throw(JsonParseException)
{
	JsonToVariant parser;
	// Store the start and end of the string
	parser.m_next = json.constBegin();
	parser.m_sym = parser.m_next;
	parser.m_end = json.constEnd();
	// Parse any JSON value.
	return parser.parseValue();
}

QList<QVariantMap> JsonToVariant::multiParse(const QString& raw) throw(JsonParseException)
{
	QList<QVariantMap> objects;
	QString json(raw.trimmed());

	JsonToVariant parser;
	// Store the start and end of the string
	parser.m_next = json.constBegin();
	parser.m_sym = parser.m_next;
	parser.m_end = json.constEnd();
	// A JSON Object is the top-level item in the parse tree
	do
	{
		objects.append(parser.parseObject());
	}
	while(parser.m_next != parser.m_end && parser.m_sym != parser.m_end);
	return objects;
}

QVariantMap JsonToVariant::parseObject()
{
	/*
	 * object
	 * 	{}
	 * 	{ members }
	 */

	QVariantMap data;

	consume('{');
	if(peekNext() != '}')
		data = parseMembers();
	consume('}');

	return data;
}

QVariantMap JsonToVariant::parseMembers()
{
	/*
	 * members
	 * 	pair
	 * 	pair , members
	 */

	QVariantMap data;
	QPair<QString, QVariant> pair;

	// loop instead of recursing
	do
	{
		// Grab a pair
		pair = parsePair();

		// Store it in our data
		data[pair.first] = pair.second;
	}
	while(tryConsume(',')); // Loop if we've got a list separator

	return data;
}

QPair<QString, QVariant> JsonToVariant::parsePair()
{
	/*
	 * pair
	 * 	string : value
	 */

	QString key = parseString();
	consume(':');
	QVariant value = parseValue();

	return qMakePair(key, value);
}

QVariantList JsonToVariant::parseArray()
{
	/*
	 * array
	 * 	[]
	 * 	[ elements ]
	 */

	QVariantList data;

	consume('[');
	if(peekNext() != ']')
		data = parseElements();
	consume(']');

	return data;
}

QVariantList JsonToVariant::parseElements()
{
	/*
	 * elements
	 * 	value
	 * 	value , elements
	 */
	QVariantList data;

	// loop instead of recursing
	do
	{
		// Grab a value
		data += parseValue();
	}
	while(tryConsume(',')); // repeat if we've got a list separator

	return data;
}

QVariant JsonToVariant::parseValue()
{
	/*
	 * value
	 * 	string
	 * 	number
	 * 	object
	 * 	array
	 * 	bool
	 * 	null
	 */

	tryConsume(':');

	// Lookahead to work out the type of value
	switch(peekNext().toAscii())
	{
		case '"':
			return parseString();
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '-':
			return parseNumber();
		case '{':
			return parseObject();
		case '[':
			return parseArray();
		case 't': // true
		case 'f': // false
			return parseBool();
		case 'n': // null
			return parseNull();
		default:
			FAIL(QObject::tr("string, number, object, array, bool, or null"));
	}
}

QString JsonToVariant::parseString()
{
	/*
	 * string
	 * 	""
	 * 	" chars "
	 */

	QString data;

	// Starting quotation marks
	consume('"');

	// If it's a non-empty string, grab the contents
	if(*m_next != '"')
		data = parseChars();

	// Ending quotation marks
	consume('"');

	return data;
}

QString JsonToVariant::parseChars()
{
	/*
	 * chars
	 * 	char
	 * 	char chars
	 */

	QString data;

	// chars contains at least one char
	data = parseChar();

	while(peekNext() != '"')
		data.append( parseChar() );
	return data;
}

QChar JsonToVariant::parseChar()
{
	/*
	 * char
	 * 	any character except for ", \, or control characters
	 *	\"
	 *	\\
	 *	\/
	 *	\b
	 *	\f
	 *	\n
	 *	\r
	 *	\t
	 *	\u four-hex-digits
	 */

	// Grab the next character, without skipping whitespace
	consume(false);

	// We're not allowed unescaped quotation marks
	if(*m_sym == '"')
		FAIL(QObject::tr("Any unicode character except for \" or JSON escape sequences"));
	
	// But some escape sequences are allowed
	if(*m_sym == '\\')
	{
		QString digits;
		switch(consume().toAscii())
		{
			case '"':
				return '"';
			case '\\':
				return '\\';
			case '/':
				return '/';
			case 'b':
				return '\b';
			case 'f':
				return '\f';
			case 'n':
				return '\n';
			case 'r':
				return '\r';
			case 't':
				return '\t';
			case 'u':
				// Unicode 4-digit hex
				for(int i = 0; i < 4; ++i)
				{
					digits += parseHexDigit();
				}
				return QChar(digits.toInt(0, 16));
			default:
				FAIL("[\"\\/bfnrtu]");
		}
	}
	return *m_sym;
}

QVariant JsonToVariant::parseNumber()
{
	/*
	 * number
	 * 	int
	 * 	int frac
	 * 	int exp
	 * 	int frac exp
	 */

	// Every JSON number starts with an int
	QString data = parseInt();

	// Lookahead for fractions and exponents

	// Do we have a fraction?
	if(*m_next == '.') data += parseFrac();
	// Do we have an exponent?
	if(*m_next == 'e' || *m_next == 'E') data += parseExp();

	// Try several return types...
	bool ok;
	QVariant ret;

	ret = data.toInt(&ok); if(ok) return ret;
	ret = data.toLongLong(&ok); if(ok) return ret;
	ret = data.toDouble(&ok); if(ok) return ret;

	// If this point is reached, don't know how to convert the string
	// to an integer.
	Q_ASSERT(false);
	return QVariant();
}

QString JsonToVariant::parseInt()
{
	/*
	 * int
	 * 	digit
	 * 	digit1-9 digits
	 * 	- digit
	 * 	- digit1-9 digits
	 */

	QString data;

	// Match any negation mark
	if(tryConsume('-'))
		data = "-";

	// Grab the first digit...
	QChar firstDigit = parseDigit();
	data += firstDigit;
	// ...if it's not zero...
	if(firstDigit != '0')
	{
		// ... try and add more digits.
		try { data += parseDigits(); }
		catch(JsonParseException)
		{
			// Catch, as more digits are entirely optional
			// Roll back.
			m_next = m_sym--;
		}
	}
	return data;
}

QString JsonToVariant::parseFrac()
{
	/*
	 * frac
	 * 	. digits
	 */

	consume('.');
	return QString(".%1").arg(parseDigits());
}

QString JsonToVariant::parseExp()
{
	/*
	 * exp
	 * 	e digits
	 */

	QString data;
	data = parseE();
	data += parseDigits();
	return data;
}

QString JsonToVariant::parseDigits()
{
	/*
	 * digits
	 * 	digit
	 * 	digit digits
	 */

	QString data;

	// Digits has at least one digit...
	data += parseDigit();

	// ... try and get some more
	// Loop instead of recurse
	Q_FOREVER
	{
		try { data += parseDigit(); }
		catch(JsonParseException)
		{
			m_next = m_sym--; // roll back
			break;
		}
	}
	return data;
}

QString JsonToVariant::parseE()
{
	/*
	 * e
	 * 	e
	 * 	e+
	 * 	e-
	 * 	E
	 * 	E+
	 * 	E-
	 */

	// Try and grab an 'e' or 'E'
	if(consume(false).toLower() == 'e')
	{
		// digits in follow[e]
		if(m_next->isDigit())
			return "e";

		// Hopefully the next is a + or -
		// grab another chracter...
		consume(false);
		// If it's not + or -, fail
		if(*m_sym != '+' && *m_sym != '-')
			FAIL("+ | -");

		// Otherwise, return e[+-]
		return QString("e%1").arg(*m_sym);
	}
	else
		FAIL("e | E");
}


QChar JsonToVariant::parseDigit()
{
	/*
	 * digit
	 * 	[0-9]
	 */

	if(!consume(false).isDigit())
		FAIL("[0-9]");
	return *m_sym;
}

QChar JsonToVariant::parseHexDigit()
{
	/*
	 * hexdigit
	 * 	[0-9a-fA-F]
	 */

	QChar character = consume().toLower();
	if(character.isDigit() || (character >= 'a' && character <= 'f'))
		return character;
	FAIL("[0-9a-fA-F]");
}

bool JsonToVariant::parseBool()
{
	/*
	 * bool
	 * 	true
	 * 	false
	 */

	switch(peekNext().toAscii())
	{
		case 't':
			consume(QString("true"));
			return true;
		case 'f':
			consume(QString("false"));
			return false;
		default:
			consume(false);
			FAIL("true | false");
	}
}

QVariant JsonToVariant::parseNull()
{
	/*
	 * null
	 * 	null
	 */

	consume(QString("null"));
	return QVariant();
}

QString JsonToVariant::remaining()
{
	QString data;

	QString::ConstIterator it = m_sym;
	while(it != m_end) data += *it++;

	return data;
}

QChar JsonToVariant::consume(bool skipWhitespace) throw(JsonParseException)
{
	// Read a character...
	do
	{
		if(m_next == m_end)
		{
			throw JsonParseException("EOF", "symbol", remaining());
		}
		m_sym = m_next++;
	}
	//...and loop while we get whitespace, if it's being skipped
	while(skipWhitespace && m_sym->isSpace());

	// Just for convenience...
	return *m_sym;
}

void JsonToVariant::consume(QChar wanted) throw(JsonParseException)
{
	// Grab a char(ignoring whitespace), and if it's not what's
	// expected, throw
	if(consume() != wanted)
	{
		FAIL(wanted);
	}
}

void JsonToVariant::consume(char wanted) throw(JsonParseException)
{
	// Convenience function for the above
	consume(QChar(wanted));
}

void JsonToVariant::consume(QString wanted) throw(JsonParseException)
{
	// Keep track of where we start...
	QString::ConstIterator it = m_sym;
	// Grab wanted.length() characters, and compare them to the
	// character in the appropriate position in the parameter
	for(int i = 0; i < wanted.length(); ++i)
		if(consume(false) != wanted[i])
		{
			// If it doesn't match, roll back, and throw a
			// parse exception
			m_sym = it;
			m_next = ++it;
			FAIL(wanted);
		}
}

bool JsonToVariant::tryConsume(QChar wanted) throw()
{
	// Grab the next character
	try
	{
		consume();
	}
	catch(JsonParseException)
	{
		// End-Of-String, rollback and return false
		m_next = m_sym--;
		return false;
	}

	// Check if it's what we want
	if(*m_sym != wanted)
	{
		// nope, something else, rollback and return false
		m_next = m_sym--;
		return false;
	}
	return true;
}

QChar JsonToVariant::peekNext(bool skipWhitespace) throw(JsonParseException)
{
	QString::ConstIterator it = m_sym;
	do
	{
		++it;
		if(it == m_end)
		{
			FAIL("symbol");
		}
	}
	while(skipWhitespace && it->isSpace());
	return *it;
}



/////// JsonReader


JsonReader::JsonReader(QObject *parent) : QObject(parent)
{
	input = 0;
	braces = 0;
	inString = false;
	inEscape = false;
	started = false;
}

void JsonReader::setInput(QIODevice *dev)
{
	input = dev;
}

bool JsonReader::parse()
{
	QByteArray data = input->readAll();
	QString s(data);

	qLog(Debug)<<"read:"<<s<<endl;

	for(int i=0;i<s.size();i++)
	{
		QChar c = s[i];
		if(!inString)
		{
			inEscape=false;
			if(c=='{')
			{
				braces++;
				started=true;
			}
			else if(c=='}')
				braces--;
			else if(c=='\"')
				inString=true;
		}
		else 
		{
			if(c=='\"')
				if(!inEscape)
					inString=false;
			inEscape=false;
			if(c=='\\')
				inEscape=true;
		}
		json.append(c);
		if(started && braces==0)
		{
			started = false;
			bool result=true;
			try{
				QVariant value = JsonToVariant::parse(json);
				json="";
	//			qLog(Debug)<<"JsonReader::parse"<<value<<endl;
				emit parsed(value.toMap());
				result = true;
			}catch(JsonParseException &x)
			{
				qLog(Debug)<<"failed to parse json "<<x.what();			
				result = false;
			}
			json="";
		}

	}
	return true;
}

QVariant JsonReader::lastParsed()
{
	return value;
}


QString qQuote(QString input)
{
	QString result="\"";
	for(int i=0;i<input.size();i++)
	{
		if(input[i]=='\"')
			result.append('\\');
		result.append(input[i]);
	}
	result.append('\"');
	return result;
}

QString VariantToJson::toJson(QVariantMap v)
{
	QString result;

	result.append("{\n");

	bool first = true;
	Q_FOREACH(QString key, v.keys())
	{
		if(!first){
			result.append(",");
		}
		first=false;
		QVariant node = v[key];
		result.append("\"").append(key).append("\":").append(toJson(node));
	}
	result.append("}\n");
	return result;
}

QString VariantToJson::toJson(QVariantList v)
{
	QString result;
	result.append("[");
	for(int i=0;i<v.size();i++)
	{
		if(i>0)
			result.append(",");
		result.append(toJson(v[i]));
	}
	result.append("]");
	return result;
}

QString VariantToJson::toJson(QVariant v)
{
	switch(v.type())
	{
	case QVariant::Map:
			return toJson(v.toMap());
	case QVariant::List:
		return toJson(v.toList());
	case QVariant::String:
	case QVariant::ByteArray:
		return qQuote(v.toString());
	case QVariant::Invalid:
		return "null";
	default:
		return qQuote(v.toString());
	}
}

void ObjectVariant::objectToVariant(QVariantMap &map, QObject *obj)
{
	for(int i = obj->metaObject()->propertyOffset(); i<obj->metaObject()->propertyCount(); i++)
	{
		QMetaProperty &p = obj->metaObject()->property(i);
		map[p.name()] = p.read(obj);
	}
}

void ObjectVariant::variantToObject(const QVariantMap &map, QObject *obj)
{
	for(int i = obj->metaObject()->propertyOffset(); i<obj->metaObject()->propertyCount(); i++)
	{
		QMetaProperty &p = obj->metaObject()->property(i);
		if(map.contains(p.name()))
			p.write(obj, map[p.name()]);
	}
}

QString ObjectVariant::toShortString(QVariantMap &map)
{
	QString result="(";
	Q_FOREACH(QString key, map.keys())
	{
		if(result.isEmpty())
			result.append(", ");
		result.append(key);
		result.append("=");
		result.append(map.value(key).toString());
	}
	result.append(")");
	return result;
}

