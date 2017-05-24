#pragma once
#include <QString>
#include <QChar>
#include <QFile>
#include <QSettings>
#include <QDir>
struct PointXYZ
{
	float X;              //!< 获取坐标的X分量
	float Y;              //!< 获取坐标的Y分量
	float Z;              //!< 获取坐标的Z分量

	// 默认将坐标设置为(0, 0, 0)
	PointXYZ(){ X = 0, Y = 0, Z = 0; }

	PointXYZ(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}
};


class QSystemConfig
{
public:
	QSystemConfig();
	~QSystemConfig();
public:
	QString m_DeviceIP;                       // 上一次成功连接的IP地址
	QString m_LastSuccessCOM_Airpower;        // 上一次成功连接气动的串口号
	QString m_CameraName;               // 摄像头名字

	bool isShowLogin;                           // 是否显示开机界面
	int  nBootScreenTimes;                      // 开机界面持续时间(ms)

	float m_fBuildSize_X;                       // 机器最大打印X轴尺寸
	float m_fBuildSize_Y;                       // 机器最大打印Y轴尺寸
	float m_fBuildSize_Z;                       // 机器最大打印Z轴尺寸

	float m_fPlatformSize_X;                    // 打印平台X轴尺寸
	float m_fPlatformSize_Y;                    // 打印平台Y轴尺寸

	int m_nGCodeOffset_X;                       // GCode显示X轴偏移坐标
	int m_nGCodeOffset_Y;                       // GCode显示Y轴偏移坐标

	bool m_isXRevise;                           // X轴是否反向
	bool m_isYRevise;                           // Y轴是否反向
	bool m_isZRevise;                           // Z轴是否反向(平台动/喷头动)

	bool m_isExtrudeTempHigh;                   // 是否是高温喷头
	bool m_isControlTemp;                       // 是否控温
	bool m_isAutoCalibration;                   // 是否自动校准XY轴坐标

	bool m_isUVAutoMode;                        // 是否自动开启UV灯
	int m_nUVPower;                             // UV灯功率(0-100)

	float m_fBuildSize_Z_Build;                 // 打印平台高度
	float m_fBuildSize_Z_Knife;                 // 对刀仪测得的高度值
	float m_fBuildSize_Z_Diff;                  // 对刀仪平台和打印平台高度差
	float m_fBuildSize_Z_Offset;                // 对刀仪平台和打印平台高度差的固定系统误差

	float m_fCamera_Z_Offset;                   // 摄像头识别相对于对刀传感器抬高高度
	float m_fHeadHeight_Z_Offset;               // Z轴对刀第一阶段下降高度值

	PointXYZ m_CalibrateKnife_Pos;             // 对高仪所在位置坐标
	PointXYZ m_CalibrateCleanKnifeHigh_Pos;    // 高温喷头清洁装置所在位置坐标
	PointXYZ m_CalibrateCleanKnifeLow_Pos;     // 低温喷头清洁装置所在位置坐标
	PointXYZ m_Camera_Pos;                     // XY校准摄像头所在位置坐标
	PointXYZ m_LevelTest_A_Pos;                // 测试点A所在位置坐标
	PointXYZ m_LevelTest_B_Pos;                // 测试点B所在位置坐标
	PointXYZ m_LevelTest_C_Pos;                // 测试点C所在位置坐标
	PointXYZ m_BuildPlatform_Pos;              // 打印平台Z轴测高位置坐标
	PointXYZ m_KnifePlatform_Pos;              // 对高仪平台Z轴测高位置坐标
	PointXYZ m_PlatformCenter_Pos;             // 打印平台中心坐标

	int m_nSpeedRange_XY_Min;                   // XY轴移动的最小速度
	int m_nSpeedRange_XY_Max;                   // XY轴移动的最大速度
	int m_nSpeedRange_Z_Min;                    // Z轴移动的最小速度
	int m_nSpeedRange_Z_Max;                    // Z轴移动的最大速度

