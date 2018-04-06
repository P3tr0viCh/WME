// ---------------------------------------------------------------------------

#ifndef WMETDBCreateH
#define WMETDBCreateH

#include "WMETDatabaseOperation.h"

// ---------------------------------------------------------------------------
class TDBCreate : public TDatabaseOperation {
public:
	__fastcall TDBCreate(TConnectionInfo *ConnectionInfo);

	void Operation();
};

// ---------------------------------------------------------------------------
#endif
