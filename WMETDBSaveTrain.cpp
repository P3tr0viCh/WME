// ---------------------------------------------------------------------------

#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsStr.h>
#include <UtilsMisc.h>

#include "WMEAdd.h"
#include "WMEStrings.h"

#include "WMETDBSaveTrain.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TDBSaveTrain::TDBSaveTrain(TConnectionInfo *ConnectionInfo,
	TTrain *Train) : TDatabaseOperation(ConnectionInfo) {
	VansFields = new TDBVansFields();
	TrainsFields = new TDBTrainsFields();

	FTrain = Train;
}

// ---------------------------------------------------------------------------
__fastcall TDBSaveTrain::~TDBSaveTrain() {
	TrainsFields->Free();
	VansFields->Free();
}

// ---------------------------------------------------------------------------
void TDBSaveTrain::OperationStart() {
}

// ---------------------------------------------------------------------------
void TDBSaveTrain::OperationEndOK() {
	WriteToLog(Format(IDS_LOG_MYSQL_SAVE_TRAIN_OK,
		ARRAYOFCONST((Train->VanList->Count))));
}

// ---------------------------------------------------------------------------
void TDBSaveTrain::OperationEndFail() {
	WriteToLog(Format(IDS_LOG_MYSQL_SAVE_TRAIN_FAIL, ErrorMessage));
}

// ---------------------------------------------------------------------------
void TDBSaveTrain::SetVansParam(TADOQuery *Query, TDBVansFieldName Name,
	int Index, Variant Value) {
	TParameter *Param = Query->Parameters->ParamByName
		(VansFields->GetParamName(Name, Index));
	Param->DataType = VansFields->GetFieldType(Name);
	Param->Value = Value;
}

// ---------------------------------------------------------------------------
void TDBSaveTrain::SetTrainsParam(TADOQuery *Query, TDBTrainsFieldName Name,
	Variant Value) {
	TParameter *Param = Query->Parameters->ParamByName
		(TrainsFields->GetParamName(Name));
	Param->DataType = TrainsFields->GetFieldType(Name);
	Param->Value = Value;
}

// ---------------------------------------------------------------------------
void TDBSaveTrain::Operation() {
	if (Train->VanList->IsEmpty()) {
		return;
	}

	UseDatabase = true;

	Connection->Open();

	TADOQuery *Query = new TADOQuery(NULL);
	try {
		Query->Connection = Connection;

		if (Train->TrainNum < 0) {
			Train->TrainNum = DateTimeToWTime(Now());
		}
		else {
			Query->SQL->Add("DELETE FROM vans");
			Query->SQL->Add("WHERE");
			Query->SQL->Add(VansFields->GetFieldName(fnVansTrnum) + "=" +
				VansFields->GetParamValue(fnVansTrnum));

			SetVansParam(Query, fnVansTrnum, -1, Train->TrainNum);

			Query->Prepared = true;

			Query->ExecSQL();

			Query->SQL->Clear();
			Query->SQL->Add("DELETE FROM trains");
			Query->SQL->Add("WHERE");
			Query->SQL->Add(TrainsFields->GetFieldName(fnTrainsTrnum) + "=" +
				TrainsFields->GetParamValue(fnTrainsTrnum));

			SetTrainsParam(Query, fnTrainsTrnum, Train->TrainNum);

			Query->Prepared = true;

			Query->ExecSQL();
		}

		Query->SQL->Clear();
		Query->SQL->Add("INSERT INTO vans");
		Query->SQL->Add("(");
		Query->SQL->Add(VansFields->GetFields(dboVansSaveTrain));
		Query->SQL->Add(")");
		Query->SQL->Add("VALUES");

		Query->SQL->Add("(" + VansFields->GetValues(dboVansSaveTrain, 0) + ")");
		for (int i = 1; i < Train->VanList->Count; i++) {
			Query->SQL->Add(",");
			Query->SQL->Add("(" + VansFields->GetValues(dboVansSaveTrain,
				i) + ")");
		}

		for (int i = 0; i < Train->VanList->Count; i++) {
			SetVansParam(Query, fnVansTrnum, i, Train->TrainNum);

			SetVansParam(Query, fnVansNum, i, Train->VanList->Items[i]->Num);
			SetVansParam(Query, fnVansWTime, i, Train->UnixTime);
			SetVansParam(Query, fnVansDatetime, i,
				DateTimeToSQLStr(Train->VanList->Items[i]->DateTime));

			SetVansParam(Query, fnVansVannum, i,
				Train->VanList->Items[i]->VanNum);

			SetVansParam(Query, fnVansCarrying, i,
				Train->VanList->Items[i]->Carrying);
			SetVansParam(Query, fnVansBrutto, i,
				Train->VanList->Items[i]->Brutto);
			SetVansParam(Query, fnVansTare, i, Train->VanList->Items[i]->Tare);
			SetVansParam(Query, fnVansNetto, i,
				Train->VanList->Items[i]->Netto);
			SetVansParam(Query, fnVansOverload, i,
				Train->VanList->Items[i]->Overload);

			SetVansParam(Query, fnVansOperator, i,
				Train->VanList->Items[i]->User->Name);
			SetVansParam(Query, fnVansOperatorTabNum, i,
				Train->VanList->Items[i]->User->TabNum);
			SetVansParam(Query, fnVansOperatorShiftNum, i,
				Train->VanList->Items[i]->User->ShiftNum);
		}

		Query->Prepared = true;

		Query->ExecSQL();

		Query->Prepared = false;

		Query->SQL->Clear();

		Query->SQL->Add("INSERT INTO trains");
		Query->SQL->Add("(");
		Query->SQL->Add(TrainsFields->GetFields(dboTrainsSaveTrain));
		Query->SQL->Add(")");
		Query->SQL->Add("VALUES");

		Query->SQL->Add("(" + TrainsFields->GetValues(dboTrainsSaveTrain,
			-1) + ")");

		SetTrainsParam(Query, fnTrainsTrnum, Train->TrainNum);
		SetTrainsParam(Query, fnTrainsWTime, Train->UnixTime);
		SetTrainsParam(Query, fnTrainsDatetime,
			DateTimeToSQLStr(Train->DateTime));
		SetTrainsParam(Query, fnTrainsCarrying, Train->Carrying);
		SetTrainsParam(Query, fnTrainsBrutto, Train->Brutto);
		SetTrainsParam(Query, fnTrainsTare, Train->Tare);
		SetTrainsParam(Query, fnTrainsNetto, Train->Netto);
		SetTrainsParam(Query, fnTrainsOverload, Train->Overload);
		SetTrainsParam(Query, fnTrainsVanCount, Train->VanCount);

		Query->Prepared = true;

		Query->ExecSQL();
	}
	__finally {
		Query->Free();
	}

	Connection->Close();
}

// ---------------------------------------------------------------------------
