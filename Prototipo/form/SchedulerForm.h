#pragma once
#include "..\\tabellaOrario\\TabellaOrario.h"
#using <System.dll>
#include "..\\messaggi\pacchettoCommandData.h"

#include "..\\phisicalTrainList.h"
#include "..\\threads\\ThreadListenerATC_IXL.h"
#include <iostream>
#include "..\\threads\\ThreadPresentazione.h"
#include "..\\mapTrenoFisicoLogico.h"
#include "..\\messaggi\\Messaggi.h"
#include "..\\logger\\Logger.h"
#include "..\\Itinerari\\tabellaItinerari.h"
#include "..\\Itinerari\\tabellaFermate.h"

#include "..\\scheduler\\ManagerCDBIXL.h"
#include "..\\scheduler\\ManagerItinerarioIXL.h"
#include "..\\EventQueue.h"

#define TRACE
namespace Prototipo {
	using namespace System::Diagnostics;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;

	/// <summary>
	/// Riepilogo per SchedulerForm
	/// </summary>
	public ref class SchedulerForm : public System::Windows::Forms::Form
	{
	public:
		SchedulerForm(void)
		{
			InitializeComponent();
			//
			//TODO: aggiungere qui il codice del costruttore.
			//

			tb = gcnew tabellaItinerari();
			tb->leggifileconfigurazioneItinerari("..\\FileConfigurazione\\ConfigurazioneItinerari.xml");

			tabella  = gcnew TabellaOrario(tb);
			tabella->leggiTabellaOrario("..\\FileConfigurazione\\TabellaOrario.xml");

			tabfermate=gcnew tabellaFermate();
			tabfermate->leggifileconfigurazioneFermate("..\\FileConfigurazione\\ConfigurazioneFermate.xml");


			//Console::WriteLine(tf->ToString());

			listaTreni = gcnew phisicalTrainList();


			ThreadPresentazione ^sd = gcnew ThreadPresentazione(listaTreni);



			oThread2 = gcnew Thread( gcnew ThreadStart(sd, &ThreadPresentazione::TCP_Management_receive ) );

			oThread2->Start();

			ManagerCDBIXL ^manaCDBIXL = gcnew ManagerCDBIXL();
			ManagerItinerarioIXL ^manaINTIXL = gcnew ManagerItinerarioIXL();

			ThreadListenerATC_IXL ^ThLATCIXL = gcnew ThreadListenerATC_IXL(manaCDBIXL,manaINTIXL);

			oThread1 = gcnew Thread( gcnew ThreadStart(ThLATCIXL, &ThreadListenerATC_IXL::UDP_Management_receive ) );

			oThread1->Start();
			EventQueue ^EventQ = gcnew EventQueue();
			manaCDBIXL->Subscribe(EventQ);
			manaINTIXL->Subscribe(EventQ);
			//EventQ->Subscribe(manaINTIXL);
			//EventQ->Subscribe(manaCDBIXL);
		}
	protected:
		/// <summary>
		/// Liberare le risorse in uso.
		/// </summary>
		~SchedulerForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  ExitButton;
	private: System::Windows::Forms::Button^  button1;
	protected: 

	private:
		/// <summary>
		/// Variabile di progettazione necessaria.
		/// </summary>
		System::ComponentModel::Container ^components;
		TabellaOrario ^tabella;
		phisicalTrainList ^listaTreni;
		tabellaItinerari ^tb;
		tabellaFermate ^tabfermate;

		Thread^ oThread1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
			 Thread^ oThread2;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Metodo necessario per il supporto della finestra di progettazione. Non modificare
			 /// il contenuto del metodo con l'editor di codice.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->ExitButton = (gcnew System::Windows::Forms::Button());
				 this->button1 = (gcnew System::Windows::Forms::Button());
				 this->button2 = (gcnew System::Windows::Forms::Button());
				 this->button3 = (gcnew System::Windows::Forms::Button());
				 this->button4 = (gcnew System::Windows::Forms::Button());
				 this->SuspendLayout();
				 // 
				 // ExitButton
				 // 
				 this->ExitButton->Location = System::Drawing::Point(21, 21);
				 this->ExitButton->Name = L"ExitButton";
				 this->ExitButton->Size = System::Drawing::Size(75, 23);
				 this->ExitButton->TabIndex = 0;
				 this->ExitButton->Text = L"Exit";
				 this->ExitButton->UseVisualStyleBackColor = true;
				 this->ExitButton->Click += gcnew System::EventHandler(this, &SchedulerForm::ExitButton_Click);
				 // 
				 // button1
				 // 
				 this->button1->Location = System::Drawing::Point(168, 20);
				 this->button1->Name = L"button1";
				 this->button1->Size = System::Drawing::Size(87, 23);
				 this->button1->TabIndex = 1;
				 this->button1->Text = L"InviaMissione";
				 this->button1->UseVisualStyleBackColor = true;
				 this->button1->Click += gcnew System::EventHandler(this, &SchedulerForm::button1_Click);
				 // 
				 // button2
				 // 
				 this->button2->Location = System::Drawing::Point(21, 92);
				 this->button2->Name = L"button2";
				 this->button2->Size = System::Drawing::Size(146, 23);
				 this->button2->TabIndex = 2;
				 this->button2->Text = L"Visualize Tabella Orario";
				 this->button2->UseVisualStyleBackColor = true;
				 this->button2->Click += gcnew System::EventHandler(this, &SchedulerForm::button2_Click);
				 // 
				 // button3
				 // 
				 this->button3->Location = System::Drawing::Point(21, 146);
				 this->button3->Name = L"button3";
				 this->button3->Size = System::Drawing::Size(146, 23);
				 this->button3->TabIndex = 3;
				 this->button3->Text = L"Visualize Conf. Itinerari";
				 this->button3->UseVisualStyleBackColor = true;
				 this->button3->Click += gcnew System::EventHandler(this, &SchedulerForm::button3_Click);
				 // 
				 // button4
				 // 
				 this->button4->Location = System::Drawing::Point(21, 201);
				 this->button4->Name = L"button4";
				 this->button4->Size = System::Drawing::Size(146, 23);
				 this->button4->TabIndex = 4;
				 this->button4->Text = L"Visualize Conf. Fermate";
				 this->button4->UseVisualStyleBackColor = true;
				 this->button4->Click += gcnew System::EventHandler(this, &SchedulerForm::button4_Click);
				 // 
				 // SchedulerForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(408, 332);
				 this->Controls->Add(this->button4);
				 this->Controls->Add(this->button3);
				 this->Controls->Add(this->button2);
				 this->Controls->Add(this->button1);
				 this->Controls->Add(this->ExitButton);
				 this->Name = L"SchedulerForm";
				 this->Text = L"SchedulerForm";
				 this->ResumeLayout(false);

			 }
			 void TCP_Management()
			 {
				 phisicalTrain ^Treno = listaTreni->getPrimo();
				 const int WAKE_UP = 0;
				 const int CHANGE_GOA_LEVEL = 3;
				 const int TRN = 4;
				 const int SLEEP = 7;
				 try
				 {


					 Messaggi ^wakeUpPkt = gcnew Messaggi();


					 wakeUpPkt->setNID_MESSAGE(201);


					 wakeUpPkt->get_pacchettoCommandData()->setNID_PACKET(161);
					 wakeUpPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(WAKE_UP);
					 wakeUpPkt->setT_TIME(tabella->getFirstTRN());





					 // Buffer for reading data
					 array<Byte>^bytes_buffer1 = gcnew array<Byte>(wakeUpPkt->getSize());

					 wakeUpPkt->serialize(bytes_buffer1);


					 Messaggi ^trainRunningNumberPkt = gcnew Messaggi();


					 trainRunningNumberPkt->setNID_MESSAGE(201);
					 trainRunningNumberPkt->get_pacchettoCommandData()->setNID_PACKET(161);
					 trainRunningNumberPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(TRN);
					 trainRunningNumberPkt->setT_TIME(tabella->getFirstTRN());
					 trainRunningNumberPkt->get_pacchettoCommandData()->setNID_OPERATIONAL(tabella->getFirstTRN());


					 // Buffer for reading data
					 array<Byte>^bytes_buffer2 = gcnew array<Byte>(trainRunningNumberPkt->getSize());

					 trainRunningNumberPkt->serialize(bytes_buffer2);

					 Messaggi ^missionPlanPkt = gcnew Messaggi();

					 missionPlanPkt->setNID_MESSAGE(200);
					 missionPlanPkt->get_pacchettoMissionPlan()->setNID_PACKET(160);
					 int TRN = tabella->getFirstTRN();
					 tabella->setMissionPlanMessage(TRN, missionPlanPkt->get_pacchettoMissionPlan());



					 // Buffer for reading data
					 array<Byte>^bytes_buffer3 = gcnew array<Byte>(missionPlanPkt->getSize());

					 missionPlanPkt->serialize(bytes_buffer3);

					 // Creates the Socket to send data over a TCP connection.
					 Socket ^sock = gcnew Socket( System::Net::Sockets::AddressFamily::InterNetwork,System::Net::Sockets::SocketType::Stream,System::Net::Sockets::ProtocolType::Tcp );


					 String ^IP = gcnew String(Treno->getIpAddress());
					 sock->Connect(IP, Treno->getTcpPort());

					 NetworkStream ^myStream = gcnew NetworkStream(sock);

					 myStream->Write(bytes_buffer1, 0, wakeUpPkt->getSize());
#ifdef TRACE

					 Logger::Info(wakeUpPkt->getNID_MESSAGE(),"ATS",IP->ToString(),wakeUpPkt->getSize(),BitConverter::ToString(bytes_buffer1),"Init");

#endif // TRACE
					 myStream->Write(bytes_buffer2, 0, trainRunningNumberPkt->getSize());
#ifdef TRACE

					 Logger::Info(trainRunningNumberPkt->getNID_MESSAGE(),"ATS",IP->ToString(),trainRunningNumberPkt->getSize(),BitConverter::ToString(bytes_buffer2),"Init");

#endif // TRACE
					 myStream->Write(bytes_buffer3, 0, missionPlanPkt->getSize());
#ifdef TRACE

					 Logger::Info(missionPlanPkt->getNID_MESSAGE(),"ATS",IP->ToString(),missionPlanPkt->getSize(),BitConverter::ToString(bytes_buffer3),"Init");

#endif // TRACE

					 Messaggi ^pktAck = gcnew Messaggi();

					 pktAck->set_pacchettoAcknowledgement();

					 // Buffer for reading data
					 array<Byte>^bytes_buffer4 = gcnew array<Byte>(pktAck->getSize());

					 myStream->Read(bytes_buffer4, 0, pktAck->getSize());
					 pktAck->deserialize(bytes_buffer4);

#ifdef TRACE

					 Logger::Info(pktAck->getNID_MESSAGE(),IP->ToString(),"ATS",pktAck->getSize(),BitConverter::ToString(bytes_buffer4),"Init");

#endif // TRACE




					 cout << "RESPONSE\n" << pktAck->get_pacchettoAcknowledgement()->getQ_MISSION_RESPONSE();


					 cout << "DONE\n";
					 myStream->Close();
					 sock->Close();
				 }
				 catch ( SocketException^ e ) 
				 {
					 Console::WriteLine( "SocketException: {0}", e );
#ifdef TRACE
					 Logger::Exception(e,"SchedulerForm");  
#endif // TRACE
				 }


			 }
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

