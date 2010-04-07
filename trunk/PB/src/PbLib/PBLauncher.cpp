#include "stdafx.h"
#include "pblauncher.h"
#include "pbapi.h"
#include "pbhook.h"

PBLauncher::PBLauncher(QObject *parent ) : QObject(parent)
{
	_processName = "FULLTILTPOKER.EXE";
	_dllPath = "PBFT.DLL";
	_dirName = ".";
	_timerId = -1;
	_maxCount=1;
}

void PBLauncher::setPath(QString path)
{
	_dirName = path;
}

void PBLauncher::setMaxCount(int mc)
{
	_maxCount = mc;
}

void PBLauncher::start()
{
	_timerId = startTimer(10000);
	timerEvent(0);
}

void PBLauncher::timerEvent(QTimerEvent *e)
{
	int count;
	ULONG pid = RtlGetProcessID(_processName.toAscii(), &count);

	if(count<_maxCount)
	{
		QString path = _dirName;
		path.append("\\");
		path.append(_processName);
		NTSTATUS res = RhCreateAndInject(const_cast<wchar_t*>(path.toStdWString().data()),
			NULL,CREATE_SUSPENDED,EASYHOOK_INJECT_DEFAULT,const_cast<wchar_t*>(_dllPath.toStdWString().data()),NULL,NULL,0,&pid);
		if(res)
			qLog(Info)<<"PBLauncher: failed to create injected process "<<_processName<<" directory "<<_dirName<<" dll "<<_dllPath<<":"<<
				QString::fromWCharArray(RtlGetLastErrorString());
		else
			qLog(Info)<<"created process "<<_processName<<", PID="<<pid;
	}
	
}
