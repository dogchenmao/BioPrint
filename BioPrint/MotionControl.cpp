#include "MotionControl.h"
#include "QSystemConfig.h"
#include <QDebug>
MotionControl::MotionControl(QObject *parent)
: QThread(parent)
{
	Init();
	start();
}

MotionControl::~MotionControl()
{
}

void MotionControl::Init()
{
	static MC_COM_INIT_DATA *initData = nullptr ;

	initData->InitMaxXAxis = m_QSystemConfig.m_fBuildSize_X;
	initData->InitMaxYAxis = m_QSystemConfig.m_fBuildSize_Y;
	initData->InitMaxZAxis = m_QSystemConfig.m_fBuildSize_Z;
	initData->D_ValueSensorPlatform = m_QSystemConfig.m_fBuildSize_Z_Diff;
	initData->CameraXAxis = m_QSystemConfig.m_Camera_Pos.X;
	initData->CameraYAxis = m_QSystemConfig.m_Camera_Pos.Y;
	initData->AdjZ_HeadXAxis = m_QSystemConfig.m_CalibrateKnife_Pos.X;
	initData->AdjZ_HeadYAxis = m_QSystemConfig.m_CalibrateKnife_Pos.Y;
	initData->Adj_SensorXAxis = m_QSystemConfig.m_KnifePlatform_Pos.X;
	initData->Adj_SensorYAxis = m_QSystemConfig.m_KnifePlatform_Pos.Y;
	initData->Adj_PlatformXAxis = m_QSystemConfig.m_BuildPlatform_Pos.X;
	initData->Adj_PlatformYAxis = m_QSystemConfig.m_BuildPlatform_Pos.Y;
	initData->ClearHighHeadXAxis = m_QSystemConfig.m_CalibrateCleanKnifeHigh_Pos.X;
	initData->ClearHighHeadYAxis = m_QSystemConfig.m_CalibrateCleanKnifeHigh_Pos.Y;
	initData->ClearLowHeadXAxis = m_QSystemConfig.m_CalibrateCleanKnifeLow_Pos.X;
	initData->ClearLowHeadYAxis = m_QSystemConfig.m_CalibrateCleanKnifeLow_Pos.Y;
	initData->Z_HeadHeight = m_QSystemConfig.m_fBuildSize_Z_Knife;
	//initData.Z_HeadOffsetX = m_QSystemConfig.m_fHeadOffsetX;
	//initData.Adj_PlatformXAxisOffset = m_QSystemConfig.m_fPlatformXAxisOffset;
	//initData.AdjZ_SensorHeightXAxisOffset = m_QSystemConfig.m_fZSensorHeightXAxisOffset;
	//initData.adjZ_HeadCameraZOffset = m_QSystemConfig.m_fZHeadCameraZOffset;
	//initData.adjZ_HeadFirstStageAxis = m_QSystemConfig.m_fZHeadFirstStageAxis;
	//initData.AdjZ_SensorFirstStagAxis = m_QSystemConfig.m_fZSensorFirstStagAxis;
	//initData.AdjZ_PlatformFirstStageAxis = m_QSystemConfig.m_fZPlatformFirstStageAxis;



	//initData.SwitchHeadYAxis[1] = m_QSystemConfig.m_fSwitchHeadYAxis1;
	//initData.SwitchHeadYAxis[2] = m_QSystemConfig.m_fSwitchHeadYAxis2;
	//initData.SwitchHeadYAxis[3] = m_QSystemConfig.m_fSwitchHeadYAxis3;
	//initData.SwitchHeadYAxis[4] = m_QSystemConfig.m_fSwitchHeadYAxis4;

	//initData.TestAdjHighSensorXAxis = m_QSystemConfig.m_TestAdjHighSensor_Pos.X;
	//initData.TestAdjHighSensorYAxis = m_QSystemConfig.m_TestAdjHighSensor_Pos.Y;
	//initData.TestAdjHighSensorZAxis = m_QSystemConfig.m_TestAdjHighSensor_Pos.Z;

	//initData.TestAdjHeadXAxis = m_QSystemConfig.m_TestAdjHead_Pos.X;
	//initData.TestAdjHeadYAxis = m_QSystemConfig.m_TestAdjHead_Pos.Y;
	//initData.TestAdjHeadZAxis = m_QSystemConfig.m_TestAdjHead_Pos.Z;

	//for (int i = 0; i < 256; i++) {
	//	initData.HeadSpecData[i].ClearModule = (MC_U8)theApp.m_NozzleInfo.GetNozzleInfo(i)->CleanModule;
	//	initData.HeadSpecData[i].LocateShelfX = theApp.m_NozzleInfo.GetNozzleInfo(i)->LocateShelfX;
	//	initData.HeadSpecData[i].CmpHead3OffsetX = theApp.m_NozzleInfo.GetNozzleInfo(i)->CmpHead3OffsetX;
	//}
	initData = nullptr;
	MC_CoreInit(initData);
}

void MotionControl::run()
{

}