#include <winsock2.h>
#define _WINSOCK2API_

#include <QtWidgets>
#include <QtWidgets/QApplication>
#include <QtPlugin>
#include <QXmlStreamReader>
#include <QtGui>
#include <QTextStream>
#include <QFile>


Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)

#include <Windows.h>
#include <io.h>
#include <dbghelp.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory>
#include <memory.h>
#include <tchar.h>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <shlobj.h>
#include <direct.h>
#include <vector>
#include "strsafe.h"
#include <map>
#include <stdarg.h>
#include "resource.h"
#include <iomanip>
#include <intrin.h>       
#include <iphlpapi.h>   
#include <mutex>
#include <WinInet.h>
#include <chrono>
#include <thread>
#include <tlhelp32.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "distorm.h"

#include <psapi.h>


using namespace std;
#define MAX_INSTRUCTIONS (500)
// Link the library into our project.
#pragma comment(lib, "distorm.lib")



#pragma comment(lib, "Dbghelp.lib")
#pragma comment(lib, "detours.lib")
#include "detours.h"

//using namespace std::chrono_literals;

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "Wininet")
#ifdef _DEBUG
#define DEBUG_WAS_DEFINED
#undef _DEBUG
#endif

#include "Python.h"

#include <boost/filesystem/path.hpp>
#include "boost/filesystem/operations.hpp"
#ifdef DEBUG_WAS_DEFINED
#define _DEBUG
#endif

#include<AsmOperations.h>
#include "LogWindow.h"
#include "Xor32.h"
#include "Misc.h"
#include "Timer.h"

#include "StringExtension.h"
#include "FileExtension.h"
#include "MemoryExtension.h"

#include "ProtectExtension.h"
#include "PatternScan.h"
#include "PatternScan2.h"
#include "PatternScanFast.h"




#include "MainCore.h"

