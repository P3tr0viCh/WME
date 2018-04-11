// ---------------------------------------------------------------------------

#ifndef WMETDatabaseOperationH
#define WMETDatabaseOperationH

#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>

#include "WMETConnectionInfo.h"

// ---------------------------------------------------------------------------
class TDatabaseOperation : public TObject {
private:
	TADOConnection *FConnection;

	TConnectionInfo *FConnectionInfo;

	bool FUseDatabase;

	String FErrorMessage;

	__fastcall TDatabaseOperation();

	void __fastcall SetUseDatabase(bool Value);

public:
	__fastcall TDatabaseOperation(TConnectionInfo *ConnectionInfo);
	__fastcall ~TDatabaseOperation();

	virtual void OperationStart() = 0;
	virtual void OperationEndOK() = 0;
	virtual void OperationEndFail() = 0;

	virtual void Operation() = 0;

	bool Execute();

__published:
	__property TADOConnection *Connection = {read = FConnection};

	__property TConnectionInfo *ConnectionInfo = {read = FConnectionInfo};

	__property bool UseDatabase = {read = FUseDatabase, write = SetUseDatabase};

	__property String ErrorMessage = {read = FErrorMessage};
};

// ---------------------------------------------------------------------------
#endif
