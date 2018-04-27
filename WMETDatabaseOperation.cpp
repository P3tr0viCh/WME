// ---------------------------------------------------------------------------

#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsStr.h>

#include "WMEStrings.h"

#include "WMETDatabaseOperation.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TDatabaseOperation::TDatabaseOperation(TConnectionInfo *Connection) {
	FConnection = new TADOConnection(NULL);

	FConnectionInfo = Connection;
}

// ---------------------------------------------------------------------------
__fastcall TDatabaseOperation::~TDatabaseOperation() {
	FConnection->Free();
}

// ---------------------------------------------------------------------------
void __fastcall TDatabaseOperation::SetUseDatabase(bool Value) {
	FUseDatabase = Value;

	Connection->ConnectionString = ConnectionInfo->GetConnectionString(Value);
}

// ---------------------------------------------------------------------------
bool TDatabaseOperation::Execute() {
	bool Result = false;

	OperationStart();

	try {
		Operation();

		Result = true;
	}
	catch (Exception * E) {
		FErrorMessage = E->Message;
	}

	if (Result) {
		OperationEndOK();
	}
	else {
		if (IsEmpty(FErrorMessage)) {
			FErrorMessage = LoadStr(IDS_ERROR_UNKNOWN);
		}

		OperationEndFail();
	}

	return Result;
}

// ---------------------------------------------------------------------------
