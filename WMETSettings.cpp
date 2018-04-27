// ---------------------------------------------------------------------------

#pragma hdrstop

#include <System.IniFiles.hpp>

#include <UtilsLog.h>
#include <UtilsStr.h>
#include <UtilsFiles.h>
#include <UtilsFileIni.h>

#include "WMEStrings.h"

#include "WMETSettings.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TSettings::TSettings() {
	FConfigDir = GetConfigDir();

	FColorReadOnly = TColor(0x00E8E8E8);

	FConnection = new TConnectionInfo();
	FUserList = new TObjList<TUser>();

	FVanTypeList = new TVanTypeList();

	FCargoTypeList = new TVanCatalogList();
	FDepartStationList = new TVanCatalogList();
	FPurposeStationList = new TVanCatalogList();
	FInvoiceRecipientList = new TVanCatalogList();
	FInvoiceSupplierList = new TVanCatalogList();
}

// ---------------------------------------------------------------------------
__fastcall TSettings::~TSettings() {
	FInvoiceSupplierList->Free();
	FInvoiceRecipientList->Free();
	FPurposeStationList->Free();
	FDepartStationList->Free();
	FCargoTypeList->Free();

	FVanTypeList->Free();

	FUserList->Free();
	FConnection->Free();
}

// ---------------------------------------------------------------------------
bool __fastcall TSettings::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TSettings * Settings = (TSettings*) Obj;

	if (!Settings->Connection->Equals(Connection))
		return false;

	if (!Settings->UserList->Equals(UserList))
		return false;

	if (!Settings->VanTypeList->Equals(VanTypeList))
		return false;

	if (!Settings->CargoTypeList->Equals(CargoTypeList))
		return false;
	if (!Settings->DepartStationList->Equals(DepartStationList))
		return false;
	if (!Settings->PurposeStationList->Equals(PurposeStationList))
		return false;
	if (!Settings->InvoiceRecipientList->Equals(InvoiceRecipientList))
		return false;
	if (!Settings->InvoiceSupplierList->Equals(InvoiceSupplierList))
		return false;

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TSettings::Assign(TSettings * Source) {
	FConnection->Assign(Source->Connection);
	FUserList->Assign(Source->UserList);
	FVanTypeList->Assign(Source->VanTypeList);
	FCargoTypeList->Assign(Source->CargoTypeList);
	FDepartStationList->Assign(Source->DepartStationList);
	FPurposeStationList->Assign(Source->PurposeStationList);
	FInvoiceRecipientList->Assign(Source->InvoiceRecipientList);
	FInvoiceSupplierList->Assign(Source->InvoiceSupplierList);
}

