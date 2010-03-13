#include "stdafx.h"
#include "ftbutton.h"

FTButton::FTButton(QAbstractButton *w, QObject *parent) : FTWidgetHook(w, parent)
{

}

QAbstractButton *FTButton::button()
{
	return qobject_cast<QAbstractButton*>(widget());
}

void FTButton::press()
{
	button()->click();
	int w = widget()->width();
	int h = widget()->height();
	int x = qrand()%(w*2/3)+ w/6;
	int y = qrand()%(h*2/3)+ h/6;
	//click(QPoint(x,y));
}

QString FTButton::text()
{
	return button()->text();
}

FTButton *FTButton::fromWidget(QWidget *w, FTWidgetHook *parent, const QString &text, const QString &clazz, const QString &name)
{
	FTWidgetHook *wh = parent->hookFor(w);
	if(0!=wh)
		return qobject_cast<FTButton*>(wh);

	QAbstractButton *btn = qobject_cast<QAbstractButton*>(w);
	if(0==btn)
		return 0;
	QString btnText=btn->text();
	if(!text.isEmpty() && btnText.indexOf(text)<0)
		return 0;
	if(!clazz.isEmpty() && QString(btn->metaObject()->className())!=clazz)
		return 0;
	QString oname = btn->objectName();
	if(!name.isEmpty() && oname!=name)
		return 0;
	FTButton *ftbtn = new FTButton(btn, parent);
	return ftbtn;
}

FTLabel::FTLabel(QLabel *w, QObject *parent):FTWidgetHook(w, parent)
{
}
QString FTLabel::text()
{

	return label()->text();
}

QLabel *FTLabel::label()
{
	return qobject_cast<QLabel*>(widget());
}

FTLabel *FTLabel::fromWidget(QWidget *w, FTWidgetHook *parent, const QString &text, const QString &clazz, const QString &name)
{
	FTWidgetHook *wh = parent->hookFor(w);
	if(0!=wh)
		return qobject_cast<FTLabel*>(wh);
	if(!clazz.isEmpty() && QString(w->metaObject()->className())!=clazz)
		return 0;
	QString oname = w->objectName();
	if(!name.isEmpty() && oname!=name)
		return 0;

	QLabel *lbl = qobject_cast<QLabel*>(w);
	if(0==lbl)
		return 0;
	QString lbltext=lbl->text();
	if(!text.isEmpty() && lbltext.indexOf(text)<0)
		return 0;
	
	FTLabel *ftlbl = new FTLabel(lbl, parent);
	return ftlbl;
}