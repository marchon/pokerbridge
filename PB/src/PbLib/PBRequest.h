#pragma once


class PBRequestState
{
public:
	PBRequestState();

	bool sent(){ return _sent; }
	void setSent();
	bool answered(){ return _answered; }
	void setAnswered();
	void reset();
	
	bool timedOut();
private:
	QTime _sendTime;
	bool _sent;
	bool _answered;
	int _timeout;
};