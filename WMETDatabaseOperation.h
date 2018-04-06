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

	int FLogOperationStart;
	int FLogOperationEndOK;
	int FLogOperationEndFail;

	__fastcall TDatabaseOperation();

	void SetUseDatabase(bool Value);

public:
	__fastcall TDatabaseOperation(TConnectionInfo *ConnectionInfo);
	__fastcall ~TDatabaseOperation();

	virtual void Operation() = 0;

	bool Execute();

	__property TADOConnection *Connection = {read = FConnection};

	__property TConnectionInfo *ConnectionInfo = {read = FConnectionInfo};

	__property bool UseDatabase = {read = FUseDatabase, write = SetUseDatabase};

	__property String ErrorMessage = {read = FErrorMessage};

	__property int LogOperationStart = {
		read = FLogOperationStart, write = FLogOperationStart};
	__property int LogOperationEndOK = {
		read = FLogOperationEndOK, write = FLogOperationEndOK};
	__property int LogOperationEndFail = {
		read = FLogOperationEndFail, write = FLogOperationEndFail};
};

// ---------------------------------------------------------------------------
#endif
