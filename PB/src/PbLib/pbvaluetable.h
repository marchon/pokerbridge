#pragma once

class PBValueTable : public QObject
{
	Q_OBJECT;
public:
	PBValueTable(int rows, int columns);
	
	QString column(int col);
	void setColumn(int col, QString value);
	int indexOfColumn(QString column);

	QString value(int row, int col);
	void  setValue(int row, int col, QString value);
	
	int rowCount();
	int columnCount();
	
protected:
	QVector<QString> _header;
	QVector<QString> _value;
};