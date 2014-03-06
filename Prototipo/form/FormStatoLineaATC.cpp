#include "FormStatoLineaATC.h"

void Prototipo::FormStatoLineaATC::genera(){


	tableCDB = gcnew tableLayoutPanelAllCDB(listbuttonCDB);
	tableCDB->Location =  System::Drawing::Point(1, 1);
	tableCDB->Name = "statoCDB";
	//tablel->Size =  System::Drawing::Size(75, 16);
	tableCDB->TabIndex = 1;
	tableCDB->Text = "Stato CDB IXL";

	Controls->Add(tableCDB);

}
void Prototipo::FormStatoLineaATC::OnNext(Event<StateCDB^> ^value){
	if(value!=nullptr){
				StateCDB ^stCDB =	value->getEvent();
				if(stCDB!=nullptr){
					int id =	stCDB->getNID_CDB();
					int stato =	stCDB->getQ_STATOCDB();
					int nid_op=	stCDB->getNID_OPERATIONAL();
					int nid_engine =	stCDB->getNID_ENGINE();
					//tableCDB->findandsetCDB(id,stato, nid_op, nid_engine);
					this->Invoke(myDelegate,id,stato, nid_op, nid_engine);
				}
			}
}

/*
void Prototipo::FormStatoLineaATC::aggiorna(){

	while(!_shouldStop){
		if(eventiATC==nullptr){
			Thread::Sleep(100);
		}else{
			Event<StateCDB^> ^even = eventiATC->getEvent();
			if(even!=nullptr){
				StateCDB ^stCDB =	even->getEvent();
				if(stCDB!=nullptr){
					int id =	stCDB->getNID_CDB();
					int stato =	stCDB->getQ_STATOCDB();
					int nid_op=	stCDB->getNID_OPERATIONAL();
					int nid_engine =	stCDB->getNID_ENGINE();
					//tableCDB->findandsetCDB(id,stato, nid_op, nid_engine);
					this->Invoke(myDelegate,id,stato, nid_op, nid_engine);
				}
			}

		}
	}

}*/

void  Prototipo::FormStatoLineaATC::findandsetCDB(int id, int stato, int nid_op, int nid_engine){
	if(listbuttonCDB->ContainsKey(id)){
		if(stato==QStateCDB::cdbOccupato){
			listbuttonCDB[id]->BackColor= System::Drawing::Color::Red;
			String ^texttoltip =String::Format("NID_O {0}\n\rNID_E {1}", nid_op, nid_engine);
			ToolTip1->SetToolTip(listbuttonCDB[id], texttoltip );
		}
		if(stato==QStateCDB::cdbLibero){
			listbuttonCDB[id]->BackColor= System::Drawing::Color::Gray;
			ToolTip1->SetToolTip(listbuttonCDB[id], "Libero" );
		}
		if(stato==QStateCDB::cdbImpegnato){
			listbuttonCDB[id]->BackColor= System::Drawing::Color::White;
			String ^texttoltip =String::Format("NID_O {0}\n\rNID_E {1}", nid_op, nid_engine);
			ToolTip1->SetToolTip(listbuttonCDB[id], texttoltip );
		}

	}

}


void Prototipo::FormStatoLineaATC::RequestStop()
    {
        _shouldStop = true;
    }