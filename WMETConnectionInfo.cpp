// ---------------------------------------------------------------------------

#pragma hdrstop

#include <UtilsStr.h>

#include "WMEStrings.h"

#include "WMETConnectionInfo.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TConnectionInfo::TConnectionInfo() {
	SetDefault();
}

// ---------------------------------------------------------------------------
void TConnectionInfo::SetDefault() {
	FHost = "localhost";
	FPort = "3306";
	FDatabase = "wme";
	FUser = "root";
	FPassword = "";
}

// ---------------------------------------------------------------------------
bool __fastcall TConnectionInfo::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TConnectionInfo * Connection = (TConnectionInfo*) Obj;

	if (Host != Connection->Host || Port != Connection->Port ||
		Database != Connection->Database || User != Connection->User ||
		Password != Connection->Password)
		return false;

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TConnectionInfo::Assign(TConnectionInfo * Source) {
	Host = Source->Host;
	Port = Source->Port;
	Database = Source->Database;
	User = Source->User;
	Password = Source->Password;
}

// ---------------------------------------------------------------------------
String __fastcall TConnectionInfo::ToString() {
	String S;

	S = "TConnectionInfo{";
	S += "Host='" + Host + "'";
	S += ", Port='" + Port + "'";
	S += ", Database='" + Database + "'";
	S += ", User='" + User + "'";
	S += ", Password='" + String(IsEmpty(Password) ? "" : "*") + "'";
	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
String TConnectionInfo::GetConnectionString(bool WithDB) {
	return Format(IDS_MYSQL_CONNECTION,
		ARRAYOFCONST((FHost, FPort, WithDB ? FDatabase : String(""), User,
		FPassword)));
}
