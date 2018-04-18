// ---------------------------------------------------------------------------

#ifndef WMETDBLoadTrainsH
#define WMETDBLoadTrainsH

#include "WMETTrain.h"

#include "WMETDBTrainsFields.h"

#include "WMETDatabaseOperation.h"

// ---------------------------------------------------------------------------
class TDBLoadTrains : public TDatabaseOperation {
private:
	TTrainList *FTrainList;

	TDBTrainsFields *TrainsFields;

public:
	__fastcall TDBLoadTrains(TConnectionInfo *ConnectionInfo);
	__fastcall ~TDBLoadTrains();

	void OperationStart();
	void OperationEndOK();
	void OperationEndFail();

	void Operation();

	__property TTrainList *TrainList = {read = FTrainList};
};

// ---------------------------------------------------------------------------
#endif
