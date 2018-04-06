// ---------------------------------------------------------------------------

#pragma hdrstop

#include "WMEStrings.h"

#include "WMETDBDrop.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TDBDrop::TDBDrop(TConnectionInfo *ConnectionInfo)
	: TDatabaseOperation(ConnectionInfo) {
	LogOperationEndOK = IDS_LOG_MYSQL_DB_DROP_OK;
	LogOperationEndFail = IDS_LOG_MYSQL_DB_DROP_FAIL;
}

// ---------------------------------------------------------------------------
void TDBDrop::Operation() {
	UseDatabase = false;

	Connection->Open();

	Connection->Execute(LoadStr(IDS_MYSQL_DATABASE_DROP));

    Connection->Close();
}

// ---------------------------------------------------------------------------
