#include "QSystemConfig.h"


QSystemConfig::QSystemConfig()
{
	m_nSpeed_XY = 1500;
	m_nSpeed_Z = 1000;
	m_fPressure = 0.4;
	m_nMoveMode = 0;
	m_nMoveLength = 0;
	m_fCustomMoveLength = 0.5;              // 默认自定义移动长度为0.5mm
	m_nMaterialSize = 5;                // 默认自定义材料有5项
	m_nExtrudeTemp_Set = 25;
	m_nPlatformTemp_Set = 25;
	m_nKnife1Temp_Set = 25;
	m_nKnife2Temp_Set = 25;
	m_nKnife3Temp_Set = 25;
	m_nKnife4Temp_Set = 25;

	QDir tempDir;
	UserDataPath = tempDir.currentPath();
}


QSystemConfig::~QSystemConfig()
{
}

void QSystemConfig::SetFileName(QString *nameStr)
{
	name = nameStr;
}

QString QSystemConfig::GetUserDataPath(void)
{
	return UserDataPath;
}

QVariant GetValue(QSettings *configIniRead, QString szSection, QString PszEntry, QVariant fDefault)
{
	QVariant buffVariant;
	buffVariant = configIniRead->value((QString)(szSection + "/" + PszEntry));
	if (buffVariant.isValid())
	{
		return buffVariant;
	}
	else
	{
		return fDefault;
	}
}

