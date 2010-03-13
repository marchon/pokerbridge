#ifndef FTBUTTON_H
#define FTBUTTON_H

#pragma once
#include "ftwidgethook.h"
class FTButton : public FTWidgetHook
{
	Q_OBJECT
public:
	FTButton(QAbstractButton *w, QObject *parent = 0);
	QString text();

	QAbstractButton *button();
	static FTButton *fromWidget(QWidget *w, FTWidgetHook *parent, const QString &text = "", const QString &clazz = "", const QString &name = "");
public:
	void press();
};

class FTLabel: public FTWidgetHook
{
	Q_OBJECT
public:
	FTLabel(QLabel *w, QObject *parent=0);
	QString text();
	QLabel *label();
	static FTLabel *fromWidget(QWidget *w, FTWidgetHook *parent, const QString &text = "", const QString &clazz = "", const QString &name = "");
};


#endif