// ---------------------------------------------------------------------------

#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsStr.h>

#include "WMEStrings.h"

#include "WMEAdd.h"

#include "WMETDBDrop.h"

#include "WMETDBCreate.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TDBCreate::TDBCreate(TConnectionInfo *ConnectionInfo)
	: TDatabaseOperation(ConnectionInfo) {
}

// ---------------------------------------------------------------------------
void TDBCreate::OperationEndOK() {
	WriteToLog(LoadStr(IDS_LOG_MYSQL_DB_CREATE_OK));
}

// ---------------------------------------------------------------------------
void TDBCreate::OperationEndFail() {
	WriteToLog(Format(IDS_LOG_MYSQL_DB_CREATE_FAIL, ErrorMessage));
}

// ---------------------------------------------------------------------------
void TDBCreate::Operation() {
	// Drop and Create DB
	UseDatabase = false;

	Connection->Open();
	Connection->BeginTrans();

	Connection->Execute(LoadStr(IDS_MYSQL_DATABASE_DROP));
	Connection->Execute(LoadStr(IDS_MYSQL_DATABASE_CREATE));

	Connection->CommitTrans();
	Connection->Close();

	// Create tables

	UseDatabase = true;

	Connection->Open();
	Connection->BeginTrans();

	Connection->Execute(LoadSQL(IDS_MYSQL_TBL_TRAINS_CREATE));
	Connection->Execute(LoadSQL(IDS_MYSQL_TBL_VANS_CREATE));

	Connection->CommitTrans();
	Connection->Close();
}

// ---------------------------------------------------------------------------
