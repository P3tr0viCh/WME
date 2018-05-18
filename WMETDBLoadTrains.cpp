// ---------------------------------------------------------------------------

#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsStr.h>

#include "WMEStrings.h"

#include "WMETDBLoadTrains.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TDBLoadTrains::TDBLoadTrains(TConnectionInfo * ConnectionInfo,
	int APage, int ATrainCount) : TDatabaseOperation(ConnectionInfo) {
	Page = APage;
	TrainCount = ATrainCount;

	FTrainList = new TTrainList();

	TrainsFields = new TDBTrainsFields();
}

// ---------------------------------------------------------------------------
__fastcall TDBLoadTrains::~TDBLoadTrains() {
	TrainsFields->Free();

	FTrainList->Free();
}

// ---------------------------------------------------------------------------
void TDBLoadTrains::OperationStart() {
}

// ---------------------------------------------------------------------------
void TDBLoadTrains::OperationEndOK() {
	WriteToLog(Format(IDS_LOG_MYSQL_LOAD_TRAINS_OK,
		ARRAYOFCONST((TrainList->Count))));
}

// ---------------------------------------------------------------------------
void TDBLoadTrains::OperationEndFail() {
	WriteToLog(Format(IDS_LOG_MYSQL_LOAD_TRAINS_FAIL, ErrorMessage));
}

// ---------------------------------------------------------------------------
void TDBLoadTrains::Operation() {
	UseDatabase = true;

	Connection->Open();

	TADOQuery * Query = new TADOQuery(NULL);
	try {
		Query->Connection = Connection;

		Query->SQL->Add("SELECT");
		Query->SQL->Add(TrainsFields->GetFields());
		Query->SQL->Add("FROM trains");
		Query->SQL->Add("ORDER BY");
		Query->SQL->Add(TrainsFields->GetFieldName(fnTrainsDatetime));
		Query->SQL->Add("DESC");

		if (TrainCount > 0 && Page >= 0) {
			Query->SQL->Add("LIMIT " + IntToStr(TrainCount) + " OFFSET " +
				IntToStr(TrainCount * Page));
		}

		// WriteToLog(Query->SQL->Text);

		Query->Open();

		TTrain * Train;

		while (!Query->Eof) {
			Train = new TTrain();

			Train->TrainNum =
				Query->FieldByName(TrainsFields->GetFieldName(fnTrainsTrnum))
				->AsInteger;
			Train->DateTime =
				Query->FieldByName(TrainsFields->GetFieldName(fnTrainsDatetime))
				->AsDateTime;

			Train->WeightType = (TWeightType) Query->FieldByName
				(TrainsFields->GetFieldName(fnTrainsWeightType))->AsInteger;

			Train->Carrying =
				Query->FieldByName(TrainsFields->GetFieldName(fnTrainsCarrying))
				->AsInteger;
			Train->Brutto =
				Query->FieldByName(TrainsFields->GetFieldName(fnTrainsBrutto))
				->AsInteger;
			Train->Tare =
				Query->FieldByName(TrainsFields->GetFieldName(fnTrainsTare))
				->AsInteger;
			Train->Netto =
				Query->FieldByName(TrainsFields->GetFieldName(fnTrainsNetto))
				->AsInteger;
			Train->Overload =
				Query->FieldByName(TrainsFields->GetFieldName(fnTrainsOverload))
				->AsInteger;

			Train->VanCount =
				Query->FieldByName(TrainsFields->GetFieldName(fnTrainsVanCount))
				->AsInteger;

			Train->User->Name =
				Query->FieldByName(TrainsFields->GetFieldName(fnTrainsOperator))
				->AsString;
			Train->User->TabNum =
				Query->FieldByName
				(TrainsFields->GetFieldName(fnTrainsOperatorTabNum))->AsString;
			Train->User->ShiftNum =
				Query->FieldByName
				(TrainsFields->GetFieldName(fnTrainsOperatorShiftNum))
				->AsString;

			FTrainList->Add(Train);

			Query->Next();
		}
	}
	__finally {
		Query->Free();
	}

	Connection->Close();
}

// ---------------------------------------------------------------------------