// ---------------------------------------------------------------------------
String __fastcall TSettings::ToString() {
	String S;

	S = "TSettings{";
	S += "Connection='" + Connection->ToString() + "'";
	S += "UserList->Count='" + IntToStr(UserList->Count) + "'";
	S += "VanTypeList->Count='" + IntToStr(VanTypeList->Count) + "'";
	S += "CargoTypeList->Count='" + IntToStr(CargoTypeList->Count) + "'";
	S += "DepartStationList->Count='" +
		IntToStr(DepartStationList->Count) + "'";
	S += "PurposeStationList->Count='" +
		IntToStr(PurposeStationList->Count) + "'";
	S += "InvoiceRecipientList->Count='" +
		IntToStr(InvoiceRecipientList->Count) + "'";
	S += "InvoiceSupplierList->Count='" +
		IntToStr(InvoiceSupplierList->Count) + "'";
	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
int __fastcall UserListSort(void* Item1, void* Item2) {
	TUser * User1 = (TUser*)Item1;
	TUser * User2 = (TUser*)Item2;

	if (User1->IsAdmin && !User2->IsAdmin) {
		return -1;
	}

	if (!User1->IsAdmin && User2->IsAdmin) {
		return 1;
	}

	return AnsiCompareStr(User1->Name, User2->Name);
}

// ---------------------------------------------------------------------------
int __fastcall VanTypeListSort(void* Item1, void* Item2) {
	TVanType * VanType1 = (TVanType*)Item1;
	TVanType * VanType2 = (TVanType*)Item2;

	return AnsiCompareStr(VanType1->Name, VanType2->Name);
}

// ---------------------------------------------------------------------------
int __fastcall VanCatalogListSort(void* Item1, void* Item2) {
	TVanCatalog * VanCatalog1 = (TVanCatalog*)Item1;
	TVanCatalog * VanCatalog2 = (TVanCatalog*)Item2;

	return AnsiCompareStr(VanCatalog1->Name, VanCatalog2->Name);
}

// ---------------------------------------------------------------------------
String TSettings::GetConfigDir() {
	return IncludeTrailingBackslash(FileInAppDir(CFG_DIR_NAME));
}

// ---------------------------------------------------------------------------
bool TSettings::CheckConfigDir() {
	if (!DirectoryExists(FConfigDir)) {
		if (!CreateDir(FConfigDir)) {
			WriteToLog(Format(IDS_LOG_CREATE_DIR_FAIL, FConfigDir));
			return false;
		}
	}

	return true;
}

// ---------------------------------------------------------------------------
String TSettings::GetConfigFileName(String ConfigName) {
	return FConfigDir + ConfigName + CFG_EXT;
}

// ---------------------------------------------------------------------------
String TSettings::EncryptPass(String S) {
	return S;
}

// ---------------------------------------------------------------------------
String TSettings::DecryptPass(String S) {
	return S;
}

// ---------------------------------------------------------------------------
void TSettings::DeleteConfigFile(String ConfigFileName) {
	if (FileExists(ConfigFileName) && !DeleteFile(ConfigFileName)) {
		throw Exception(IDS_LOG_DELETE_FILE_FAIL);
	}
}

// ---------------------------------------------------------------------------
void TSettings::LoadDatabase(String ConfigFileName) {
	TIniFile * IniFile = new TIniFile(ConfigFileName);

	String Section = "Connection";

	try {
		Connection->Host = IniFile->ReadString(Section, "host",
		Connection->Host);
		Connection->Port = IniFile->ReadString(Section, "port",
			Connection->Port);
		Connection->User = IniFile->ReadString(Section, "user",
			Connection->User);
		Connection->Password = IniFile->ReadString(Section, "pass",
			EncryptPass(Connection->Password));
	}
	__finally {
		delete IniFile;
	}
}

// ---------------------------------------------------------------------------
void TSettings::LoadUsers(String ConfigFileName) {
	TIniFile * IniFile = new TIniFile(ConfigFileName);

	TUser * User;

	String Section;

	try {
		int Count = IniFile->ReadInteger("Users", "Count", 0);

		for (int i = 0; i < Count; i++) {
			Section = "User_" + IntToStr(i);

			User = new TUser();

			User->Name = IniFile->ReadString(Section, "Name", "");
			User->Pass = EncryptPass(IniFile->ReadString(Section, "Pass", ""));
			User->TabNum = IniFile->ReadString(Section, "TabNum", "");
			User->ShiftNum = IniFile->ReadString(Section, "ShiftNum", "");

			User->IsAdmin = IniFile->ReadBool(Section, "IsAdmin", false);

			UserList->Add(User);
		}

		if (UserList->IsEmpty()) {
			User = new TUser();

			User->Name = LoadStr(IDS_TXT_ADMIN_DEFAULT_NAME);
			User->IsAdmin = true;

			UserList->Add(User);
		}
	}
	__finally {
		delete IniFile;
	}
}

// ---------------------------------------------------------------------------
void TSettings::LoadVanTypes(String ConfigFileName) {
	TIniFile * IniFile = new TIniFile(ConfigFileName);

	TVanType * VanType;

	String Section;

	try {
		int Count = IniFile->ReadInteger("VanTypes", "Count", 0);

		for (int i = 0; i < Count; i++) {
			Section = "VanType_" + IntToStr(i);

			VanType = new TVanType();

			VanType->Code = IniFile->ReadInteger(Section, "Code",
				VanType->Code);
			VanType->Name = IniFile->ReadString(Section, "Name", VanType->Name);
			VanType->AxisCount = IniFile->ReadInteger(Section, "AxisCount",
				VanType->AxisCount);

			VanTypeList->Add(VanType);
		}
	}
	__finally {
		delete IniFile;
	}
}

// ---------------------------------------------------------------------------
void TSettings::LoadVanCatalog(String ConfigFileName, String Name,
	TVanCatalogList * VanCatalogList) {
	TIniFile * IniFile = new TIniFile(ConfigFileName);

	TVanCatalog * VanCatalog;

	String Section;

	try {
		int Count = IniFile->ReadInteger(Name + "s", "Count", 0);

		for (int i = 0; i < Count; i++) {
			Section = Name + "_" + IntToStr(i);

			VanCatalog = new TVanCatalog();

			VanCatalog->Code = IniFile->ReadInteger(Section, "Code",
				VanCatalog->Code);
			VanCatalog->Name = IniFile->ReadString(Section, "Name",
				VanCatalog->Name);

			VanCatalogList->Add(VanCatalog);
		}
	}
	__finally {
		delete IniFile;
	}
}

// ---------------------------------------------------------------------------
void TSettings::LoadCargoTypes(String ConfigFileName) {
	LoadVanCatalog(ConfigFileName, "CargoType", CargoTypeList);
}

// ---------------------------------------------------------------------------
void TSettings::LoadDepartStations(String ConfigFileName) {
	LoadVanCatalog(ConfigFileName, "DepartStation", DepartStationList);
}

// ---------------------------------------------------------------------------
void TSettings::LoadPurposeStations(String ConfigFileName) {
	LoadVanCatalog(ConfigFileName, "PurposeStation", PurposeStationList);
}

// ---------------------------------------------------------------------------
void TSettings::LoadInvoiceRecipients(String ConfigFileName) {
	LoadVanCatalog(ConfigFileName, "InvoiceRecipient", InvoiceRecipientList);
}

// ---------------------------------------------------------------------------
void TSettings::LoadInvoiceSuppliers(String ConfigFileName) {
	LoadVanCatalog(ConfigFileName, "InvoiceSupplier", InvoiceSupplierList);
}

// ---------------------------------------------------------------------------
bool TSettings::Load() {
	if (!CheckConfigDir()) {
		return false;
	}

	String ConfigFileName;

	try {
		ConfigFileName = GetConfigFileName("Database");
		LoadDatabase(ConfigFileName);

		ConfigFileName = GetConfigFileName("Users");
		LoadUsers(ConfigFileName);

		ConfigFileName = GetConfigFileName("VanTypes");
		LoadVanTypes(ConfigFileName);

		ConfigFileName = GetConfigFileName("CargoTypes");
		LoadCargoTypes(ConfigFileName);
		ConfigFileName = GetConfigFileName("DepartStations");
		LoadDepartStations(ConfigFileName);
		ConfigFileName = GetConfigFileName("PurposeStations");
		LoadPurposeStations(ConfigFileName);
		ConfigFileName = GetConfigFileName("InvoiceRecipients");
		LoadInvoiceRecipients(ConfigFileName);
		ConfigFileName = GetConfigFileName("InvoiceSuppliers");
		LoadInvoiceSuppliers(ConfigFileName);
	}
	catch (Exception * E) {
		WriteToLog(Format(IDS_LOG_READ_FILE_FAIL,
			ARRAYOFCONST((ConfigFileName, E->Message))));

		return false;
	}

	return true;
}

// ---------------------------------------------------------------------------
void TSettings::SaveDatabase(String ConfigFileName) {
	TIniFile * IniFile = new TIniFile(ConfigFileName);
	try {
		String Section = "Connection";

		IniFile->WriteString(Section, "host", Connection->Host);
		IniFile->WriteString(Section, "port", Connection->Port);
		IniFile->WriteString(Section, "user", Connection->User);
		IniFile->WriteString(Section, "pass",
			DecryptPass(Connection->Password));
	}
	__finally {
		delete IniFile;
	}
}

// ---------------------------------------------------------------------------
void TSettings::SaveUsers(String ConfigFileName) {
	DeleteConfigFile(ConfigFileName);

	UserList->Sort(UserListSort);

	String Section;

	TIniFile * IniFile = new TIniFile(ConfigFileName);
	try {
		IniFile->WriteInteger("Users", "Count", UserList->Count);

		for (int i = 0; i < UserList->Count; i++) {
			Section = "User_" + IntToStr(i);

			IniFile->WriteString(Section, "Name", UserList->Items[i]->Name);
			IniFile->WriteString(Section, "Pass",
				EncryptPass(UserList->Items[i]->Pass));
			IniFile->WriteString(Section, "TabNum", UserList->Items[i]->TabNum);
			IniFile->WriteString(Section, "ShiftNum",
				UserList->Items[i]->ShiftNum);

			IniFile->WriteBool(Section, "IsAdmin", UserList->Items[i]->IsAdmin);
		}
	}
	__finally {
		delete IniFile;
	}
}

// ---------------------------------------------------------------------------
void TSettings::SaveVanTypes(String ConfigFileName) {
	DeleteConfigFile(ConfigFileName);

	VanTypeList->Sort(VanTypeListSort);

	String Section;

	TIniFile * IniFile = new TIniFile(ConfigFileName);
	try {
		IniFile->WriteInteger("VanTypes", "Count", VanTypeList->Count);

		for (int i = 0; i < VanTypeList->Count; i++) {
			Section = "VanType_" + IntToStr(i);

			IniFile->WriteInteger(Section, "Code", VanTypeList->Items[i]->Code);
			IniFile->WriteString(Section, "Name", VanTypeList->Items[i]->Name);
			IniFile->WriteInteger(Section, "AxisCount",
				VanTypeList->Items[i]->AxisCount);
		}
	}
	__finally {
		delete IniFile;
	}
}

// ---------------------------------------------------------------------------
void TSettings::SaveVanCatalog(String ConfigFileName, String Name,
	TVanCatalogList * VanCatalogList) {
	DeleteConfigFile(ConfigFileName);

	VanCatalogList->Sort(VanCatalogListSort);

	String Section;

	TIniFile * IniFile = new TIniFile(ConfigFileName);
	try {
		IniFile->WriteInteger(Name + "s", "Count", VanCatalogList->Count);

		for (int i = 0; i < VanCatalogList->Count; i++) {
			Section = Name + "_" + IntToStr(i);

			IniFile->WriteInteger(Section, "Code",
				VanCatalogList->Items[i]->Code);
			IniFile->WriteString(Section, "Name",
				VanCatalogList->Items[i]->Name);
		}
	}
	__finally {
		delete IniFile;
	}
}

// ---------------------------------------------------------------------------
void TSettings::SaveCargoTypes(String ConfigFileName) {
	SaveVanCatalog(ConfigFileName, "CargoType", CargoTypeList);
}

// ---------------------------------------------------------------------------
void TSettings::SaveDepartStations(String ConfigFileName) {
	SaveVanCatalog(ConfigFileName, "DepartStation", DepartStationList);
}

// ---------------------------------------------------------------------------
void TSettings::SavePurposeStations(String ConfigFileName) {
	SaveVanCatalog(ConfigFileName, "PurposeStation", PurposeStationList);
}

// ---------------------------------------------------------------------------
void TSettings::SaveInvoiceRecipients(String ConfigFileName) {
	SaveVanCatalog(ConfigFileName, "InvoiceRecipient", InvoiceRecipientList);
}

// ---------------------------------------------------------------------------
void TSettings::SaveInvoiceSuppliers(String ConfigFileName) {
	SaveVanCatalog(ConfigFileName, "InvoiceSupplier", InvoiceSupplierList);
}

// ---------------------------------------------------------------------------
bool TSettings::Save() {
	if (!CheckConfigDir()) {
		return false;
	}

	TIniFile* IniFile;

	String ConfigFileName;

	String Section;

	try {
		ConfigFileName = GetConfigFileName("Database");
		SaveDatabase(ConfigFileName);

		ConfigFileName = GetConfigFileName("Users");
		SaveUsers(ConfigFileName);

		ConfigFileName = GetConfigFileName("VanTypes");
		SaveVanTypes(ConfigFileName);

		ConfigFileName = GetConfigFileName("CargoTypes");
		SaveCargoTypes(ConfigFileName);
		ConfigFileName = GetConfigFileName("DepartStations");
		SaveDepartStations(ConfigFileName);
		ConfigFileName = GetConfigFileName("PurposeStations");
		SavePurposeStations(ConfigFileName);
		ConfigFileName = GetConfigFileName("InvoiceRecipients");
		SaveInvoiceRecipients(ConfigFileName);
		ConfigFileName = GetConfigFileName("InvoiceSuppliers");
		SaveInvoiceSuppliers(ConfigFileName);
	}
	catch (Exception * E) {
		WriteToLog(Format(IDS_LOG_WRITE_FILE_FAIL,
			ARRAYOFCONST((ConfigFileName, E->Message))));

		return false;
	}

	return true;
}
