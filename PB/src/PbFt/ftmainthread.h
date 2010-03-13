#pragma once

class FTMainThread : public QThread
{
	Q_OBJECT;
public:
	virtual void run();

public:
	static HMODULE hInjectionLib;
	static QWaitCondition threadExited;
};