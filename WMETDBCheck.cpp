// ---------------------------------------------------------------------------

#pragma hdrstop

#include "WMEStrings.h"

#include "WMETDBCheck.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TDBCheck::TDBCheck(TConnectionInfo *ConnectionInfo)
	: TDatabaseOperation(ConnectionInfo) {
	LogOperationEndOK = IDS_LOG_MYSQL_CONNECT_OK;
	LogOperationEndFail = IDS_LOG_MYSQL_CONNECT_FAIL;
}

// ---------------------------------------------------------------------------
void TDBCheck::Operation() {
// TODO
}

// ---------------------------------------------------------------------------
