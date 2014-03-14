﻿
#include "stdafx.h"
#include "stdafx.h"

using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace SchedulerATSTest {
	using namespace System;
	ref class MessaggiTest;


	/// <summary>
	///Classe di test per MessaggiTest.
	///Creata per contenere tutti gli unit test MessaggiTest
	///</summary>
	[TestClass]
	public ref class MessaggiTest
	{
	private: array<Byte>^fromString(String ^msg){
				 int len = ( msg->Length / 2)+(msg->Length%2);//+1;
				array<Byte>^sendBytes = gcnew array<Byte>(len);
				for (int i = 0; i < sendBytes->Length; i++)
				{
					String ^str = msg->Substring(i *2, 2);
					int h =str->Length;
					if(h>1){
						sendBytes[i] = Byte::Parse(str,System::Globalization::NumberStyles::HexNumber);
					}
				}
				return sendBytes;
			 };
	private: Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  testContextInstance;
			 /// <summary>
			 ///Ottiene o imposta il contesto dei test, che fornisce
			 ///funzionalità e informazioni sull'esecuzione dei test corrente.
			 ///</summary>
	public: property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  TestContext
			{
				Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  get()
				{
					return testContextInstance;
				}
				System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  value)
				{
					testContextInstance = value;
				}
			}

#pragma region Attributi di test aggiuntivi
			// 
			//Durante la scrittura dei test è possibile utilizzare i seguenti attributi aggiuntivi:
			//
			//Utilizzare ClassInitialize per eseguire il codice prima di eseguire il primo test della classe
			//public: [ClassInitialize]
			//static System::Void MyClassInitialize(TestContext^  testContext)
			//{
			//}
			//
			//Utilizzare ClassCleanup per eseguire il codice dopo l'esecuzione di tutti i test di una classe
			//public: [ClassCleanup]
			//static System::Void MyClassCleanup()
			//{
			//}
			//
			//Utilizzare TestInitialize per eseguire il codice prima di eseguire ciascun test
			//
			//public: [TestInitialize]
			//System::Void MyTestInitialize()
			//{
			//}
			//Utilizzare TestCleanup per eseguire il codice dopo l'esecuzione di ciascun test
			//public: [TestCleanup]
			//System::Void MyTestCleanup()
			//{
			//}
			//
#pragma endregion
			/// <summary>
			///Test per deserialize and serialize
			///</summary>
	public: [TestMethod]
			void deserializeAndReselalizzeTest()
			{
				//Deserializza MISSIONPLAN
				Messaggi^  target = (gcnew Messaggi(200)); 
				String ^msgMissPlan  = "C80CA00000E8B402F34000501227BA099CA83FE000A000066010440B478021E3C0000E40208407A03878F00003F0082105A81620F800012202D0416A0782F800004B849C105A82617B400016E1AF8416A0B8D2100006300AA105A83A23140001B801908348";
				array<Byte>^Bytesd = fromString(msgMissPlan);
				target->deserialize(Bytesd);
				String ^expected = "NID_MESSAGE 200;L_MESSAGE 101;T_TRAIN 1861;NID_PACKET: 160;L_PACKET: 755;Q_SCALE: 1;D_MISSION: 0;V_MISSION: 80;N_ITER1: 2;D_MISSION: 8827;V_MISSION: 80;D_MISSION: 9842;V_MISSION: 80;T_START_TIME: 2044;NID_LRGB: 102;D_LRGB: 10;D_STOP: 130;Q_DOORS: 2;T_DOORS_TIME: 90;N_ITER2: 7;T_START_TIME: 2050;NID_LRGB: 114;D_LRGB: 3870;D_STOP: 130;Q_DOORS: 1;T_DOORS_TIME: 30;T_START_TIME: 2062;NID_LRGB: 126;D_LRGB: 3870;D_STOP: 130;Q_DOORS: 1;T_DOORS_TIME: 90;T_START_TIME: 2070;NID_LRGB: 145;D_LRGB: 4220;D_STOP: 180;Q_DOORS: 1;T_DOORS_TIME: 90;T_START_TIME: 2078;NID_LRGB: 151;D_LRGB: 1520;D_STOP: 1180;Q_DOORS: 1;T_DOORS_TIME: 90;T_START_TIME: 2086;NID_LRGB: 183;D_LRGB: 3034;D_STOP: 1726;Q_DOORS: 1;T_DOORS_TIME: 90;T_START_TIME: 2094;NID_LRGB: 198;D_LRGB: 6722;D_STOP: 170;Q_DOORS: 1;T_DOORS_TIME: 90;T_START_TIME: 2106;NID_LRGB: 220;D_LRGB: 4490;D_STOP: 100;Q_DOORS: 2;T_DOORS_TIME: 210;";
				
				Assert::AreEqual(target->ToString(),expected);
				//Serializza MISSIONPLAN
				array<Byte>^Bytess =  target->serialize();
			
				CollectionAssert::AreEqual(Bytesd,Bytess);
				//Deserializza STATOLINEAIXL
				Messaggi^  statolinea = (gcnew Messaggi(1)); 
				String ^msgstatolinea  = "0184BFFFFFFFE01465000001901008F0000019110000019210000019310000019410000019510000019610000019710000019810000019910000019A10000019B10000019C10000019D10000019E10000019F1000001A01000001A11000001A21000001A31000001A41000001A51000001A61000001A71000001A81000001A91000001AA1000001AB1000001AC1000001AD1000001B81000001B91000001BA1000001BB1000001BC1000001BD1000001BE1000001BF1000001C01000001C11000001F51000001F61000001F71000001F81000001F910000271A10000271B10000271C10000271D10000283D10000283E100002B02100002B03100002B04100002B05100002B0C100002B0D100002B0E100002B0F100002C25100002C26100002EEA100002EEB100002EEC100002EED100002EEE100002EEF100002EF0100002EF4100002EF5100002EF6100002EF7100002EF8100002EF9100002EFA10000300D10000300E10000300F1000032D21000032D31000032D41000033F51000033F61000036BA1000036BB1000036BC1000036C41000036C51000036C61000037DD1000037DE100003AA2100003AA3100003AA4100003AAC100003AAD100003AAE100003BC5100003BC6100003E8A100003E8B100003E8C100003E8D100003E8E100003E8F100003E90100003E91100003E94100003E9B100003E96100003E97100003E98100003E95100003E99100003E9A100003FAD100003FAE100003FAF10000427210000427310000427410000427510000427610000427710000427810000427910000427A10000427B10000427C10000428610000428710000428810000428910000428A10000428B10000428C10000428D10000428E10000428F1000042901000043951000043961000043971000043981044FC800013BA04010C00009DD4200004EEC2000027770800015AE080000AD742000056BC100002B5F0800015B0040000AD844000056C4100002B630800017A2080000BD14200005E8C100002F470800017A4040000BD24400005E94200002F4B0800017A6040000BD34200005E9C100002F4F1000017A8040000BD4420000665810000332D080001997080000CCBC200006E28200003715080001B8B040000DC5C200006E30100003719100001B8D040000DC6C2000075F8200003AFD080001D7F040000EBFC200007600100003B01100001D81040000EC0C200007DC8100003EE5080001F73080000FB9C200007DD0100003EE9080001F75040000FBAC400007DD8200003EED080001F77040000FBBC200007DE0100003EF11000021660400010B3440000859C1000042CF0800021680800010B442000085A41000042D30828A240000D49100110000390B40000E4310000296C40000F3CD00003CF440000B55500002D5640000C4F50000313E40000C4FD00003140400010379000040DF400010381000040E1400011319000044C74180";
				array<Byte>^bbytesd = fromString(msgstatolinea);
				statolinea->deserialize(bbytesd);
				expected = "NID_MESSAGE 1;L_MESSAGE 1061;T_TRAIN -1;NID_PACKET: 0;L_PACKET: 5221;NID_CDB: 400;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;N_ITER: 143;NID_CDB: 401;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 402;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 403;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 404;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 405;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 406;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 407;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 408;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 409;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 410;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 411;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 412;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 413;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 414;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 415;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 416;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 417;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 418;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 419;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 420;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 421;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 422;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 423;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 424;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 425;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 426;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 427;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 428;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 429;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 440;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 441;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 442;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 443;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 444;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 445;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 446;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 447;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 448;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 449;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 501;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 502;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 503;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 504;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 505;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 10010;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 10011;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 10012;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 10013;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 10301;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 10302;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 11010;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 11011;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 11012;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 11013;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 11020;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 11021;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 11022;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 11023;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 11301;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 11302;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12010;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12011;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12012;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12013;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12014;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12015;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12016;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12020;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12021;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12022;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12023;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12024;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12025;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12026;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12301;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12302;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 12303;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 13010;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 13011;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 13012;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 13301;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 13302;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 14010;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 14011;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 14012;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 14020;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 14021;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 14022;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 14301;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 14302;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 15010;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 15011;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 15012;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 15020;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 15021;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 15022;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 15301;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 15302;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16010;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16011;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16012;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16013;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16014;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16015;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16016;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16017;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16020;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16027;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16022;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16023;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16024;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16021;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16025;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16026;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16301;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16302;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 16303;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17010;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17011;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17012;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17013;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17014;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17015;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17016;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17017;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17018;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17019;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17020;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17030;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17031;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17032;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17033;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17034;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17035;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17036;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17037;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17038;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17039;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17040;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17301;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17302;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17303;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_CDB: 17304;Q_STATOCDB: 0;Q_DEVIATIOIO: 1;NID_PACKET: 4;L_PACKET: 2553;NID_SEGN: 10100;Q_STATOSEGN: 1;N_ITER: 67;NID_SEGN: 10101;Q_STATOSEGN: 1;NID_SEGN: 10102;Q_STATOSEGN: 2;NID_SEGN: 10103;Q_STATOSEGN: 1;NID_SEGN: 11100;Q_STATOSEGN: 2;NID_SEGN: 11101;Q_STATOSEGN: 1;NID_SEGN: 11102;Q_STATOSEGN: 1;NID_SEGN: 11103;Q_STATOSEGN: 1;NID_SEGN: 11104;Q_STATOSEGN: 1;NID_SEGN: 11105;Q_STATOSEGN: 2;NID_SEGN: 11106;Q_STATOSEGN: 1;NID_SEGN: 11107;Q_STATOSEGN: 1;NID_SEGN: 12100;Q_STATOSEGN: 2;NID_SEGN: 12101;Q_STATOSEGN: 1;NID_SEGN: 12102;Q_STATOSEGN: 1;NID_SEGN: 12103;Q_STATOSEGN: 1;NID_SEGN: 12104;Q_STATOSEGN: 1;NID_SEGN: 12105;Q_STATOSEGN: 2;NID_SEGN: 12106;Q_STATOSEGN: 2;NID_SEGN: 12107;Q_STATOSEGN: 1;NID_SEGN: 12108;Q_STATOSEGN: 1;NID_SEGN: 12109;Q_STATOSEGN: 1;NID_SEGN: 12110;Q_STATOSEGN: 1;NID_SEGN: 12111;Q_STATOSEGN: 2;NID_SEGN: 12112;Q_STATOSEGN: 1;NID_SEGN: 12113;Q_STATOSEGN: 1;NID_SEGN: 13100;Q_STATOSEGN: 1;NID_SEGN: 13101;Q_STATOSEGN: 1;NID_SEGN: 13102;Q_STATOSEGN: 2;NID_SEGN: 13103;Q_STATOSEGN: 1;NID_SEGN: 14100;Q_STATOSEGN: 2;NID_SEGN: 14101;Q_STATOSEGN: 1;NID_SEGN: 14102;Q_STATOSEGN: 1;NID_SEGN: 14103;Q_STATOSEGN: 1;NID_SEGN: 14104;Q_STATOSEGN: 1;NID_SEGN: 14105;Q_STATOSEGN: 2;NID_SEGN: 14106;Q_STATOSEGN: 1;NID_SEGN: 14107;Q_STATOSEGN: 1;NID_SEGN: 15100;Q_STATOSEGN: 2;NID_SEGN: 15101;Q_STATOSEGN: 1;NID_SEGN: 15102;Q_STATOSEGN: 1;NID_SEGN: 15103;Q_STATOSEGN: 1;NID_SEGN: 15104;Q_STATOSEGN: 1;NID_SEGN: 15105;Q_STATOSEGN: 2;NID_SEGN: 15106;Q_STATOSEGN: 1;NID_SEGN: 15107;Q_STATOSEGN: 1;NID_SEGN: 16100;Q_STATOSEGN: 1;NID_SEGN: 16101;Q_STATOSEGN: 1;NID_SEGN: 16102;Q_STATOSEGN: 2;NID_SEGN: 16103;Q_STATOSEGN: 1;NID_SEGN: 16104;Q_STATOSEGN: 1;NID_SEGN: 16105;Q_STATOSEGN: 1;NID_SEGN: 16106;Q_STATOSEGN: 1;NID_SEGN: 16107;Q_STATOSEGN: 2;NID_SEGN: 16108;Q_STATOSEGN: 2;NID_SEGN: 16109;Q_STATOSEGN: 1;NID_SEGN: 16110;Q_STATOSEGN: 1;NID_SEGN: 16111;Q_STATOSEGN: 1;NID_SEGN: 16112;Q_STATOSEGN: 1;NID_SEGN: 16113;Q_STATOSEGN: 2;NID_SEGN: 17100;Q_STATOSEGN: 1;NID_SEGN: 17101;Q_STATOSEGN: 2;NID_SEGN: 17102;Q_STATOSEGN: 1;NID_SEGN: 17103;Q_STATOSEGN: 1;NID_SEGN: 17104;Q_STATOSEGN: 2;NID_SEGN: 17105;Q_STATOSEGN: 1;NID_SEGN: 17106;Q_STATOSEGN: 1;NID_SEGN: 17107;Q_STATOSEGN: 1;NID_PACKET: 5;L_PACKET: 649;NID_BLOCCO: 13604;Q_STATOBLOCCO: 1;N_ITER: 17;NID_BLOCCO: 14603;Q_STATOBLOCCO: 1;NID_BLOCCO: 14604;Q_STATOBLOCCO: 1;NID_BLOCCO: 10604;Q_STATOBLOCCO: 1;NID_BLOCCO: 15603;Q_STATOBLOCCO: 1;NID_BLOCCO: 15604;Q_STATOBLOCCO: 1;NID_BLOCCO: 11605;Q_STATOBLOCCO: 1;NID_BLOCCO: 11606;Q_STATOBLOCCO: 1;NID_BLOCCO: 12605;Q_STATOBLOCCO: 1;NID_BLOCCO: 12606;Q_STATOBLOCCO: 1;NID_BLOCCO: 12607;Q_STATOBLOCCO: 1;NID_BLOCCO: 12608;Q_STATOBLOCCO: 1;NID_BLOCCO: 16606;Q_STATOBLOCCO: 1;NID_BLOCCO: 16607;Q_STATOBLOCCO: 1;NID_BLOCCO: 16608;Q_STATOBLOCCO: 1;NID_BLOCCO: 16609;Q_STATOBLOCCO: 1;NID_BLOCCO: 17606;Q_STATOBLOCCO: 1;NID_BLOCCO: 17607;Q_STATOBLOCCO: 1;NID_PACKET: 6;";
				Assert::AreEqual(statolinea->ToString(),expected);
				//Serializza STATOLINEAIXL
				Bytess =  statolinea->serialize();
				String ^hex = BitConverter::ToString(Bytess);	
				CollectionAssert::AreEqual(bbytesd,Bytess);

				//Deserializza STATOLINEAATC
				Messaggi^  statolineaatc = (gcnew Messaggi(11)); 
				String ^msgstatolineaatc  ="0B0A8000000411A265000000000000000000000000000500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
				bbytesd = fromString(msgstatolineaatc);
				statolineaatc->deserialize(bbytesd);
				expected = "NID_MESSAGE 11;L_MESSAGE 84;T_TRAIN 32;NID_PACKET: 141;L_PACKET: 613;NID_CDB: 0;Q_STATOCDB: 1;Q_DEVIATIOIO: 4;N_ITER: 5;NID_CDB: 0;Q_STATOCDB: 1;Q_DEVIATIOIO: 4;NID_CDB: 0;Q_STATOCDB: 1;Q_DEVIATIOIO: 4;NID_CDB: 0;Q_STATOCDB: 1;Q_DEVIATIOIO: 4;NID_CDB: 0;Q_STATOCDB: 1;Q_DEVIATIOIO: 4;NID_CDB: 0;Q_STATOCDB: 1;Q_DEVIATIOIO: 4;";
				Assert::AreEqual(statolineaatc->ToString(),expected);
				//Serializza STATOLINEAATC
				Bytess =  statolineaatc->serialize();
				hex = BitConverter::ToString(Bytess);	
				CollectionAssert::AreEqual(bbytesd,Bytess);

				//Deserializza Presentazione
				Messaggi^  Presentazione = (gcnew Messaggi(215)); 
				String ^msgPresentazione  ="D702200002B6602009E32035000E1C0000";
				bbytesd = fromString(msgPresentazione);
				Presentazione->deserialize(bbytesd);
				expected = "NID_MESSAGE 215;L_MESSAGE 17;T_TRAIN 5555;NID_ENGINE 65615;NID_PACKET: 25;L_PACKET: 53;M_PORT: 3612;";
				Assert::AreEqual(Presentazione->ToString(),expected);
				//Serializza Presentazione
				Bytess =  Presentazione->serialize();
				hex = BitConverter::ToString(Bytess);	
				CollectionAssert::AreEqual(bbytesd,Bytess);

				//Deserializza wakeup
				Messaggi^  wakeup = (gcnew Messaggi(201)); 
				String ^msgwakeup  ="C901400000FB14201800";
				bbytesd = fromString(msgwakeup);
				wakeup->deserialize(bbytesd);
				expected = "NID_MESSAGE 201;L_MESSAGE 10;T_TRAIN 2008;NID_PACKET 161;L_PACKET 24;Q_COMMAND_TYPE 0;";
				Assert::AreEqual(wakeup->ToString(),expected);
				//Serializza wakeup
				Bytess =  wakeup->serialize();
				hex = BitConverter::ToString(Bytess);	
				CollectionAssert::AreEqual(bbytesd,Bytess);


				//Deserializza TRN
				Messaggi^  trn = (gcnew Messaggi(201)); 
				String ^msgtrn  ="C901C00000FB14203880000092A0";
				bbytesd = fromString(msgtrn);
				trn->deserialize(bbytesd);
				expected = "NID_MESSAGE 201;L_MESSAGE 14;T_TRAIN 2008;NID_PACKET 161;L_PACKET 56;Q_COMMAND_TYPE 4;";
				Assert::AreEqual(trn->ToString(),expected);
				//Serializza trn
				Bytess =  trn->serialize();
				hex = BitConverter::ToString(Bytess);	
				CollectionAssert::AreEqual(bbytesd,Bytess);


				
				//Deserializza missionpln con n_iter1 sbagliato
				Messaggi^  missionpln = (gcnew Messaggi(200)); 
				String ^msgmissionpln  ="C80AC00000FB14027554E646E1EA000A0000DD0104247463FC2120000188020888E90905C900005C06BE123A44C0F7C000130127048E91D009B00004680A5123A49C249A000146020888E93108AC0000580064123A00";
				bbytesd = fromString(msgmissionpln);
			
				missionpln->deserialize(bbytesd);
				Assert::IsTrue(true, "Exception was properly thrown");
			//	}
			//	expected = "NID_MESSAGE 200;L_MESSAGE 86;T_TRAIN 2008;NID_PACKET: 160;L_PACKET: 629;Q_SCALE: 1;D_MISSION: 10700;V_MISSION: 70;N_ITER1: 0;T_START_TIME: 980;NID_LRGB: 221;D_LRGB: 10;D_STOP: 130;Q_DOORS: 1;T_DOORS_TIME: 570;N_ITER2: 6;T_START_TIME: 1020;NID_LRGB: 196;D_LRGB: 4240;D_STOP: 130;Q_DOORS: 2;T_DOORS_TIME: 570;T_START_TIME: 1060;NID_LRGB: 184;D_LRGB: 2962;D_STOP: 1726;Q_DOORS: 1;T_DOORS_TIME: 570;T_START_TIME: 1100;NID_LRGB: 152;D_LRGB: 1982;D_STOP: 1180;Q_DOORS: 1;T_DOORS_TIME: 570;T_START_TIME: 1140;NID_LRGB: 141;D_LRGB: 310;D_STOP: 165;Q_DOORS: 1;T_DOORS_TIME: 570;T_START_TIME: 1180;NID_LRGB: 163;D_LRGB: 4685;D_STOP: 130;Q_DOORS: 2;T_DOORS_TIME: 570;T_START_TIME: 1220;NID_LRGB: 176;D_LRGB: 4440;D_STOP: 100;Q_DOORS: 1;T_DOORS_TIME: 570;";
			//	Assert::AreEqual(missionpln->ToString(),expected);
				//Serializza missionpln
			//	Bytess =  missionpln->serialize();
			//	hex = BitConverter::ToString(Bytess);	
			//	CollectionAssert::AreEqual(bbytesd,Bytess);
				//

				//Deserializza ack
				Messaggi^  ack = (gcnew Messaggi(210)); 
				String ^msgack  ="D20220000004002009F440360000000C80";
				bbytesd = fromString(msgack);
				ack->deserialize(bbytesd);
				expected = "NID_MESSAGE 210;L_MESSAGE 17;T_TRAIN 32;NID_ENGINE 65615;NID_PACKET: 162;L_PACKET: 54;T_TRAIN: 12;Q_MISSION_RESPONSE: 1;";
				Assert::AreEqual(ack->ToString(),expected);
				//Serializza ack
				Bytess =  ack->serialize();
				hex = BitConverter::ToString(Bytess);	
				CollectionAssert::AreEqual(bbytesd,Bytess);
				
				//
				//Deserializza cmdixl
				Messaggi^  cmdixl = (gcnew Messaggi(10)); 
				String ^msgcmdixl  ="0A01E00000FB014037000045F9BFC0";
				bbytesd = fromString(msgcmdixl);
				cmdixl->deserialize(bbytesd);
				expected = "NID_MESSAGE 10;L_MESSAGE 15;T_TRAIN 2008;NID_PACKET: 10;L_PACKET: 55;NID_ITIN: 17913;Q_CMDITIN: 2;NID_PACKET: 255;";
				Assert::AreEqual(cmdixl->ToString(),expected);
				//Serializza cmdixl
				Bytess =  cmdixl->serialize();
				hex = BitConverter::ToString(Bytess);	
				CollectionAssert::AreEqual(bbytesd,Bytess);

				//E701E0000003218037000001007FC0

				//Deserializza cmdblocco
				Messaggi^  cmdblocco = (gcnew Messaggi(231)); 
				String ^msgcmdblocco  ="E701E0000003218037000001007FC0";
				bbytesd = fromString(msgcmdblocco);
				cmdblocco->deserialize(bbytesd);
				expected = "NID_MESSAGE 231;L_MESSAGE 15;T_TRAIN 25;NID_PACKET: 12;L_PACKET: 55;NID_BLOCCO: 256;Q_CMDBLOCCO: 1;NID_PACKET: 255;";
				Assert::AreEqual(cmdblocco->ToString(),expected);
				//Serializza cmdblocco
				Bytess =  cmdblocco->serialize();
				hex = BitConverter::ToString(Bytess);	
				CollectionAssert::AreEqual(bbytesd,Bytess);


				
				//Deserializza fault
				Messaggi^  mfault = (gcnew Messaggi(211)); 
				String ^msgmfault  ="D301800002B6602026E32000";
				bbytesd = fromString(msgmfault);
				mfault->deserialize(bbytesd);
				expected = "NID_MESSAGE 211;L_MESSAGE 12;T_TRAIN 5555;NID_PACKET: 1;L_PACKET: 38;NID_COMPONENT: 14;M_FAULT: 50;N_ITER: 0;";
				Assert::AreEqual(mfault->ToString(),expected);
				//Serializza fault
				Bytess =  mfault->serialize();
				hex = BitConverter::ToString(Bytess);	
				CollectionAssert::AreEqual(bbytesd,Bytess);

				//Deserializza nulla
				String ^msgnull  ="000000000000000000000000000000";
				bbytesd = fromString(msgnull);
				Messaggi^ msgnul = (gcnew Messaggi()); 
				msgnul->deserialize(bbytesd);

			}

			/// <summary>
			///Test per getSize
			///</summary>
public: [TestMethod]
		void getSizeTest()
		{
			Messaggi^  target = (gcnew Messaggi()); 
			int expected = 7; 
			int actual;
			actual = target->getSize();
			Assert::AreEqual(expected, actual);

			target = (gcnew Messaggi(211)); 
			expected = 12; 
			actual = target->getSize();
			Assert::AreEqual(expected, actual);


		}
};
}
namespace SchedulerATSTest {

}
