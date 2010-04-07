#include "stdafx.h"
#include "pbgameoptions.h"

PBGameOptions::PBGameOptions(int options)
{
	_options = options;
}

QString PBGameOptions::toString()
{
	int idx = staticMetaObject.indexOfEnumerator("EGameOptions");
	QMetaEnum enu = staticMetaObject.enumerator(idx);
	return enu.valueToKeys(_options);
}

PBGameOptions PBGameOptions::fromString(QString s)
{
	int idx = staticMetaObject.indexOfEnumerator("EGameOptions");
	QMetaEnum enu = staticMetaObject.enumerator(idx);
	PBGameOptions opts(enu.keysToValue(s.toLatin1()));
	return opts;
}

bool PBGameOptions::isTourney()
{
	return (_options & (SNG | MTT)) !=0;
}