	int m_nTempRange_Ex_Min;                    // 喷头设置最低温度
	int m_nTempRange_Ex_Max;                    // 喷头设置最高温度
	int m_nTempRange_Pl_Min;                    // 平台设置最低温度
	int m_nTempRange_Pl_Max;                    // 平台设置最高温度

	float m_fCurrent_Min;                       // 驱动气泵的电流最小值
	float m_fCurrent_Max;                       // 驱动气泵的电流最大值

	float m_fRegression_K;                      // 电流-压力回归方程斜率
	float m_fRegression_B;                      // 电流-压力回归方程截距

	float m_fPressure_Min;                      // 可以设置压力的最小值
	float m_fPressure_Max;                      // 可以设置压力的最大值

	int m_nFlow_Min;                            // 水冷机流速下限

	bool m_isFlow_Open;                         // 水冷机是否打开

	/************************************************************************/
	/*                            用户数据配置                              */
	/************************************************************************/
	unsigned short m_nVersion;                            //!< 设备版本信息

	int m_nSpeed_XY;                            //!< 当前设置XY轴移动速度
	int m_nSpeed_Z;                             //!< 当前设置Z轴移动速度

	float m_fPressure;                          //!< 当前设置压力大小

	int m_nMoveMode;                            //!< 当前设置移动模式索引
	int m_nMoveLength;                          //!< 当前设置移动长度索引

	float m_fCustomMoveLength;                  //!< 自定义移动长度
	int m_nMaterialSize;                        //!< 自定义材料选项个数
	//CStringArray m_strMaterial;                 //!< 用户自定义材料选项

	int m_nExtrudeTemp_Set;                     //!< 用户设定喷头温度
	int m_nPlatformTemp_Set;                    //!< 用户设定平台温度
	int m_nKnife1Temp_Set;                      //!< 用户设定刀架1温度
	int m_nKnife2Temp_Set;                      //!< 用户设定刀架2温度
	int m_nKnife3Temp_Set;                      //!< 用户设定刀架3温度
	int m_nKnife4Temp_Set;                      //!< 用户设定刀架4温度

	int m_Camera_Direction_X;                   // 摄像头X方向
	//  1:   X+   --->   X+
	// -1:   X+   --->   X-
	//  2:   X+   --->   Y+
	// -2:   X+   --->   Y-
	int m_Camera_Direction_Y;                   // 摄像头Y方向
	//  1:   Y+   --->   Y+
	// -1:   Y+   --->   Y-
	//  2:   Y+   --->   X+
	// -2:   Y+   --->   X-

	PointXYZ m_Camera_Radio;                   // 1mm对应摄像头像素个数



	/************************************************************************/
	/*                           模型GCode参数配置                          */
	/************************************************************************/
	//int m_nExtrudeNum;                          //!< 喷头编号索引
	//int m_nExtrudeType;                         //!< 喷头类型索引
	//int m_nMaterial;                            //!< 打印材料索引
	//int m_nSupportMode;                         //!< 支撑模式索引
	//bool m_bAddRaft;                            //!< 是否打印基座
	//bool m_bAddBoundary;                        //!< 是否打印轮廓
	//int m_nPrintSpeed;                          //!< 打印速度
	//int m_nThickness;                           //!< 打印层厚
	//int m_nExtrudeTemp;                         //!< 喷头温度
	//int m_nPlatformTemp;                        //!< 平台温度
	//int m_nFillRate;                            //!< 填充间距
	//int m_nExtraFill;                           //!< 表面实心层

protected:
	QString *name;                       //!< 用于存放需要打开文件的文件名(包含路径)
	QString UserDataPath;                       //!< 用户数据目录
	QFile File;					              //!< 存放用户数据的文件
public:
	void SetFileName(QString *name);
	QString GetUserDataPath(void);
	void Load();
	void Save();
};

extern QSystemConfig m_QSystemConfig;