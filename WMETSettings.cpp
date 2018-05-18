// ---------------------------------------------------------------------------

#pragma hdrstop

#include <System.IniFiles.hpp>

#include <UtilsLog.h>
#include <UtilsStr.h>
#include <UtilsFiles.h>
#include <UtilsFileIni.h>
#include <UtilsCryptoPP.h>

#include "WMEEncKey.h"

#include "WMEStrings.h"
#include "WMEStringsSettings.h"

#include "WMETSettings.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TSettings::TSettings() {
	FConfigDir = GetConfigDir();

	FColorReadOnly = TColor(0x00E8E8E8);

	FUseServer = false;

	FLocalConnection = new TConnectionInfo();
	FServerConnection = new TConnectionInfo();

	FUserList = new TUserList();

	FVanTypeList = new TVanTypeList();

	FCargoTypeList = new TVanCatalogList();
	FDepartStationList = new TVanCatalogList();
	FPurposeStationList = new TVanCatalogList();
	FInvoiceRecipientList = new TVanCatalogList();
	FInvoiceSupplierList = new TVanCatalogList();

	FLoadTrainCount = 5;
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

	FServerConnection->Free();
	FLocalConnection->Free();
}

// ---------------------------------------------------------------------------
bool __fastcall TSettings::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TSettings * Settings = (TSettings*) Obj;

	if (Settings->LoadTrainCount != LoadTrainCount)
		return false;

	if (Settings->UseServer != UseServer)
		return false;

	if (!Settings->LocalConnection->Equals(LocalConnection))
		return false;
	if (!Settings->ServerConnection->Equals(ServerConnection))
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
	FLocalConnection->Assign(Source->LocalConnection);
	FServerConnection->Assign(Source->ServerConnection);

	FUseServer = Source->UseServer;

	FUserList->Assign(Source->UserList);

	FVanTypeList->Assign(Source->VanTypeList);

	FCargoTypeList->Assign(Source->CargoTypeList);
	FDepartStationList->Assign(Source->DepartStationList);
	FPurposeStationList->Assign(Source->PurposeStationList);
	FInvoiceRecipientList->Assign(Source->InvoiceRecipientList);
	FInvoiceSupplierList->Assign(Source->InvoiceSupplierList);

	FLoadTrainCount = Source->LoadTrainCount;
}