				 if(!listaTreni->is_Empthy()){
					 Thread  ^oThread = gcnew Thread( gcnew ThreadStart(this, &Prototipo::SchedulerForm::TCP_Management) );

					 oThread->Start();

				 }else{

#ifdef TRACE
					 Logger::Info("SchedulerForm"," Lista treni Vuota");  
#endif // TRACE

					 MessageBox::Show("Lista treni Vuota");
				 }


			 }
	private: System::Void ExitButton_Click(System::Object^  sender, System::EventArgs^  e) {
#ifdef TRACE
				 Logger::Info("SchedulerForm"," ExitButton_Click");  
#endif // TRACE
				 oThread1->Abort();
				 oThread2->Abort();
				 Application::Exit();
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(tabella->get_TabellaOrario()->Count<1){
					 MessageBox::Show("Tabella Orario Vuota");
				 }else{

					 System::Windows::Forms::Form ^  form;
					 System::Windows::Forms::DataGridView^  dataGridView1;
					 dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(dataGridView1))->BeginInit();
					 dataGridView1->AccessibleName = L"datagrid";
					 dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
					 dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
					 dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
					 dataGridView1->Location = System::Drawing::Point(12, 12);
					 dataGridView1->Name = L"dataGridView1";
					 dataGridView1->Size = System::Drawing::Size(890, 344);
					 dataGridView1->TabIndex = 8;

					 form = gcnew Form();
					 form->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
					 form->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					 form->ClientSize = System::Drawing::Size(915, 415);
					 form->Controls->Add(dataGridView1);
					 form->Name = L"Tabella Orario";
					 form->Text = L"Tabella Orario";
					 form->ResumeLayout(false);
					 form->PerformLayout();
					 form->SuspendLayout();

					 dataGridView1->ColumnCount = 10;
					 dataGridView1->RowCount = tabella->get_TabellaOrario()->Count*8;
					 int colonna=0;
					 int riga=0;
					 dataGridView1->Columns[ 0 ]->Name = "Id_Treno";
					 dataGridView1->Columns[ 1 ]->Name = "Nome Stazione";
					 dataGridView1->Columns[ 2 ]->Name = "id Stazione";
					 dataGridView1->Columns[ 3 ]->Name = "Orario Arrivo";
					 dataGridView1->Columns[ 4 ]->Name = "Orario Partenza";
					 dataGridView1->Columns[ 5 ]->Name = "BinProg";
					 dataGridView1->Columns[ 6 ]->Name = "TempoMAPorte";
					 dataGridView1->Columns[ 7 ]->Name = "LatoAPorte";
					 dataGridView1->Columns[ 8 ]->Name = "It Entrata";
					 dataGridView1->Columns[ 9 ]->Name = "It Uscita";

					 for each( KeyValuePair<int , List<Fermata^>^> kvp in tabella->get_TabellaOrario() )
					 {

						 String ^po=kvp.Key+"\n\r";
						 dataGridView1->Rows[riga]->Cells[0]->Value=po;


						 for each (Fermata ^dvar in kvp.Value)
						 { 
							 dataGridView1->Rows[riga]->Cells[1]->Value=dvar->getnameStazione();
							 dataGridView1->Rows[riga]->Cells[2]->Value=dvar->getIdStazione();
							 TimeSpan Arrivo = TimeSpan::FromSeconds(dvar->getOrarioArrivo()*30);
							 dataGridView1->Rows[riga]->Cells[3]->Value= Arrivo.ToString();
							 TimeSpan Partenza = TimeSpan::FromSeconds(dvar->getOrarioPartenza()*30);
							 dataGridView1->Rows[riga]->Cells[4]->Value=Partenza.ToString();
							 dataGridView1->Rows[riga]->Cells[5]->Value=dvar->getBinarioProgrammato();
							 dataGridView1->Rows[riga]->Cells[6]->Value=dvar->gettempoMinimoAperturaPorte();
							 dataGridView1->Rows[riga]->Cells[7]->Value=dvar->getLatoAperturaPorte();
							 dataGridView1->Rows[riga]->Cells[8]->Value=dvar->getnameitinerarioEntrata();
							 dataGridView1->Rows[riga]->Cells[9]->Value=dvar->getnameitinerarioUscita();
							 riga++;
						 }

					 }


					 form->Visible=true;
				 }

			 }
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(tb->getMap()->Count<1){
					 MessageBox::Show("Tabella Conf Itinirari Vuota");
				 }else{
					 System::Windows::Forms::Form ^  form;
					 System::Windows::Forms::DataGridView^  dataGridView1;
					 dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(dataGridView1))->BeginInit();
					 dataGridView1->AccessibleName = L"datagridit";
					 dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
					 dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
					 dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
					 dataGridView1->Location = System::Drawing::Point(12, 12);
					 dataGridView1->Name = L"dataGridViewit";
					 dataGridView1->Size = System::Drawing::Size(810, 360);
					 dataGridView1->TabIndex = 18;

					 form = gcnew Form();
					 form->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
					 form->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					 form->ClientSize = System::Drawing::Size(830, 415);
					 form->Controls->Add(dataGridView1);
					 form->Name = L"Tabella Configurazione Itinerari";
					 form->Text = L"Tabella Configurazione Itinerari";
					 form->ResumeLayout(false);
					 form->PerformLayout();
					 form->SuspendLayout();

					 dataGridView1->ColumnCount = 12;
					 dataGridView1->RowCount = 410;
					 int colonna=0;
					 int riga=0;
					 dataGridView1->Columns[ 0 ]->Name = "offset";
					 // dataGridView1->Columns[ 1 ]->Name = "offset";
					 dataGridView1->Columns[ 1 ]->Name = "Nome Stazione";
					 dataGridView1->Columns[ 2 ]->Name = "prevCDB";
					 dataGridView1->Columns[ 3 ]->Name = "Id It";
					 dataGridView1->Columns[ 4 ]->Name = "Nome It";
					 dataGridView1->Columns[ 5 ]->Name = "LRGB";
					 dataGridView1->Columns[ 6 ]->Name = "DSTOP";
					 dataGridView1->Columns[ 7 ]->Name = "Dir";
					 dataGridView1->Columns[ 8 ]->Name = "nextCDB";
					 //  dataGridView1->Columns[ 10 ]->Name = "prevCDB";
					 dataGridView1->Columns[ 9]->Name = "PB";
					 dataGridView1->Columns[ 10]->Name = "NS";
					 dataGridView1->Columns[ 11 ]->Name = "L_CDB";

					 for each( KeyValuePair<int , stazione^> kvp in tb->getMap() )
					 {

						 String ^po=kvp.Key+"\n\r";
						 dataGridView1->Rows[riga]->Cells[0]->Value=po;

						 stazione ^station =kvp.Value;
						 // dataGridView1->Rows[riga]->Cells[1]->Value= station->get_idStazione();
						 dataGridView1->Rows[riga]->Cells[1]->Value= station->get_NomeStazione();

						 for each (KeyValuePair<String^,List<Itinerario^>^> ^ikvp in station->getItinerari())
						 {

							 dataGridView1->Rows[riga]->Cells[2]->Value=ikvp->Key;
							 List<Itinerario^>^listitn = ikvp->Value;
							 for each (Itinerario ^itvar in listitn)
							 {
								 dataGridView1->Rows[riga]->Cells[3]->Value=itvar->getId();
								 dataGridView1->Rows[riga]->Cells[4]->Value=itvar->getName();
								 dataGridView1->Rows[riga]->Cells[5]->Value=itvar->getLrgb();
								 dataGridView1->Rows[riga]->Cells[6]->Value=itvar->getDStop();
								 dataGridView1->Rows[riga]->Cells[7]->Value=itvar->getLatoBanchina();
								 dataGridView1->Rows[riga]->Cells[8]->Value=itvar->getNextCDB();
								 //	 dataGridView1->Rows[riga]->Cells[10]->Value=itvar->getPrevCDB();
								 dataGridView1->Rows[riga]->Cells[9]->Value=itvar->getPorteBanchina();
								 dataGridView1->Rows[riga]->Cells[10]->Value=itvar->get_nextstation();
								 List<int> ^cdb = itvar->getLCDB();
								 for each (int cdbvar in cdb)
								 {
									 if(cdbvar){
										 dataGridView1->Rows[riga]->Cells[11]->Value=cdbvar;
									 }
									 riga++;
								 }


							 }


						 }

					 }


					 form->Visible=true;

				 }

			 }
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {

				 if(tabfermate->getTabFermate()->Count<1){
					 MessageBox::Show("Tabella Conf Fermate Vuota");
				 }else{
					 System::Windows::Forms::Form ^  form;
					 System::Windows::Forms::DataGridView^  dataGridView1;
					 dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(dataGridView1))->BeginInit();
					 dataGridView1->AccessibleName = L"datagridit";
					 dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
					 dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
					 dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
					 dataGridView1->Location = System::Drawing::Point(12, 12);
					 dataGridView1->Name = L"dataGridViewit";
					 dataGridView1->Size = System::Drawing::Size(810, 360);
					 dataGridView1->TabIndex = 18;

					 form = gcnew Form();
					 form->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
					 form->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					 form->ClientSize = System::Drawing::Size(830, 415);
					 form->Controls->Add(dataGridView1);
					 form->Name = L"Tabella Configurazione Fermata";
					 form->Text = L"Tabella Configurazione Fermata";
					 form->ResumeLayout(false);
					 form->PerformLayout();
					 form->SuspendLayout();

					 dataGridView1->ColumnCount = 11;
					 dataGridView1->RowCount = 15;
					 int colonna=0;
					 int riga=0;

					 dataGridView1->Columns[ 0 ]->Name = "Nome Fermata";				
					 dataGridView1->Columns[ 1 ]->Name = "Nome Binario";
					 dataGridView1->Columns[ 2 ]->Name = "Binario";
					 dataGridView1->Columns[ 3 ]->Name = "Direzione";
					 dataGridView1->Columns[ 4 ]->Name = "NID_LRGB";
					 dataGridView1->Columns[ 5 ]->Name = "DSTOP";
					 dataGridView1->Columns[ 6 ]->Name = "PB";
					 dataGridView1->Columns[ 7 ]->Name = "LB";
					 dataGridView1->Columns[ 8 ]->Name = "nextCDB";

					 dataGridView1->Columns[ 9]->Name = "prevCDB";
					 dataGridView1->Columns[ 10]->Name = "CDB";


					 for each( KeyValuePair<String^ ,  List<binario^> ^> ^kvp in tabfermate->getTabFermate() )
					 {

						 String ^po=kvp->Key+"\n\r";
						 dataGridView1->Rows[riga]->Cells[0]->Value=po;

						 List<binario^> ^binari =kvp->Value;

						 for each (binario^ ikvp in binari)
						 {	
							 dataGridView1->Rows[riga]->Cells[1]->Value= ikvp->getNameBin();
							 dataGridView1->Rows[riga]->Cells[2]->Value=ikvp->getBin();
							 dataGridView1->Rows[riga]->Cells[3]->Value=ikvp->getDirezione();
							 dataGridView1->Rows[riga]->Cells[4]->Value=ikvp->getNid_lrgb();
							 dataGridView1->Rows[riga]->Cells[5]->Value=ikvp->getD_stop();
							 dataGridView1->Rows[riga]->Cells[6]->Value=ikvp->getPorteBanchina();
							 dataGridView1->Rows[riga]->Cells[7]->Value=ikvp->getLatoBanchina();
							 dataGridView1->Rows[riga]->Cells[8]->Value=ikvp->getNextCDB();
							 //	 dataGridView1->Rows[riga]->Cells[10]->Value=itvar->getPrevCDB();
							 dataGridView1->Rows[riga]->Cells[9]->Value=ikvp->getPrevCDB();
							 dataGridView1->Rows[riga]->Cells[10]->Value=ikvp->getCDB ();


							 riga++;

						 }

					 }


					 form->Visible=true;

				 }

			 }
	};


}
