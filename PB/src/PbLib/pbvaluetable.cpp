#include "stdafx.h"
#include "pbvaluetable.h"

PBValueTable::PBValueTable(int rows, int columns)
{
	_header.resize(columns);
	_value.resize(rows*columns);
}
	
QString PBValueTable::column(int col)
{
	return _header[col];
}

void PBValueTable::setColumn(int col, QString value)
{
	_header[col] = value;
}

QString PBValueTable::value(int row, int col)
{
	return _value[row*columnCount()+row];
}

void PBValueTable::setValue(int row, int col, QString value)
{
	_value[row*columnCount()+col] = value;
}
	
int PBValueTable::rowCount()
{
	return _value.size()/_header.size();
}

int PBValueTable::columnCount()
{
	return _header.size();
}