// ---------------------------------------------------------------------------
String __fastcall TSettings::ToString() {
	String S;

	S = "TSettings{";
	S += "LocalConnection='" + LocalConnection->ToString() + "'";
	S += ",";
	S += "ServerConnection='" + ServerConnection->ToString() + "'";
	S += ",";
	S += "UseServer='" + BoolToStr(UseServer) + "'";
	S += ",";
	S += "UserList->Count='" + IntToStr(UserList->Count) + "'";
	S += ",";
	S += "VanTypeList->Count='" + IntToStr(VanTypeList->Count) + "'";
	S += ",";
	S += "CargoTypeList->Count='" + IntToStr(CargoTypeList->Count) + "'";
	S += ",";
	S += "DepartStationList->Count='" +
		IntToStr(DepartStationList->Count) + "'";
	S += ",";
	S += "PurposeStationList->Count='" +
		IntToStr(PurposeStationList->Count) + "'";
	S += ",";
	S += "InvoiceRecipientList->Count='" +
		IntToStr(InvoiceRecipientList->Count) + "'";
	S += ",";
	S += "InvoiceSupplierList->Count='" +
		IntToStr(InvoiceSupplierList->Count) + "'";
	S += ",";
	S += "LoadTrainCount='" + IntToStr(LoadTrainCount) + "'";
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
String TSettings::GetConfigFileName(NativeUInt ConfigName) {
	return FConfigDir + LoadStr(ConfigName) + CFG_EXT;
}

// ---------------------------------------------------------------------------
String TSettings::CRC(String Text) {
	try {
		return HashSHA256(Text);
	}
	catch (...) {
		return "";
	}
}

// ---------------------------------------------------------------------------
String TSettings::Encrypt(String Text) {
	if (IsEmpty(Text)) {
		return "";
	}

	try {
		return EncryptAES(Text, ENC_KEY);
	}
	catch (...) {
		return "";
	}
}

// ---------------------------------------------------------------------------
String TSettings::Decrypt(String Text) {
	if (IsEmpty(Text)) {
		return "";
	}

	try {
		return DecryptAES(Text, ENC_KEY);
	}
	catch (...) {
		return "";
	}
}

// ---------------------------------------------------------------------------
String TSettings::GetUsersCRC() {
	String Result;

	for (int i = 0; i < UserList->Count; i++) {
		Result = Result + UserList->Items[i]->Name;
	}

	return CRC(Result);
}

// ---------------------------------------------------------------------------
void TSettings::DeleteConfigFile(String ConfigFileName) {
	if (FileExists(ConfigFileName) && !DeleteFile(ConfigFileName)) {
		throw Exception(IDS_LOG_DELETE_FILE_FAIL);
	}
}

// ---------------------------------------------------------------------------
bool TSettings::LoadUsers(String ConfigFileName) {
	if (!FileExists(ConfigFileName)) {
		return false;
	}

	TIniFile * IniFile = new TIniFile(ConfigFileName);

	TUser * User;

	String Section;

	try {
		int Count = IniFile->ReadInteger("Users", "Count", 0);

		for (int i = 0; i < Count; i++) {
			Section = "User_" + IntToStr(i);

			User = new TUser();

			User->Name = IniFile->ReadString(Section, "Name", "");
			User->Pass = Decrypt(IniFile->ReadString(Section, "Pass", ""));
			User->TabNum = IniFile->ReadString(Section, "TabNum", "");
			User->ShiftNum = IniFile->ReadString(Section, "ShiftNum", "");

			User->IsAdmin = IniFile->ReadBool(Section, "IsAdmin", false);

			UserList->Add(User);
		}

		if (UserList->IsEmpty()) {
			return false;
		}

		String CRC = IniFile->ReadString(LoadStr(IDS_SETTINGS_CRC_SECTION),
			LoadStr(IDS_SETTINGS_CRC_IDENT), "");

		if (IsEmpty(CRC)) {
			throw new EEncodingError(IDS_LOG_CRC_EMPTY);
		}

		CRC = Decrypt(CRC);

		String UsersCRC = GetUsersCRC();

		if (!SameStr(CRC, UsersCRC)) {
			throw new EEncodingError(IDS_LOG_CRC_WRONG);
		}
	}
	__finally {
		delete IniFile;
	}

	return true;
}

// ---------------------------------------------------------------------------
void TSettings::LoadSettings(String ConfigFileName) {
	TIniFile * IniFile = new TIniFile(ConfigFileName);

	String Section;

	try {
		Section = "Main";
		UseServer = IniFile->ReadBool(Section, "UseServer", UseServer);
		LoadTrainCount = IniFile->ReadInteger(Section, "LoadTrainCount",
			LoadTrainCount);
	}
	__finally {
		delete IniFile;
	}
}

// ---------------------------------------------------------------------------
void TSettings::LoadDatabases(String ConfigFileName) {
	TIniFile * IniFile = new TIniFile(ConfigFileName);

	String Section;

	try {
		Section = "Local";
		LocalConnection->Host = IniFile->ReadString(Section, "host",
			LocalConnection->Host);
		LocalConnection->Port = IniFile->ReadString(Section, "port",
			LocalConnection->Port);
		LocalConnection->User = IniFile->ReadString(Section, "user",
			LocalConnection->User);
		LocalConnection->Password =
			Decrypt(IniFile->ReadString(Section, "pass", ""));

		Section = "Server";
		ServerConnection->Host = IniFile->ReadString(Section, "host",
			ServerConnection->Host);
		ServerConnection->Port = IniFile->ReadString(Section, "port",
			ServerConnection->Port);
		ServerConnection->User = IniFile->ReadString(Section, "user",
			ServerConnection->User);
		ServerConnection->Password =
			Decrypt(IniFile->ReadString(Section, "pass", ""));
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
		ConfigFileName = GetConfigFileName(IDS_SETTINGS_CONFIG_USERS);
		if (!LoadUsers(ConfigFileName)) {
			TUser * User = new TUser();

			User->Name = LoadStr(IDS_TXT_ADMIN_DEFAULT_NAME);
			User->IsAdmin = true;

			UserList->Add(User);

			WriteToLog(IDS_LOG_EMPTY_USERLIST);

			return true;
		}

		ConfigFileName = GetConfigFileName(IDS_SETTINGS_CONFIG_SETTINGS);
		LoadSettings(ConfigFileName);

		ConfigFileName = GetConfigFileName(IDS_SETTINGS_CONFIG_DATABASES);
		LoadDatabases(ConfigFileName);

		ConfigFileName = GetConfigFileName(IDS_SETTINGS_CONFIG_VANTYPES);
		LoadVanTypes(ConfigFileName);

		ConfigFileName = GetConfigFileName(IDS_SETTINGS_CONFIG_CARGOTYPES);
		LoadCargoTypes(ConfigFileName);
		ConfigFileName = GetConfigFileName(IDS_SETTINGS_CONFIG_DEPART_STATIONS);
		LoadDepartStations(ConfigFileName);
		ConfigFileName =
			GetConfigFileName(IDS_SETTINGS_CONFIG_PURPOSE_STATIONS);
		LoadPurposeStations(ConfigFileName);
		ConfigFileName =
			GetConfigFileName(IDS_SETTINGS_CONFIG_INVOICE_SUPPLIERS);
		LoadInvoiceRecipients(ConfigFileName);
		ConfigFileName =
			GetConfigFileName(IDS_SETTINGS_CONFIG_INVOICE_RECIPIENTS);
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
void TSettings::SaveUsers(String ConfigFileName) {
	DeleteConfigFile(ConfigFileName);

	UserList->Sort(UserListSort);

	String Section;

	TFileIni * IniFile = new TFileIni(ConfigFileName);
	try {
		IniFile->WriteString(LoadStr(IDS_SETTINGS_CRC_SECTION),
			LoadStr(IDS_SETTINGS_CRC_IDENT), Encrypt(GetUsersCRC()));

		IniFile->WriteInteger("Users", "Count", UserList->Count);

		for (int i = 0; i < UserList->Count; i++) {
			Section = "User_" + IntToStr(i);

			IniFile->WriteString(Section, "Name", UserList->Items[i]->Name);
			IniFile->WriteString(Section, "Pass",
				Encrypt(UserList->Items[i]->Pass));
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
void TSettings::SaveSettings(String ConfigFileName) {
	TIniFile * IniFile = new TIniFile(ConfigFileName);

	String Section;

	try {
		Section = "Main";
		IniFile->WriteBool(Section, "UseServer", UseServer);
		IniFile->WriteInteger(Section, "LoadTrainCount", LoadTrainCount);
	}
	__finally {
		delete IniFile;
	}
}

// ---------------------------------------------------------------------------
void TSettings::SaveDatabases(String ConfigFileName) {
	TIniFile * IniFile = new TIniFile(ConfigFileName);

	String Section;
	try {
		Section = "Local";
		IniFile->WriteString(Section, "host", LocalConnection->Host);
		IniFile->WriteString(Section, "port", LocalConnection->Port);
		IniFile->WriteString(Section, "user", LocalConnection->User);
		IniFile->WriteString(Section, "pass",
			Encrypt(LocalConnection->Password));

		Section = "Server";
		IniFile->WriteString(Section, "host", ServerConnection->Host);
		IniFile->WriteString(Section, "port", ServerConnection->Port);
		IniFile->WriteString(Section, "user", ServerConnection->User);
		IniFile->WriteString(Section, "pass",
			Encrypt(ServerConnection->Password));
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

	String ConfigFileName;

	String Section;

	try {
		ConfigFileName = GetConfigFileName(IDS_SETTINGS_CONFIG_USERS);
		SaveUsers(ConfigFileName);

		ConfigFileName = GetConfigFileName(IDS_SETTINGS_CONFIG_SETTINGS);
		SaveSettings(ConfigFileName);

		ConfigFileName = GetConfigFileName(IDS_SETTINGS_CONFIG_DATABASES);
		SaveDatabases(ConfigFileName);

		ConfigFileName = GetConfigFileName(IDS_SETTINGS_CONFIG_VANTYPES);
		SaveVanTypes(ConfigFileName);

		ConfigFileName = GetConfigFileName(IDS_SETTINGS_CONFIG_CARGOTYPES);
		SaveCargoTypes(ConfigFileName);
		ConfigFileName = GetConfigFileName(IDS_SETTINGS_CONFIG_DEPART_STATIONS);
		SaveDepartStations(ConfigFileName);
		ConfigFileName =
			GetConfigFileName(IDS_SETTINGS_CONFIG_PURPOSE_STATIONS);
		SavePurposeStations(ConfigFileName);
		ConfigFileName =
			GetConfigFileName(IDS_SETTINGS_CONFIG_INVOICE_SUPPLIERS);
		SaveInvoiceRecipients(ConfigFileName);
		ConfigFileName =
			GetConfigFileName(IDS_SETTINGS_CONFIG_INVOICE_RECIPIENTS);
		SaveInvoiceSuppliers(ConfigFileName);
	}
	catch (Exception * E) {
		WriteToLog(Format(IDS_LOG_WRITE_FILE_FAIL,
			ARRAYOFCONST((ConfigFileName, E->Message))));

		return false;
	}

	return true;
}
