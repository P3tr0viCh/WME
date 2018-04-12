// ---------------------------------------------------------------------------

#ifndef WMETDBSaveTrainH
#define WMETDBSaveTrainH

#include "WMETTrain.h"

#include "WMETDBVansFields.h"
#include "WMETDBTrainsFields.h"

#include "WMETDatabaseOperation.h"

// ---------------------------------------------------------------------------
class TDBSaveTrain : public TDatabaseOperation {
private:
	TTrain *FTrain;

	TDBVansFields *VansFields;
	TDBTrainsFields *TrainsFields;

public:
	__fastcall TDBSaveTrain(TConnectionInfo *ConnectionInfo, TTrain *Train);
	__fastcall ~TDBSaveTrain();

	void OperationStart();
	void OperationEndOK();
	void OperationEndFail();

	void SetVansParam(TADOQuery * Query, TDBVansFieldName Name, int Index,
		Variant Value);
	void SetTrainsParam(TADOQuery *Query, TDBTrainsFieldName Name,
		Variant Value);

	void Operation();

	__property TTrain *Train = {read = FTrain};
};

// ---------------------------------------------------------------------------
#endif
