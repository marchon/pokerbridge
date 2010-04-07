#include "stdafx.h"
#include "pbserver.h"


int main(int argc, char*argv[])
{
	QPBLog::install();
	QPBLog::logToFile("pbserver.log");
	//PBLib_init();

	qLog(Debug)<<"pblaunch";

	QCoreApplication app(argc, argv);

	PBServer *s = new PBServer(&app);
	

	int res = app.exec();
	QPBLog::uninstall();
	qLog(Debug) << "exiting";
}

