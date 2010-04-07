#include "stdafx.h"
#include "pbrequest.h"

PBRequestState::PBRequestState()
{
	_sent = false;
	_answered = false;
}

void PBRequestState::setSent()
{
	_sent = true;
	_sendTime = QTime::currentTime();
}

void PBRequestState::setAnswered()
{
	_answered = true;
}

void PBRequestState::reset()
{
	_sent = false;
	_answered = false;
}

bool PBRequestState::timedOut()
{
	return(_sent && !_answered && _sendTime.elapsed()>3000);
}