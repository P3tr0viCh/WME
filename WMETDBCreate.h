// ---------------------------------------------------------------------------

#ifndef WMETDBCreateH
#define WMETDBCreateH

#include "WMETDatabaseOperation.h"

// ---------------------------------------------------------------------------
class TDBCreate : public TDatabaseOperation {
public:
	__fastcall TDBCreate(TConnectionInfo *ConnectionInfo);

	void OperationStart() {
	};
	void OperationEndOK();
	void OperationEndFail();

	void Operation();
};

// ---------------------------------------------------------------------------
#endif
