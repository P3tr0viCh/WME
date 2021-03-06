// ---------------------------------------------------------------------------

#ifndef WMETDBCheckH
#define WMETDBCheckH

#include "WMETDatabaseOperation.h"

// ---------------------------------------------------------------------------
class TDBCheck : public TDatabaseOperation {
private:
	String FMySQLVersion;

public:
	__fastcall TDBCheck(TConnectionInfo *ConnectionInfo);

	void OperationStart();
	void OperationEndOK();
	void OperationEndFail();

	void Operation();

	__property String MySQLVersion = {read = FMySQLVersion};
};

// ---------------------------------------------------------------------------
#endif
