#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <psapi.h>
#include <shlwapi.h>

#include <stdio.h>
#include <iostream>

#define QWEAKPOINTER_ENABLE_ARROW
#include "QtCore\QtCore"
#include "QtGui\QtGui"
#include <QtSql\QtSql>
#include <QtScript\QtScript>
#include <QtXml\QtXml>
#include <QtNetwork\QtNetwork>

#include "EasyHook.h"

#include "pbglobal.h"
#include "pbdefs.h"

#include "qpblog.h"
#include "rmsg.h"