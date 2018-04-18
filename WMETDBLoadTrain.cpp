// ---------------------------------------------------------------------------

#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsStr.h>

#include "WMEStrings.h"

#include "WMETDBLoadTrain.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TDBLoadTrain::TDBLoadTrain(TConnectionInfo *ConnectionInfo,
	int TrainNum) : TDatabaseOperation(ConnectionInfo) {
	FVanList = new TVanList();

	VansFields = new TDBVansFields();

	FTrainNum = TrainNum;
}

// ---------------------------------------------------------------------------
__fastcall TDBLoadTrain::~TDBLoadTrain() {
	VansFields->Free();

	FVanList->Free();
}

// ---------------------------------------------------------------------------
void TDBLoadTrain::OperationStart() {
}

// ---------------------------------------------------------------------------
void TDBLoadTrain::OperationEndOK() {
	WriteToLog(Format(IDS_LOG_MYSQL_LOAD_TRAIN_OK,
		ARRAYOFCONST((VanList->Count))));
}

// ---------------------------------------------------------------------------
void TDBLoadTrain::OperationEndFail() {
	WriteToLog(Format(IDS_LOG_MYSQL_LOAD_TRAIN_FAIL, ErrorMessage));
}

// ---------------------------------------------------------------------------
void TDBLoadTrain::Operation() {
	UseDatabase = true;

	Connection->Open();

	TADOQuery *Query = new TADOQuery(NULL);
	try {
		Query->Connection = Connection;

		Query->SQL->Add("SELECT");
		Query->SQL->Add(VansFields->GetFields(dboVansLoadTrain));
		Query->SQL->Add("FROM vans");
		Query->SQL->Add("WHERE");
		Query->SQL->Add(VansFields->GetFieldName(fnVansTrnum));
		Query->SQL->Add("=");
		Query->SQL->Add(VansFields->GetParamValue(fnVansTrnum));
		Query->SQL->Add("ORDER BY");
		Query->SQL->Add(VansFields->GetFieldName(fnVansNum));

		// WriteToLog(Query->SQL->Text);

		TParameter *Param = Query->Parameters->ParamByName
			(VansFields->GetParamName(fnVansTrnum));
		Param->DataType = VansFields->GetFieldType(fnVansTrnum);
		Param->Value = TrainNum;

		Query->Open();

		TVan *Van;

		while (!Query->Eof) {
			Van = new TVan();

			Van->Num = Query->FieldByName(VansFields->GetFieldName(fnVansNum))
				->AsInteger;

			Van->DateTime =
				Query->FieldByName(VansFields->GetFieldName(fnVansDatetime))
				->AsDateTime;

			Van->Carrying =
				Query->FieldByName(VansFields->GetFieldName(fnVansCarrying))
				->AsInteger;
			Van->Brutto =
				Query->FieldByName(VansFields->GetFieldName(fnVansBrutto))
				->AsInteger;

			Van->TareTrft =
				Query->FieldByName(VansFields->GetFieldName(fnVansTare))
				->AsInteger;
			Van->TareIndex = 0;

			// Van->Netto =
			// Query->FieldByName(VansFields->GetFieldName(fnVansNetto))
			// ->AsInteger;
			// Van->Overload =
			// Query->FieldByName(VansFields->GetFieldName(fnVansOverload))
			// ->AsInteger;

			FVanList->Add(Van);

			Query->Next();
		}
	}
	__finally {
		Query->Free();
	}

	Connection->Close();
}

// ---------------------------------------------------------------------------