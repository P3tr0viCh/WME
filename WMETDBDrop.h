// ---------------------------------------------------------------------------

#ifndef WMETDBDropH
#define WMETDBDropH

#include "WMETDatabaseOperation.h"

// ---------------------------------------------------------------------------
class TDBDrop : public TDatabaseOperation {
public:
	__fastcall TDBDrop(TConnectionInfo *ConnectionInfo);

	void OperationStart() {
	};
	void OperationEndOK();
	void OperationEndFail();

	void Operation();
};

// ---------------------------------------------------------------------------
#endif
