// ---------------------------------------------------------------------------

#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsStr.h>

#include "WMEStrings.h"

#include "WMETDBDrop.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TDBDrop::TDBDrop(TConnectionInfo *ConnectionInfo)
	: TDatabaseOperation(ConnectionInfo) {
}

// ---------------------------------------------------------------------------
void TDBDrop::OperationEndOK() {
	WriteToLog(LoadStr(IDS_LOG_MYSQL_DB_DROP_OK));
}

// ---------------------------------------------------------------------------
void TDBDrop::OperationEndFail() {
	WriteToLog(Format(IDS_LOG_MYSQL_DB_DROP_FAIL, ErrorMessage));
}

// ---------------------------------------------------------------------------
void TDBDrop::Operation() {
	UseDatabase = false;

	Connection->Open();

	Connection->Execute(LoadStr(IDS_MYSQL_DATABASE_DROP));

	Connection->Close();
}

// ---------------------------------------------------------------------------
