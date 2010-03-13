#pragma once


class PBEvent : public QObject
{
	Q_OBJECT
public:
	QString eventType();
	PBEvent(QString eventType);
};

