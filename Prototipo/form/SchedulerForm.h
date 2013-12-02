#pragma once
#include "..\\tabellaOrario\\TabellaOrario.h"
#using <System.dll>
#include "..\\messaggi\pacchettoCommandData.h"
#include "..\\tabellaOrario\\FormVisualizzeTabOrario.h"
#include "..\\Itinerari\\FormVisualizzeConfItine.h"
#include "..\\Itinerari\\FormVisualizzeConfFermate.h"
#include "..\\phisicalTrainList.h"
#include "..\\threads\\ThreadListenerATC_IXL.h"
#include <iostream>
#include "..\\threads\\ThreadPresentazione.h"
#include "..\\mapTrenoFisicoLogico.h"
#include "..\\messaggi\\Messaggi.h"
#include "..\\logger\\Logger.h"
#include "..\\Itinerari\\TabellaStazioni.h"

#include "..\\manager\\ManagerStatoLineaATC.h"
#include "..\\manager\\ManagerStatoLineaIXL.h"
#include "..\\manager\\ManagerMsgATO.h"
#include "..\\ThreadSchedule.h"
#include "..\\ThreadSchedulerSortedList.h"
#include "..\\EventQueue.h"
#include "..\\wdogcontrol.h"
#include "..\\FormStatoLineaIXL.h"
#include "FormStatoLineaATC.h"
#include "..\\ConfVelocita\\ConfigurazioneVelocita.h"
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
	using namespace System::Runtime::InteropServices;
	using namespace System::Globalization;
	using namespace System::Xml;
	/*Utilizzo questa classe per rappresentare graficamente un pannello di controllo dello scheduler
	sono presenti alcuni pulsanti che visualizzano informazioni sulla configurazione del sistema*/
	/// <summary>
	/// Riepilogo per SchedulerForm
	/// </summary>
	public ref class SchedulerForm : public System::Windows::Forms::Form
	{
	public:
		SchedulerForm(void)
		{

			InitializeComponent();
			this->wdogs =( gcnew wdogcontrol());
			//this->wdogs->BackColor = System::Drawing::Color::Blue;
			this->wdogs->Location =  System::Drawing::Point(0, 300);
			this->wdogs->Name = "firstControl1";
			this->wdogs->Size =  System::Drawing::Size(75, 16);
			this->wdogs->TabIndex = 5;
			this->wdogs->Text = "Wacth DOG";
			this->Controls->Add(this->wdogs);
			//
			//TODO: aggiungere qui il codice del costruttore.
			//
			FasediConfigurazione();

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
		TabellaOrario ^tabellaOrario;
		phisicalTrainList ^listaTreni;
		TabellaStazioni ^tabItinerari;
		FormStatoLineaATC ^stATC;
		FormStatoLineaIXL ^stif ;
		ThreadListenerATC_IXL ^ThLATCIXL;
		ThreadPresentazione ^ThreadP;
		//ThreadSchedule ^ThSchedule;
		ThreadSchedulerSortedList ^ThScheduleSortedList;
		wdogcontrol ^wdogs;
		ConfigurazioneVelocita ^confVelocita;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;


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
				 this->button1->Enabled = false;
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
				 physicalTrain ^Treno = listaTreni->getPrimo();

				 try
				 {


					 Messaggi ^wakeUpPkt = gcnew Messaggi();


					 wakeUpPkt->setNID_MESSAGE(MessATO::UnconditionCommand);


					 wakeUpPkt->get_pacchettoCommandData()->setNID_PACKET(161);
					 wakeUpPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(WAKE_UP);
					 DateTime orarioSupporto3 = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);
					 TimeSpan ^sinceMidnight =  DateTime::Now - orarioSupporto3;
					 wakeUpPkt->setT_TIME((int)sinceMidnight->TotalSeconds/30);





					 // Buffer for reading data
					 array<Byte>^bytes_buffer1 =wakeUpPkt->serialize();


					 Messaggi ^trainRunningNumberPkt = gcnew Messaggi();


					 trainRunningNumberPkt->setNID_MESSAGE(MessATO::UnconditionCommand);
					 trainRunningNumberPkt->get_pacchettoCommandData()->setNID_PACKET(161);
					 trainRunningNumberPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(TRN);
					 trainRunningNumberPkt->setT_TIME((int)sinceMidnight->TotalSeconds/30);

					 trainRunningNumberPkt->get_pacchettoCommandData()->setNID_OPERATIONAL(tabellaOrario->getFirstTRN());


					 // Buffer for reading data
					 array<Byte>^bytes_buffer2 = trainRunningNumberPkt->serialize();

					 Messaggi ^missionPlanPkt = gcnew Messaggi();

					 missionPlanPkt->setNID_MESSAGE(MessATO::MissionPlan);
					 missionPlanPkt->get_pacchettoMissionData()->setNID_PACKET(160);
					 int TRN = tabellaOrario->getFirstTRN();
					 tabellaOrario->setMissionPlanMessage(TRN, missionPlanPkt->get_pacchettoMissionData(), confVelocita->getProfiloVelocita(TRN));



					 // Buffer for reading data
					 array<Byte>^bytes_buffer3 =  missionPlanPkt->serialize();

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
				 stATC->RequestStop();
				 stif->RequestStop() ;
				 ThLATCIXL->RequestStop();
				 ThreadP->RequestStop();

				// ThSchedule->RequestStop();
				 ThScheduleSortedList->RequestStop();
				 Application::Exit();
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(tabellaOrario->get_TabellaOrario()->Count<1){
					 MessageBox::Show("Tabella Orario Vuota");
#ifdef TRACE
					 Logger::Info("SchedulerForm"," Tabella Orario Vuota");  
#endif // TRACE
				 }else{
					 FormVisualizzeTabOrario ^formtb= gcnew FormVisualizzeTabOrario(tabellaOrario);
					 formtb->Visible=true;
				 }

			 }
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(tabItinerari->getMap()->Count<1){
					 MessageBox::Show("Tabella Conf Itinirari Vuota");
#ifdef TRACE
					 Logger::Info("SchedulerForm"," Tabella Conf Itinirari Vuota");  
#endif // TRACE
				 }else{

					 FormVisualizzeConfItine ^formCI = gcnew FormVisualizzeConfItine(tabItinerari);
					 formCI->Visible=true;

				 }

			 }
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {

				 if(tabItinerari->getMap()->Count<1){
					 MessageBox::Show("Tabella Conf Fermate Vuota");
#ifdef TRACE
					 Logger::Info("SchedulerForm"," Tabella Conf Fermate Vuota");  
#endif // TRACE
				 }else{
					 FormVisualizzeConfFermate ^formCF = gcnew FormVisualizzeConfFermate(tabItinerari);

					 formCF->Visible=true;

				 }

			 }

	private: void FasediConfigurazione(){
				 //
				 //Leggo dai file di configurazione le informazioni sugli itinerari, la tabella orario, le informazioni sulle stazioni e le informazioni sui treni
				 //
				 tabItinerari = gcnew TabellaStazioni();
				 tabItinerari->leggifileconfigurazioneItinerari();
				 tabItinerari->leggifileconfigurazioneFermate();

				 tabellaOrario  = gcnew TabellaOrario(tabItinerari);
				 tabellaOrario->leggiTabellaOrario();

				// tabfermate=gcnew tabellaFermate();
				// tabfermate->leggifileconfigurazioneFermate();

				 mapTrenoFisicoLogico ^mapsTrenoFisicoLogico = gcnew mapTrenoFisicoLogico();

				 confVelocita= gcnew ConfigurazioneVelocita();

				 Console::WriteLine(confVelocita->ToString());

				 listaTreni = gcnew phisicalTrainList();

				 //filtro osservabile dei messaggi dell'ATO
				 ManagerMsgATO ^manaStateATO = gcnew ManagerMsgATO();


				 ThreadP= gcnew ThreadPresentazione(listaTreni,manaStateATO);
				 //Thread TCP che ascolta i messaggi provenienti dall'ATO
				 Thread^ oThreadTCP_ATO = gcnew Thread( gcnew ThreadStart( ThreadP, &ThreadPresentazione::TCP_Management_receive ) );

				 oThreadTCP_ATO->Start();

				 //filtri osservabili per i messaggi provenienti rispettivamente da IXL e ATC
				 ManagerStatoLineaIXL ^manaStateIXL = gcnew ManagerStatoLineaIXL();
				 ManagerStatoLineaATC ^manaStateATC = gcnew ManagerStatoLineaATC();


				 ThLATCIXL= gcnew ThreadListenerATC_IXL(manaStateIXL,manaStateATC);

				 Thread^ oThreadUDP_ATC_IXL = gcnew Thread( gcnew ThreadStart(ThLATCIXL, &ThreadListenerATC_IXL::UDP_Management_receive ) );

				 oThreadUDP_ATC_IXL->Start();

				 EventQueue ^EventQIXL = gcnew EventQueue();
				 EventQIXL->Subscribe(manaStateIXL);
				 ////
				 EventQueue ^visualQIXL = gcnew EventQueue();
				 visualQIXL->Subscribe(manaStateIXL);
				 stif = gcnew FormStatoLineaIXL(visualQIXL);
				 stif->Visible=true;
				 Thread ^ oThreadformStatoI  = gcnew Thread( gcnew ThreadStart(stif,&FormStatoLineaIXL::aggiorna));
				 oThreadformStatoI->Start();
				 /////

				 ////
				 EventQueue ^visualQATC = gcnew EventQueue();
				 visualQATC->Subscribe(manaStateATC);
				 stATC = gcnew FormStatoLineaATC(visualQATC);
				 stATC->Visible=true;
				 Thread ^	 oThreadformStatoATC  = gcnew Thread( gcnew ThreadStart(stATC,&FormStatoLineaATC::aggiorna));
				 oThreadformStatoATC->Start();
				 /////
				 EventQueue ^EventQATC = gcnew EventQueue();
				 EventQATC->Subscribe(manaStateATC);

				 EventQueue ^EventQATO = gcnew EventQueue();

				 EventQATO->Subscribe(manaStateATO);
				 List<EventQueue^>^listqueue = gcnew List<EventQueue^>();
				 listqueue->Add(EventQIXL);
				 listqueue->Add(EventQATC);
				 listqueue->Add(EventQATO);


				/* ThSchedule =gcnew ThreadSchedule(listqueue,tabellaOrario,tabItinerari,mapsTrenoFisicoLogico, wdogs,manaStateATC, manaStateIXL, confVelocita);

				 Thread^	 oThreadSchedule  = gcnew Thread( gcnew ThreadStart(ThSchedule,&ThreadSchedule::SimpleSchedule));
				 oThreadSchedule->Start();*/

				  ThScheduleSortedList =gcnew ThreadSchedulerSortedList(listqueue,tabellaOrario,tabItinerari,mapsTrenoFisicoLogico, wdogs,manaStateATC, manaStateIXL, confVelocita);

				 Thread^	 oThreadSchedule  = gcnew Thread( gcnew ThreadStart(ThScheduleSortedList,&ThreadSchedulerSortedList::Schedule));
				 oThreadSchedule->Start();

			 }
	};


}
