// ---------------------------------------------------------------------------

#ifndef WMETDBCheckH
#define WMETDBCheckH

#include "WMETDatabaseOperation.h"

// ---------------------------------------------------------------------------
class TDBCheck : public TDatabaseOperation {
public:
	__fastcall TDBCheck(TConnectionInfo *ConnectionInfo);

	void Operation();
};

// ---------------------------------------------------------------------------
#endif
