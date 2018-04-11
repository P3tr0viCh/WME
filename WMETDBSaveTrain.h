// ---------------------------------------------------------------------------

#ifndef WMETDBSaveTrainH
#define WMETDBSaveTrainH

#include "WMETVan.h"

#include "WMETDatabaseOperation.h"

// ---------------------------------------------------------------------------
class TDBSaveTrain : public TDatabaseOperation {
private:
	TVanList *FVanList;

public:
	__fastcall TDBSaveTrain(TConnectionInfo *ConnectionInfo,
		TVanList *VanList);

	void OperationStart();
	void OperationEndOK();
	void OperationEndFail();

	void Operation();

	__property TVanList *VanList = {read = FVanList};
};

// ---------------------------------------------------------------------------
#endif
