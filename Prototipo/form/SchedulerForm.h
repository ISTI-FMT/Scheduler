#pragma once
#include "..\\tabellaOrario\\TabellaOrario.h"
#using <System.dll>
#include "..\\utility.h"

#include "..\\phisicalTrainList.h"
#include "..\\threads\\ThreadListenerATC_IXL.h"
#include <iostream>
#include "..\\threads\\ThreadPresentazione.h"
#include "..\\mapTrenoFisicoLogico.h"
#include "..\\messaggi\\Messaggi.h"
#include "..\\logger\\Logger.h"
#include "..\\Itinerari\\tabellaItinerari.h"

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

			tabellaItinerari ^tb = gcnew tabellaItinerari();
			tb->leggifileconfigurazioneItinerari("..\\FileConfigurazione\\ConfigurazioneItinerari.xml");

			Console::WriteLine(tb->ToString());

			listaTreni = gcnew phisicalTrainList();


			ThreadPresentazione ^sd = gcnew ThreadPresentazione(listaTreni);


			oThread2 = gcnew Thread( gcnew ThreadStart(sd, &ThreadPresentazione::TCP_Management_receive ) );

			oThread2->Start();

			oThread1 = gcnew Thread( gcnew ThreadStart( &ThreadListenerATC_IXL::UDP_Management_receive ) );

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
	private: System::Windows::Forms::Button^  button2;
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
				 // SchedulerForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(408, 332);
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
				 }


			 }
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

				 if(!listaTreni->is_Empthy()){
					 Thread  ^oThread = gcnew Thread( gcnew ThreadStart(this, &Prototipo::SchedulerForm::TCP_Management) );

					 oThread->Start();

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
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

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
				 dataGridView1->Size = System::Drawing::Size(671, 344);
				 dataGridView1->TabIndex = 8;

				 form = gcnew Form();
				 form->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 form->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 form->ClientSize = System::Drawing::Size(730, 415);
				 form->Controls->Add(dataGridView1);
				 form->Name = L"Tabella Orario";
				 form->Text = L"Tabella Orario";
				 form->ResumeLayout(false);
				 form->PerformLayout();
				 form->SuspendLayout();

				 dataGridView1->ColumnCount = 7;
				 dataGridView1->RowCount = tabella->get_TabellaOrario()->Count*8;
				 int colonna=0;
				 int riga=0;
				 dataGridView1->Columns[ 0 ]->Name = "Id_Treno";
				 dataGridView1->Columns[ 1 ]->Name = "None Stazione";
				 dataGridView1->Columns[ 2 ]->Name = "Orario Arrivo";
				 dataGridView1->Columns[ 3 ]->Name = "Orario Partenza";
				 dataGridView1->Columns[ 4 ]->Name = "BinProg";
				 dataGridView1->Columns[ 5 ]->Name = "TempoMAPorte";
				 dataGridView1->Columns[ 6 ]->Name = "LatoAPorte";

				 for each( KeyValuePair<int , List<Fermata^>^> kvp in tabella->get_TabellaOrario() )
				 {

					 String ^po=kvp.Key+"\n\r";
					 dataGridView1->Rows[riga]->Cells[0]->Value=po;


					 for each (Fermata ^dvar in kvp.Value)
					 {
						 dataGridView1->Rows[riga]->Cells[1]->Value=dvar->getIdStazione();
						 TimeSpan Arrivo = TimeSpan::FromSeconds(dvar->getOrarioArrivo()*30);
						 dataGridView1->Rows[riga]->Cells[2]->Value= Arrivo.ToString();
						 TimeSpan Partenza = TimeSpan::FromSeconds(dvar->getOrarioPartenza()*30);
						 dataGridView1->Rows[riga]->Cells[3]->Value=Partenza.ToString();
						 dataGridView1->Rows[riga]->Cells[4]->Value=dvar->getBinarioProgrammato();
						 dataGridView1->Rows[riga]->Cells[5]->Value=dvar->gettempoMinimoAperturaPorte();
						 dataGridView1->Rows[riga]->Cells[6]->Value=dvar->getLatoAperturaPorte();
						 riga++;
					 }

				 }


				 form->Visible=true;

			 }
	};


}
