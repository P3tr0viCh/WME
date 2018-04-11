// ---------------------------------------------------------------------------

#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsStr.h>

#include "WMEStrings.h"

#include "WMETDBCheck.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TDBCheck::TDBCheck(TConnectionInfo *ConnectionInfo)
	: TDatabaseOperation(ConnectionInfo) {
}

// ---------------------------------------------------------------------------
void TDBCheck::OperationStart() {
	WriteToLog(Format(IDS_LOG_MYSQL_CONNECT, ARRAYOFCONST((ConnectionInfo->User,
		ConnectionInfo->Host, ConnectionInfo->Port))));
}

// ---------------------------------------------------------------------------
void TDBCheck::OperationEndOK() {
	WriteToLog(Format(IDS_LOG_MYSQL_CONNECT_OK, MySQLVersion));
}

// ---------------------------------------------------------------------------
void TDBCheck::OperationEndFail() {
	WriteToLog(Format(IDS_LOG_MYSQL_CONNECT_FAIL, ErrorMessage));
}

// ---------------------------------------------------------------------------
void TDBCheck::Operation() {
	UseDatabase = false;

	Connection->Open();

	TADODataSet *DataSet = new TADODataSet(NULL);
	try {
		DataSet->Recordset = Connection->Execute(LoadStr(IDS_MYSQL_VERSION));

		FMySQLVersion = DataSet->Fields->Fields[0]->AsString;
	}
	__finally {
		DataSet->Free();
	}

	Connection->Close();
}

// ---------------------------------------------------------------------------
