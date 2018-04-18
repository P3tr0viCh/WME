// ---------------------------------------------------------------------------

#ifndef WMETDBLoadTrainH
#define WMETDBLoadTrainH

#include "WMETVan.h"

#include "WMETDBVansFields.h"

#include "WMETDatabaseOperation.h"

// ---------------------------------------------------------------------------
class TDBLoadTrain : public TDatabaseOperation {
private:
	int FTrainNum;

	TVanList *FVanList;

	TDBVansFields *VansFields;

public:
	__fastcall TDBLoadTrain(TConnectionInfo *ConnectionInfo, int TrainNum);
	__fastcall ~TDBLoadTrain();

	void OperationStart();
	void OperationEndOK();
	void OperationEndFail();

	void Operation();

	__property int TrainNum = {read = FTrainNum};

	__property TVanList *VanList = {read = FVanList};
};

// ---------------------------------------------------------------------------
#endif
