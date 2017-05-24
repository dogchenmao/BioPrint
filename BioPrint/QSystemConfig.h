#pragma once
#include <QString>
#include <QChar>
#include <QFile>
#include <QSettings>
#include <QDir>
struct PointXYZ
{
	float X;              //!< ��ȡ�����X����
	float Y;              //!< ��ȡ�����Y����
	float Z;              //!< ��ȡ�����Z����

	// Ĭ�Ͻ���������Ϊ(0, 0, 0)
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
	QString m_DeviceIP;                       // ��һ�γɹ����ӵ�IP��ַ
	QString m_LastSuccessCOM_Airpower;        // ��һ�γɹ����������Ĵ��ں�
	QString m_CameraName;               // ����ͷ����

	bool isShowLogin;                           // �Ƿ���ʾ��������
	int  nBootScreenTimes;                      // �����������ʱ��(ms)

	float m_fBuildSize_X;                       // ��������ӡX��ߴ�
	float m_fBuildSize_Y;                       // ��������ӡY��ߴ�
	float m_fBuildSize_Z;                       // ��������ӡZ��ߴ�

	float m_fPlatformSize_X;                    // ��ӡƽ̨X��ߴ�
	float m_fPlatformSize_Y;                    // ��ӡƽ̨Y��ߴ�

	int m_nGCodeOffset_X;                       // GCode��ʾX��ƫ������
	int m_nGCodeOffset_Y;                       // GCode��ʾY��ƫ������

	bool m_isXRevise;                           // X���Ƿ���
	bool m_isYRevise;                           // Y���Ƿ���
	bool m_isZRevise;                           // Z���Ƿ���(ƽ̨��/��ͷ��)

	bool m_isExtrudeTempHigh;                   // �Ƿ��Ǹ�����ͷ
	bool m_isControlTemp;                       // �Ƿ����
	bool m_isAutoCalibration;                   // �Ƿ��Զ�У׼XY������

	bool m_isUVAutoMode;                        // �Ƿ��Զ�����UV��
	int m_nUVPower;                             // UV�ƹ���(0-100)

	float m_fBuildSize_Z_Build;                 // ��ӡƽ̨�߶�
	float m_fBuildSize_Z_Knife;                 // �Ե��ǲ�õĸ߶�ֵ
	float m_fBuildSize_Z_Diff;                  // �Ե���ƽ̨�ʹ�ӡƽ̨�߶Ȳ�
	float m_fBuildSize_Z_Offset;                // �Ե���ƽ̨�ʹ�ӡƽ̨�߶Ȳ�Ĺ̶�ϵͳ���

	float m_fCamera_Z_Offset;                   // ����ͷʶ������ڶԵ�������̧�߸߶�
	float m_fHeadHeight_Z_Offset;               // Z��Ե���һ�׶��½��߶�ֵ

	PointXYZ m_CalibrateKnife_Pos;             // �Ը�������λ������
	PointXYZ m_CalibrateCleanKnifeHigh_Pos;    // ������ͷ���װ������λ������
	PointXYZ m_CalibrateCleanKnifeLow_Pos;     // ������ͷ���װ������λ������
	PointXYZ m_Camera_Pos;                     // XYУ׼����ͷ����λ������
	PointXYZ m_LevelTest_A_Pos;                // ���Ե�A����λ������
	PointXYZ m_LevelTest_B_Pos;                // ���Ե�B����λ������
	PointXYZ m_LevelTest_C_Pos;                // ���Ե�C����λ������
	PointXYZ m_BuildPlatform_Pos;              // ��ӡƽ̨Z����λ������
	PointXYZ m_KnifePlatform_Pos;              // �Ը���ƽ̨Z����λ������
	PointXYZ m_PlatformCenter_Pos;             // ��ӡƽ̨��������

	int m_nSpeedRange_XY_Min;                   // XY���ƶ�����С�ٶ�
	int m_nSpeedRange_XY_Max;                   // XY���ƶ�������ٶ�
	int m_nSpeedRange_Z_Min;                    // Z���ƶ�����С�ٶ�
	int m_nSpeedRange_Z_Max;                    // Z���ƶ�������ٶ�

