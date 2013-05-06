#pragma once
#include "tabellaOrario\\TabellaOrario.h"
#using <System.dll>
#include "utility.h"

#include "phisicalTrainList.h"
#include "String2string.h"
#include "threads\\ThreadListenerATC.h"
#include <iostream>
#include "threads\\ThreadPresentazione.h"
#include "mapTrenoFisicoLogico.h"
#include "messaggi\\Messaggi.h"
#include "logger\\Logger.h"

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
			tabella  = gcnew TabellaOrario;
			tabella->leggiTabellaOrario("..\\FileConfigurazione\\TabellaOrario.xml");



			listaTreni = gcnew phisicalTrainList();


			ThreadPresentazione ^sd = gcnew ThreadPresentazione(listaTreni);


			 oThread2 = gcnew Thread( gcnew ThreadStart(sd, &ThreadPresentazione::TCP_Management_receive ) );

			oThread2->Start();

			 oThread1 = gcnew Thread( gcnew ThreadStart( &ThreadListenerATC::UDP_Management_receive ) );

			oThread1->Start();


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
		Thread^ oThread1;
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
			// SchedulerForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(408, 332);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->ExitButton);
			this->Name = L"SchedulerForm";
			this->Text = L"SchedulerForm";
			this->ResumeLayout(false);

		}
		void TCP_Management(phisicalTrain ^Treno, TabellaOrario ^tabella)
		{
			try
			{


				Messaggi ^wakeUpPkt = gcnew Messaggi();


				wakeUpPkt->setNID_MESSAGE(201);


				wakeUpPkt->get_pacchettoCommandData()->setNID_PACKET(161);
				wakeUpPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(WAKE_UP);
				wakeUpPkt->setT_TRAIN(tabella->getFirstTRN());





				// Buffer for reading data
				array<Byte>^bytes_buffer1 = gcnew array<Byte>(wakeUpPkt->getSize());

				wakeUpPkt->serialize(bytes_buffer1);


				Messaggi ^trainRunningNumberPkt = gcnew Messaggi();


				trainRunningNumberPkt->setNID_MESSAGE(201);
				trainRunningNumberPkt->get_pacchettoCommandData()->setNID_PACKET(161);
				trainRunningNumberPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(TRN);
				trainRunningNumberPkt->setT_TRAIN(tabella->getFirstTRN());
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
			}
			catch ( SocketException^ e ) 
			{
				Console::WriteLine( "SocketException: {0}", e );
			}


		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

				 if(!listaTreni->is_Empthy()){
					 TCP_Management(listaTreni->getPrimo(), tabella);
				 }else{

#ifdef TRACE
					 Trace::WriteLine("Lista treni Vuota");  
#endif // TRACE

					 MessageBox::Show("Lista treni Vuota");
				 }


			 }
	private: System::Void ExitButton_Click(System::Object^  sender, System::EventArgs^  e) {

				 oThread1->Abort();
				 oThread2->Abort();
				 Application::Exit();
			 }
};


}