#pragma once

class PBGameOptions 
{
	Q_GADGET
	Q_ENUMS(EGameOptions)
public:
	enum EGameOptions
	{
		FullRing	=	 1,
		NoLimit		=	 2,
		Limit		=	 4,
		SNG			=	 8,
		MTT			=	16,
		Cash		=	32,
	};
	PBGameOptions(int options = 0);
	QString toString();
	static PBGameOptions fromString(QString s);

	bool isTourney();
private:
	int _options;
};