	int m_nTempRange_Ex_Min;                    // ��ͷ��������¶�
	int m_nTempRange_Ex_Max;                    // ��ͷ��������¶�
	int m_nTempRange_Pl_Min;                    // ƽ̨��������¶�
	int m_nTempRange_Pl_Max;                    // ƽ̨��������¶�

	float m_fCurrent_Min;                       // �������õĵ�����Сֵ
	float m_fCurrent_Max;                       // �������õĵ������ֵ

	float m_fRegression_K;                      // ����-ѹ���ع鷽��б��
	float m_fRegression_B;                      // ����-ѹ���ع鷽�̽ؾ�

	float m_fPressure_Min;                      // ��������ѹ������Сֵ
	float m_fPressure_Max;                      // ��������ѹ�������ֵ

	int m_nFlow_Min;                            // ˮ�����������

	bool m_isFlow_Open;                         // ˮ����Ƿ��

	/************************************************************************/
	/*                            �û���������                              */
	/************************************************************************/
	unsigned short m_nVersion;                            //!< �豸�汾��Ϣ

	int m_nSpeed_XY;                            //!< ��ǰ����XY���ƶ��ٶ�
	int m_nSpeed_Z;                             //!< ��ǰ����Z���ƶ��ٶ�

	float m_fPressure;                          //!< ��ǰ����ѹ����С

	int m_nMoveMode;                            //!< ��ǰ�����ƶ�ģʽ����
	int m_nMoveLength;                          //!< ��ǰ�����ƶ���������

	float m_fCustomMoveLength;                  //!< �Զ����ƶ�����
	int m_nMaterialSize;                        //!< �Զ������ѡ�����
	//CStringArray m_strMaterial;                 //!< �û��Զ������ѡ��

	int m_nExtrudeTemp_Set;                     //!< �û��趨��ͷ�¶�
	int m_nPlatformTemp_Set;                    //!< �û��趨ƽ̨�¶�
	int m_nKnife1Temp_Set;                      //!< �û��趨����1�¶�
	int m_nKnife2Temp_Set;                      //!< �û��趨����2�¶�
	int m_nKnife3Temp_Set;                      //!< �û��趨����3�¶�
	int m_nKnife4Temp_Set;                      //!< �û��趨����4�¶�

	int m_Camera_Direction_X;                   // ����ͷX����
	//  1:   X+   --->   X+
	// -1:   X+   --->   X-
	//  2:   X+   --->   Y+
	// -2:   X+   --->   Y-
	int m_Camera_Direction_Y;                   // ����ͷY����
	//  1:   Y+   --->   Y+
	// -1:   Y+   --->   Y-
	//  2:   Y+   --->   X+
	// -2:   Y+   --->   X-

	PointXYZ m_Camera_Radio;                   // 1mm��Ӧ����ͷ���ظ���



	/************************************************************************/
	/*                           ģ��GCode��������                          */
	/************************************************************************/
	//int m_nExtrudeNum;                          //!< ��ͷ�������
	//int m_nExtrudeType;                         //!< ��ͷ��������
	//int m_nMaterial;                            //!< ��ӡ��������
	//int m_nSupportMode;                         //!< ֧��ģʽ����
	//bool m_bAddRaft;                            //!< �Ƿ��ӡ����
	//bool m_bAddBoundary;                        //!< �Ƿ��ӡ����
	//int m_nPrintSpeed;                          //!< ��ӡ�ٶ�
	//int m_nThickness;                           //!< ��ӡ���
	//int m_nExtrudeTemp;                         //!< ��ͷ�¶�
	//int m_nPlatformTemp;                        //!< ƽ̨�¶�
	//int m_nFillRate;                            //!< �����
	//int m_nExtraFill;                           //!< ����ʵ�Ĳ�

protected:
	QString *name;                       //!< ���ڴ����Ҫ���ļ����ļ���(����·��)
	QString UserDataPath;                       //!< �û�����Ŀ¼
	QFile File;					              //!< ����û����ݵ��ļ�
public:
	void SetFileName(QString *name);
	QString GetUserDataPath(void);
	void Load();
	void Save();
};

extern QSystemConfig m_QSystemConfig;