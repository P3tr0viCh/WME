// ---------------------------------------------------------------------------

#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsStr.h>
#include <UtilsMisc.h>

#include "WMEStrings.h"

#include "WMETDBSaveTrain.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TDBSaveTrain::TDBSaveTrain(TConnectionInfo *ConnectionInfo,
	TVanList *VanList) : TDatabaseOperation(ConnectionInfo) {
	FVanList = VanList;
}

// ---------------------------------------------------------------------------
void TDBSaveTrain::OperationStart() {
}

// ---------------------------------------------------------------------------
void TDBSaveTrain::OperationEndOK() {
	WriteToLog(Format(IDS_LOG_MYSQL_SAVE_TRAIN_OK,
		ARRAYOFCONST((VanList->Count))));
}

// ---------------------------------------------------------------------------
void TDBSaveTrain::OperationEndFail() {
	WriteToLog(Format(IDS_LOG_MYSQL_SAVE_TRAIN_FAIL, ErrorMessage));
}

// ---------------------------------------------------------------------------
String GetParam(String ParamName, int Index) {
	return Index < 0 ? ParamName : ":" + ParamName + IntToStr(Index);
}

// ---------------------------------------------------------------------------
String GetVansParams(int Index) {
	return GetParam("trnum", Index) + "," + GetParam("num", Index) + "," +
		GetParam("wtime", Index) + "," + GetParam("bdatetime", Index) + "," +
		GetParam("vannum", Index) + "," + GetParam("brutto", Index);
}

// ---------------------------------------------------------------------------
String GetTrainParams(int Index) {
	return GetParam("trnum", Index) + "," + GetParam("wtime", Index) + "," +
		GetParam("bdatetime", Index) + "," + GetParam("brutto", Index);
}

// ---------------------------------------------------------------------------
String DateTimeToSQLStr(TDateTime ADateTime) {
	return FormatDateTime("yyyyMMddhhnnss", ADateTime);
}

// ---------------------------------------------------------------------------
void TDBSaveTrain::Operation() {
	if (VanList->Count == 0) {
		return;
	}

	randomize();

	UseDatabase = true;

	Connection->Open();

	TParameter *Param;

	TADOQuery *Query = new TADOQuery(NULL);
	try {
		Query->Connection = Connection;

		int TrainNum = rand();

		int UnixTime = 0;

		Query->SQL->Clear();
		Query->SQL->Add("INSERT INTO vans");
		Query->SQL->Add("(");
		Query->SQL->Add(GetVansParams(-1));
		Query->SQL->Add(")");
		Query->SQL->Add("VALUES");

		Query->SQL->Add("(" + GetVansParams(0) + ")");
		for (int i = 1; i < VanList->Count; i++) {
			Query->SQL->Add(",");
			Query->SQL->Add("(" + GetVansParams(i) + ")");
		}

		for (int i = 0; i < VanList->Count; i++) {
			Param = Query->Parameters->ParamByName("trnum" + IntToStr(i));
			Param->DataType = ftInteger;
			Param->Value = TrainNum;
			Param = Query->Parameters->ParamByName("num" + IntToStr(i));
			Param->DataType = ftInteger;
			Param->Value = VanList->Items[i]->Num;
			Param = Query->Parameters->ParamByName("wtime" + IntToStr(i));
			Param->DataType = ftInteger;
			Param->Value = UnixTime;
			Param = Query->Parameters->ParamByName("bdatetime" + IntToStr(i));
			Param->DataType = ftString;
			Param->Value = DateTimeToSQLStr(VanList->Items[i]->DateTime);
			Param = Query->Parameters->ParamByName("vannum" + IntToStr(i));
			Param->DataType = ftString;
			Param->Value = VanList->Items[i]->VanNum;
			Param = Query->Parameters->ParamByName("brutto" + IntToStr(i));
			Param->DataType = ftInteger;
			Param->Value = VanList->Items[i]->Brutto;
		}

		// WriteToLog(VanList->ToString());

		Query->Prepared = true;

		Query->ExecSQL();

		Query->Prepared = false;

		float Brutto = 0;
		for (int i = 0; i < VanList->Count; i++) {
			Brutto += VanList->Items[i]->Brutto;
		}

		Query->SQL->Clear();

		Query->SQL->Add("INSERT INTO trains");
		Query->SQL->Add("(");
		Query->SQL->Add(GetTrainParams(-1));
		Query->SQL->Add(")");
		Query->SQL->Add("VALUES");
		Query->SQL->Add("(" + GetTrainParams(0) + ")");

		Param = Query->Parameters->ParamByName("trnum0");
		Param->DataType = ftInteger;
		Param->Value = TrainNum;
		Param = Query->Parameters->ParamByName("wtime0");
		Param->DataType = ftInteger;
		Param->Value = UnixTime;
		Param = Query->Parameters->ParamByName("bdatetime0");
		Param->DataType = ftString;
		Param->Value = DateTimeToSQLStr(VanList->Items[0]->DateTime);
		Param = Query->Parameters->ParamByName("brutto0");
		Param->DataType = ftInteger;
		Param->Value = Brutto;

		Query->Prepared = true;

		Query->ExecSQL();
	}
	__finally {
		Query->Free();
	}

	Connection->Close();
}

// ---------------------------------------------------------------------------
