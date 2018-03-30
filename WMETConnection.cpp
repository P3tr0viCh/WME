// ---------------------------------------------------------------------------

#pragma hdrstop

#include <UtilsStr.h>

#include "WMEStrings.h"

#include "WMETConnection.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TConnection::TConnection() {
	SetDefault();
}

// ---------------------------------------------------------------------------
void TConnection::SetDefault() {
	FHost = "localhost";
	FPort = "3306";
	FDatabase = "wme";
	FUser = "root";
	FPassword = "";
}

// ---------------------------------------------------------------------------
bool __fastcall TConnection::Equals(TObject* Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TConnection *Connection = (TConnection*) Obj;

	if (Host != Connection->Host || Port != Connection->Port ||
		Database != Connection->Database || User != Connection->User ||
		Password != Connection->Password)
		return false;

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TConnection::Assign(TConnection* Source) {
	Host = Source->Host;
	Port = Source->Port;
	Database = Source->Database;
	User = Source->User;
	Password = Source->Password;
}

// ---------------------------------------------------------------------------
String __fastcall TConnection::ToString() {
	String S;

	S = "TConnection{";
	S += "FHost='" + FHost + "'";
	S += ", FPort='" + FPort + "'";
	S += ", FDatabase='" + FDatabase + "'";
	S += ", FUser='" + FUser + "'";
	S += ", FPassword='" + FPassword + "'";
	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
String TConnection::GetConnectionString(bool WithDB) {
	return Format(IDS_MYSQL_CONNECTION,
		ARRAYOFCONST((FHost, FPort, WithDB ? FDatabase : String(""), FUser,
		FPassword)));
}
