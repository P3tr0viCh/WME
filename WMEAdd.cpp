// ---------------------------------------------------------------------------

#pragma hdrstop

#include <System.SysUtils.hpp>

#include <UtilsStr.h>

#include "WMEStrings.h"

#include "WMEAdd.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
String GetMySqlConnectionString(String Server, String Port, String Database,
	String User, String Password) {
	return Format(IDS_MYSQL_CONNECTION,
		ARRAYOFCONST((Server, Port, Database, User, Password)));
}
// ---------------------------------------------------------------------------