void QSystemConfig::Load()
{
	QSettings *configIniRead = new QSettings(*name, QSettings::IniFormat);

	m_DeviceIP = configIniRead->value("SYSTEMSETTING/DeviceIP").toString();
	m_LastSuccessCOM_Airpower = configIniRead->value("SYSTEMSETTING/LastSuccessCOM_Airpower").toString();
	m_CameraName = configIniRead->value("SYSTEMSETTING/CameraName").toString();

	isShowLogin = configIniRead->value("SYSTEMSETTING/isShowLogin").toBool();
	nBootScreenTimes = configIniRead->value("SYSTEMSETTING/BootScreenTimes").toInt();

	m_fBuildSize_X = GetValue(configIniRead, "MACHINE", "BuildSize_X", 330.0).toFloat();
	m_fBuildSize_Y = GetValue(configIniRead, "MACHINE", "BuildSize_Y", 160.0).toFloat();
	m_fBuildSize_Z = GetValue(configIniRead, "MACHINE", "BuildSize_Z", 135.0).toFloat();

	m_fPlatformSize_X = GetValue(configIniRead,"MACHINE", "PlatformSize_X", 160).toFloat();
	m_fPlatformSize_Y = GetValue(configIniRead, "MACHINE", "PlatformSize_Y", 160).toFloat();

	m_nGCodeOffset_X = GetValue(configIniRead, "MACHINE", "GCodeOffset_X", 80).toInt();
	m_nGCodeOffset_Y = GetValue(configIniRead, "MACHINE", "GCodeOffset_Y", 0).toInt();

	m_isXRevise = GetValue(configIniRead, "MACHINE", "isXRevise", false).toBool();
	m_isYRevise = GetValue(configIniRead, "MACHINE", "isYRevise", false).toBool();
	m_isZRevise = GetValue(configIniRead, "MACHINE", "isZRevise", false).toBool();

	m_isExtrudeTempHigh = GetValue(configIniRead, "MACHINE", "isExtrudeTempHigh", false).toBool();
	m_isControlTemp = GetValue(configIniRead, "MACHINE", "isControlTemp", true).toBool();
	m_isAutoCalibration = GetValue(configIniRead, "MACHINE", "isAutoCalibration", true).toBool();

	m_isUVAutoMode = GetValue(configIniRead, "MACHINE", "UVAutoMode", true).toBool();
	m_nUVPower = GetValue(configIniRead, "MACHINE", "UVPower", 50).toInt();

	m_fBuildSize_Z_Build = GetValue(configIniRead, "MACHINE", "BuildSize_Z_Build", 0.0).toFloat();
	m_fBuildSize_Z_Knife = GetValue(configIniRead, "MACHINE", "BuildSize_Z_Knife", 100.0).toFloat();
	m_fBuildSize_Z_Diff = GetValue(configIniRead, "MACHINE", "BuildSize_Z_Diff", 0.0).toFloat();
	m_fBuildSize_Z_Offset = GetValue(configIniRead, "MACHINE", "BuildSize_Z_Offset", 0).toFloat();

	m_fCamera_Z_Offset = GetValue(configIniRead, "MACHINE", "Camera_Z_Offset", -15.02).toFloat();
	m_fHeadHeight_Z_Offset = GetValue(configIniRead, "MACHINE", "HeadHeight_Z_Offset", 123.0).toFloat();

	//m_CalibrateKnife_Pos = GetValue(configIniRead, "MACHINE", "CalibrateKnife_Pos", PointXYZ(70, 50, 0));
	//m_CalibrateCleanKnifeHigh_Pos = GetValue(configIniRead, "MACHINE", "CalibrateCleanKnifeHigh_Pos", PointXYZ(17, 125, 0));
	//m_CalibrateCleanKnifeLow_Pos = GetValue(configIniRead, "MACHINE", "CalibrateCleanKnifeLow_Pos", PointXYZ(61, 125, 0));
	//m_Camera_Pos = GetValue(configIniRead, "MACHINE", "Camera_Pos", PointXYZ(32, 50, 0));

	//m_LevelTest_A_Pos = GetValue(configIniRead, "MACHINE", "LevelTest_A_Pos", PointXYZ(260, 10, 0));
	//m_LevelTest_B_Pos = GetValue(configIniRead, "MACHINE", "LevelTest_B_Pos", PointXYZ(260, 160, 0));
	//m_LevelTest_C_Pos = GetValue(configIniRead, "MACHINE", "LevelTest_C_Pos", PointXYZ(335, 85, 0));

	//m_BuildPlatform_Pos = GetValue(configIniRead, "MACHINE", "BuildPlatform_Pos", PointXYZ(330, 84, 0));
	//m_KnifePlatform_Pos = GetValue(configIniRead, "MACHINE", "KnifePlatform_Pos", PointXYZ(143, 62, 0));

	//m_PlatformCenter_Pos = GetValue(configIniRead, "MACHINE", "PlatformCenter_Pos", PointXYZ(240, 70, 0));

	//m_nSpeedRange_XY_Min = GetValue(configIniRead, "MACHINE", "SpeedRange_XY_Min", 1);
	//m_nSpeedRange_XY_Max = GetValue(configIniRead, "MACHINE", "SpeedRange_XY_Max", 4000);
	//m_nSpeedRange_Z_Min = GetValue(configIniRead, "MACHINE", "SpeedRange_Z_Min", 1);
	//m_nSpeedRange_Z_Max = GetValue(configIniRead, "MACHINE", "SpeedRange_Z_Max", 1500);

	//m_nTempRange_Ex_Min = GetValue(configIniRead, "MACHINE", "TempRange_Ex_Min", -10);   //!< 低温-10~40    高温0~300
	//m_nTempRange_Ex_Max = GetValue(configIniRead, "MACHINE", "TempRange_Ex_Max", 300);
	//m_nTempRange_Pl_Min = GetValue(configIniRead, "MACHINE", "TempRange_Pl_Min", -30);
	//m_nTempRange_Pl_Max = GetValue(configIniRead, "MACHINE", "TempRange_Pl_Max", 60);

	//m_fCurrent_Min = GetValue(configIniRead, "MACHINE", "Current_Min", 4);
	//m_fCurrent_Max = GetValue(configIniRead, "MACHINE", "Current_Max", 20);

	//m_fRegression_K = GetValue(configIniRead, "MACHINE", "Regression_K", 18.072);
	//m_fRegression_B = GetValue(configIniRead, "MACHINE", "Regression_B", 3.9939);

	//m_fPressure_Min = GetValue(configIniRead, "MACHINE", "Pressure_Min", 0);
	//m_fPressure_Max = GetValue(configIniRead, "MACHINE", "Pressure_Max", 0.6);

	//m_Camera_Direction_X = GetValue(configIniRead, "MACHINE", "Camera_Dir_X", 1);
	//m_Camera_Direction_Y = GetValue(configIniRead, "MACHINE", "Camera_Dir_Y", -1);
	//m_Camera_Radio = GetValue(configIniRead, "MACHINE", "Camera_Radio", PointXYZ(44, 44, 0));

	//m_nFlow_Min = GetValue(configIniRead, "MACHINE", "Flow_Min", 3);
	//m_isFlow_Open = GetValue(configIniRead, "MACHINE", "isFlow_Open", TRUE);

}
QSystemConfig m_QSystemConfig;