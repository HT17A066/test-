// -*- C++ -*-
/*!
 * @file  Testplus.cpp
 * @brief data transmission
 * @date $Date$
 *
 * $Id$
 */

#include "Testplus.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>

#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <map>

using namespace std;

int index = 0; 


// Module specification
// <rtc-template block="module_spec">
static const char* testplus_spec[] =
  {
    "implementation_id", "Testplus",
    "type_name",         "Testplus",
    "description",       "data transmission",
    "version",           "1.0.0",
    "vendor",            "Sawasaki",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.NUM_ACTUATOR", "5",
    // Widget
    "conf.__widget__.NUM_ACTUATOR", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Testplus::Testplus(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_incoorIn("InCoor", m_incoor),
    m_indataIn("InData", m_indata),
    m_outcoorOut("OutCoor", m_outcoor),
    m_outdataOut("OutData", m_outdata)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Testplus::~Testplus()
{
}



RTC::ReturnCode_t Testplus::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("InCoor", m_incoorIn);
  addInPort("InData", m_indataIn);
  
  // Set OutPort buffer
  addOutPort("OutCoor", m_outcoorOut);
  addOutPort("OutData", m_outdataOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("NUM_ACTUATOR", m_NUM_ACTUATOR, "5");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Testplus::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Testplus::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Testplus::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Testplus::onActivated(RTC::UniqueId ec_id)
{
	m_outdata.data.length(m_NUM_ACTUATOR+1);
	for (int i=0; i < m_outdata.data.length(); i++){ m_outdata.data[i] = 0.0; }

	m_outcoor.data.length(6); 
	for (int i=0; i < m_outcoor.data.length(); i++){ m_outcoor.data[i] = 0.0; }

  return RTC::RTC_OK;
}


RTC::ReturnCode_t Testplus::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Testplus::onExecute(RTC::UniqueId ec_id)
{
	//double m_Id_Data =Id_Data.data;
	int i, time = 0;
	double time_cin =0.0;
	int select = 0;
	//static int Num = 1;
	double test[2] = { 0.5, -0.5 };
	double rad[5];
	double xyzr[6];

	printf("�e�X�g����\n�A�[���̑�����w�肵�Ă�������\n0:���� 1:�������@2:����Ȃ�@3:����\n");
	printf("4:���� 5:���^���w 6:�t�^���w\n");
	printf("�ԍ� = ");
	scanf("%d", &select);

	/*
	if( Num == 1 ){
		Num = 2;
	}else{
		Num = 1;
	}
	*/

	//test outdata(ok)
	/*
	if (select == 0){
		for( i=0; i<m_NUM_ACTUATOR; i++ ){ m_outdata.data[i] = 0.0; }
		m_outdata.data[m_NUM_ACTUATOR] = 3.0;
		cout << "outdata = 0.0" << endl;
		m_outdataOut.write();
	}else{
		for( i=0; i<m_NUM_ACTUATOR; i++ ){ m_outdata.data[i] = 11.11; }
		m_outdata.data[m_NUM_ACTUATOR] = 11.11;
		cout << "outdata = 11.11" << endl;
		m_outdataOut.write();
	}
	*/


	///*
	switch( select ){
	case 0:
		for(i=0; i<m_NUM_ACTUATOR; i++){
			m_outdata.data[i] = 0.0;
		}
		m_outdata.data[1] = 1.57;
		m_outdata.data[m_NUM_ACTUATOR] = 3.0;

		break;
	case 1:
		for(i=0; i<m_NUM_ACTUATOR; i++){
			m_outdata.data[i] = test[index];
		}
		m_outdata.data[m_NUM_ACTUATOR] = 5.0;
		break;
	case 2:
		for(i=0; i<m_NUM_ACTUATOR; i++){
			m_outdata.data[i] = test[index];
		}
		m_outdata.data[m_NUM_ACTUATOR] = 3.0;
		break;
	case 3:
		for(i=0; i<m_NUM_ACTUATOR; i++){
			m_outdata.data[i] = test[index];
		}
		m_outdata.data[m_NUM_ACTUATOR] = 1.0;
		break;
	case 4:
		printf("\n���Ԃ��w�肵�Ă�������(�b) : ");
		//scanf("%f", &time_cin);
		cin >> time_cin;
		
		for(i=0; i<m_NUM_ACTUATOR; i++){
			m_outdata.data[i] = test[index];
		}
		m_outdata.data[m_NUM_ACTUATOR] = time_cin;
		break;
	case 5:
		printf("\n�T�[�{ID : 1 �̒l�����[rad] : ");
		//scanf("%f", &rad[0]);
		cin >> rad[0];

		printf("\n�T�[�{ID : 2 �̒l�����[rad] : ");
		cin >> rad[1];
		
		printf("\n�T�[�{ID : 3 �̒l�����[rad] : ");
		cin >> rad[2];
		
		printf("\n�T�[�{ID : 4 �̒l�����[rad] : ");
		cin >> rad[3];

		printf("\n�T�[�{ID : 5 �̒l�����[rad] : ");
		cin >> rad[4];

		for(i=0; i < m_NUM_ACTUATOR; i++)
		{
			m_outdata.data[i] = rad[i];
		}
		m_outdata.data[m_NUM_ACTUATOR] = 3.0;
		break;

	case 6:
		printf("\nx���̒l����͂��Ă������� : ");
		//scanf("%f", &xyzr[0]);
		cin >> xyzr[0];

		printf("\ny���̒l����͂��Ă������� : ");
		cin >> xyzr[1];
		
		printf("\nz���̒l����͂��Ă������� : ");
		
		cin >> xyzr[2];
		printf("\n��[rad]����͂��Ă������� : ");
		
		cin >> xyzr[3];

		printf("\n�n���h�̊J����͂��Ă�������(0:close, 1:open) : ");
		cin >> xyzr[4];

		printf("\n���Ԃ��w�肵�Ă�������(�b) : ");
		cin >> xyzr[5];

		for(i=0; i < 6; i++){
			m_outcoor.data[i] = xyzr[i];
		}
		break;

	default:
		cout << "1�`6��I�����Ă�������" << endl;
		for (int i=0; i < m_outdata.data.length(); i++){ m_outdata.data[i] = 0.0; }
		m_outdata.data[3] = 1.57;
		m_outdata.data[m_NUM_ACTUATOR] = 1.0;

		break;
	}
	if( select == 6 ){
		cout << "\n�t�^���w�œ������܂�\n";
		/*
		for(int i=0; i<6; i++)
		{
			cout << "\nm_outcoor[" << i << "] : " << m_outcoor.data[i];
		}
		cout << endl;
		cout << endl;
		*/
		m_outcoorOut.write();
	}else{
		cout << "\n�e�T�[�{��[rad]�l��time[s]�𑗐M���܂�\n";
		/*
		for(int i=0; i<m_NUM_ACTUATOR+1; i++)
		{
			cout << "\nm_outdata[" << i << "] : " << m_outdata.data[i];
		}
		cout << endl;
		cout << endl;
		*/
		m_outdataOut.write();
	}
	
	// Change goal position
	if (index == 0) { index = 1; }
	else { index = 0; }

	if( m_indataIn.isNew() )
	{
		m_indataIn.read();
		printf("���쌋�� : �e�T�[�{��[rad]�l�Ǝ���[s]���󂯎��܂���\n");
		for(i=0; i<m_NUM_ACTUATOR; i++)
			printf("ID:%d : %f [rad] \n",i+1,m_indata.data[i]);
		printf("\n");
	}

	//
	if( m_incoorIn.isNew() )
	{
		m_incoorIn.read();
		cout << "���쌋��(���W : xyz��)\n";
		cout << "x = " << m_incoor.data[0];
		cout << "\ny = " << m_incoor.data[1];
		cout << "\nz = " << m_incoor.data[2];
		cout << "\n�� = " << m_incoor.data[3];
		//cout << "\ntime[s] = " << m_incoor.data[4];
	}
	//*/

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Testplus::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Testplus::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Testplus::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Testplus::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Testplus::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void TestplusInit(RTC::Manager* manager)
  {
    coil::Properties profile(testplus_spec);
    manager->registerFactory(profile,
                             RTC::Create<Testplus>,
                             RTC::Delete<Testplus>);
  }
  
};


