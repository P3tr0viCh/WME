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

	FConnection = new TConnection();
	FUserList = new TObjList<TUser>();
}

// ---------------------------------------------------------------------------
__fastcall TSettings::~TSettings() {
	FUserList->Free();
	FConnection->Free();
}

// ---------------------------------------------------------------------------
bool __fastcall TSettings::Equals(TObject* Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TSettings *Settings = (TSettings*) Obj;

	if (!Settings->Connection->Equals(Connection))
		return false;

	if (Settings->UserList->Count != UserList->Count)
		return false;

	for (int i = 0; i < Settings->UserList->Count; i++) {
		if (!Settings->UserList->Items[i]->Equals(UserList->Items[i])) {
			return false;
		}
	}

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TSettings::Assign(TSettings* Source) {
	FConnection->Assign(Source->FConnection);
	FUserList->Assign(Source->FUserList);
}

// ---------------------------------------------------------------------------
String __fastcall TSettings::ToString() {
	String S;

	S = "TSettings{";
	S += "FConnection='" + FConnection->ToString() + "'";
	S += "FUserList->Count='" + IntToStr(FUserList->Count) + "'";
	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
int __fastcall UserListSort(void* Item1, void* Item2) {
	TUser* User1 = (TUser*)Item1;
	TUser* User2 = (TUser*)Item2;

	if (User1->IsAdmin && !User2->IsAdmin) {
		return -1;
	}

	if (!User1->IsAdmin && User2->IsAdmin) {
		return 1;
	}

	return AnsiCompareStr(User1->Name, User2->Name);
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
bool TSettings::Load() {
	if (!CheckConfigDir()) {
		return false;
	}

	TIniFile* IniFile;

	String ConfigFileName;

	String Section;

	try {
		// ---------------------
		ConfigFileName = GetConfigFileName("Database");

		IniFile = new TIniFile(ConfigFileName);
		try {
			Section = "Connection";

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

		// ---------------------
		ConfigFileName = GetConfigFileName("Users");

		TUser* User;

		IniFile = new TIniFile(ConfigFileName);
		try {
			int UserCount = IniFile->ReadInteger("Users", "Count", 0);

			for (int i = 0; i < UserCount; i++) {
				Section = "User_" + IntToStr(i);

				User = new TUser();

				User->Name = IniFile->ReadString(Section, "Name", "");
				User->Pass =
					EncryptPass(IniFile->ReadString(Section, "Pass", ""));
				User->TabNum = IniFile->ReadString(Section, "TabNum", "");
				User->ShiftNum = IniFile->ReadString(Section, "ShiftNum", "");

				User->IsAdmin = IniFile->ReadBool(Section, "IsAdmin", false);

				FUserList->Add(User);
			}

			if (FUserList->Count == 0) {
				User = new TUser();

				User->Name = LoadStr(IDS_TXT_ADMIN_DEFAULT_NAME);
				User->IsAdmin = true;

				FUserList->Add(User);
			}
		}
		__finally {
			delete IniFile;
		}
	}
	catch (Exception *E) {
		WriteToLog(Format(IDS_LOG_READ_FILE_FAIL,
			ARRAYOFCONST((ConfigFileName, E->Message))));

		return false;
	}

	return true;
}

// ---------------------------------------------------------------------------
bool TSettings::Save() {
	if (!CheckConfigDir()) {
		return false;
	}

	TIniFile* IniFile;

	String ConfigFileName;

	String Section;

	String SE = EncryptPass(Connection->Password);
	String SD = DecryptPass(SE);

	try {
		// ---------------------
		ConfigFileName = GetConfigFileName("Database");

		IniFile = new TIniFile(ConfigFileName);
		try {
			Section = "Connection";

			IniFile->WriteString(Section, "host", Connection->Host);
			IniFile->WriteString(Section, "port", Connection->Port);
			IniFile->WriteString(Section, "user", Connection->User);
			IniFile->WriteString(Section, "pass",
				DecryptPass(Connection->Password));
		}
		__finally {
			delete IniFile;
		}

		// ---------------------
		ConfigFileName = GetConfigFileName("Users");

		if (FileExists(ConfigFileName) && !DeleteFile(ConfigFileName)) {
			throw Exception("error delete file");
		}

		IniFile = new TIniFile(ConfigFileName);
		try {
			UserList->Sort(UserListSort);

			IniFile->WriteInteger("Users", "Count", UserList->Count);

			for (int i = 0; i < UserList->Count; i++) {
				Section = "User_" + IntToStr(i);

				IniFile->WriteString(Section, "Name", UserList->Items[i]->Name);
				IniFile->WriteString(Section, "Pass",
					EncryptPass(UserList->Items[i]->Pass));
				IniFile->WriteString(Section, "TabNum",
					UserList->Items[i]->TabNum);
				IniFile->WriteString(Section, "ShiftNum",
					UserList->Items[i]->ShiftNum);

				IniFile->WriteBool(Section, "IsAdmin",
					UserList->Items[i]->IsAdmin);
			}
		}
		__finally {
			delete IniFile;
		}
	}
	catch (Exception *E) {
		WriteToLog(Format(IDS_LOG_WRITE_FILE_FAIL,
			ARRAYOFCONST((ConfigFileName, E->Message))));

		return false;
	}

	return true;
}
