// ---------------------------------------------------------------------------

#ifndef WMEAddH
#define WMEAddH

#include <System.Classes.hpp>

#define sDefaultMySqlHost "localhost"
#define sDefaultMySqlPort "3306"
#define sDefaultMySqlUser "root"

String GetMySqlConnectionString(String Server, String Port, String Database,
	String User, String Password);
// ---------------------------------------------------------------------------
#endif
