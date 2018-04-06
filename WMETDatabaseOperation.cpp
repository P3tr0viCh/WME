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
	FLogOperationStart = -1;
	FLogOperationEndOK = -1;
	FLogOperationEndFail = -1;

	FConnection = new TADOConnection(NULL);

	FConnectionInfo = Connection;
}

// ---------------------------------------------------------------------------
__fastcall TDatabaseOperation::~TDatabaseOperation() {
	FConnection->Free();
}

// ---------------------------------------------------------------------------
void TDatabaseOperation::SetUseDatabase(bool Value) {
	FUseDatabase = Value;

	Connection->ConnectionString = ConnectionInfo->GetConnectionString(Value);
}

// ---------------------------------------------------------------------------
bool TDatabaseOperation::Execute() {
	bool Result = false;

	if (LogOperationStart > 0) {
		WriteToLog(LoadStr(LogOperationStart));
	}

	try {
		Operation();

		Result = true;
	}
	catch (Exception *E) {
		FErrorMessage = E->Message;
	}

	if (Result) {
		if (LogOperationEndOK > 0) {
			WriteToLog(LoadStr(LogOperationEndOK));
		}
	}
	else {
		if (IsEmpty(FErrorMessage)) {
			FErrorMessage = LoadStr(IDS_ERROR_UNKNOWN);
		}

		if (LogOperationEndFail > 0) {
			WriteToLog(Format(LogOperationEndFail, StringReplace(FErrorMessage,
				sLineBreak, " ", TReplaceFlags() << rfReplaceAll)));
		}
	}

	return Result;
}

// ---------------------------------------------------------------------------
