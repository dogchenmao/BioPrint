#ifndef __MC_COM_UDCS_H__
#define __MC_COM_UDCS_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "mc_config.h"

    typedef struct
    {
        MC_U8   HeadExistState[5];      // ��ͷ������������ڣ�MC_TRUE�������ڣ�MC_FALSE��Ĭ�϶������ڡ�0��Ԫ��ΪZ�ᣬ1-4��Ԫ��Ϊ���ܡ�
        MC_BOOL OnMC_CoreExec;          // ����MC_Exec()����ִ��ʱ��Ϊ1,�˳�ʱ��Ϊ0��
        MC_F64  CurrentCoordX;
        MC_F64  CurrentCoordY;
        MC_F64  CurrentCoordZ;
        MC_F64  CurrentCoordU;
        MC_BOOL AllAxisStop;            // �岹�˶��иñ�־��Ч��Ĭ��MC_TRUE�������ΪMC_TRUE��
        MC_BOOL ReturnHomeStart;        // ����ָ��-���㿪ʼ��־��Ĭ��MC_FALSE�������ΪMC_TRUE��
        MC_BOOL ReturnHomeFinish;       // ����ָ��-������ɱ�־��Ĭ��MC_FALSE�������ΪMC_TRUE��
        MC_BOOL MoveToCameraCenter;     // ���١�����ָ��-�ƶ�������ͷʶ��λ�á�Ĭ��MC_FALSE�������ΪMC_TRUE��
        MC_BOOL AdjZ_HeadHeightStart;   // ����ָ��-Z��Ե���ɡ�Ĭ��MC_FALSE����ʼ��ΪMC_TRUE��
        MC_BOOL AdjZ_HeadHeightFinish;  // ����ָ��-Z��Ե���ɡ�Ĭ��MC_FALSE�������ΪMC_TRUE��
        MC_F64  Z_HeadHeight;           // Z��Ե��߶ȡ�
        MC_U8   Adj_HighSensorEnable;   // �Ըߴ���������״̬��MC_TRUE-�򿪶Ըߴ�������MC_FALSE-�رնԸߴ�������
        MC_BOOL AdjZ_PlatformAndSensorHeightFinish; // ����ָ��-��������ƽ̨�Ը���ɡ�Ĭ��MC_FALSE�������ΪMC_TRUE��
        MC_F64  PlatformHeight;         // ��õ�ƽ̨�߶ȡ�
        MC_BOOL MeasurePlatformHeightFinish;        // ����ָ��-ƽ̨�����ɡ�Ĭ��MC_FALSE�������ΪMC_TRUE��
        MC_F64  D_ValueSensorPlatform;  // ƽ̨�ʹ������߶ȵ�ƫ��ֵ��
        MC_BOOL ClearHeadFinish;        // ����ָ��-��ͷ�����ɱ�־��Ĭ��MC_FALSE�������ΪMC_TRUE��
        MC_BOOL HeadRecognizeEnable;    // ��ͷʶ��ʹ�ܱ�־��������ͷ�л���������ͣ��ͷʶ��Ĭ��MC_TRUE������Ӵ�ʱ����ΪMC_FALSE��
        MC_BOOL QueueSwitchHeadStart;   // ����ָ��-��ͷ�л���ʼ��Ĭ��MC_FALSE����ʼ��ΪMC_TRUE��
        MC_BOOL QueueSwitchHeadFinish;  // ����ָ��-��ͷ�л���ɡ�Ĭ��MC_FALSE�������ΪMC_TRUE��
        MC_BOOL FastSwitchHeadStart;    // ����ָ��-��ͷ�л���ʼ��Ĭ��MC_FALSE����ʼ��ΪMC_TRUE��
        MC_BOOL FastSwitchHeadFinish;   // ����ָ��-��ͷ�л���ɡ�Ĭ��MC_FALSE�������ΪMC_TRUE��
        MC_U32  PrintTime;              // ��ǰ�ۼƴ�ӡʱ�䣬��λs��
        MC_BOOL PrintFinish;            // ��ӡ��ɱ�־������ָ��Ϊ�գ���������ָ��Ϊ�գ���������ֹͣʱ����ΪMC_FALSE������MC_FALSE��
        MC_BOOL SwitchHeadError;        // ��ͷ�л������־��Ĭ��ΪMC_FALSE��������ΪMC_TRUE��
        MC_BOOL EmergencyStopFlag;      // ����ֹͣ��־��Ĭ��ΪMC_FALSE������ֹ֮ͣ��ΪMC_TRUE��
        MC_BOOL LineMoveFinish;         // ֱ���˶���ɱ�־��ÿִ��һ��ֱ���˶������֮����ΪMC_TRUE������ΪMC_FALSE��
        MC_BOOL TestAdjHighSensor;      // �Ըߴ���������״̬��Ĭ��MC_FALSE������������MC_TRUE��
        MC_BOOL TestAdjHeadSensor;      // �Ե�����������״̬��Ĭ��MC_FALSE������������MC_TRUE��
        MC_BOOL AddHeadFinish;          // ������ͷ��ɱ�־��Ĭ��MC_FLASE���ƶ���������ͷ�ĵ㣬����ΪMC_TRUE��
        MC_BOOL SelfTestFinish;         // �Լ���ɱ�־��Ĭ��ΪMC_FALSE�������ΪMC_TRUE��
        MC_F64  Z_HeadOffsetX;          // Z��Ե�������ͷУ׼����X���ꡣ
    } MC_COM_UDCS_DATA;
    typedef struct
    {
        MC_U8   ClearModule;       // ��ͷ���ģ��ѡ��
        MC_F64  LocateShelfX;      // ��ͷ�ڵ����ϵ�X���ꡣ
        MC_F64  CmpHead3OffsetX;   // ��ͬ��ͷ�����3����ͷ���ƫ���ֵ���������ӦΪ��ͷ��ȵ�һ�룬ֱ��������ͷ�л���ƫ��������
    } MC_COM_HEAD_SPEC;

    typedef struct
    {
        MC_F64 InitMaxXAxis;          // X�����������λ��
        MC_F64 InitMaxYAxis;          // Y�����������λ��
        MC_F64 InitMaxZAxis;          // Z�����������λ��

        MC_F64 SwitchHeadYAxis[5];    // �ĸ�������ͷ�л�Y����ֵ��0��Ԫ��δʹ�á�

        MC_F64 D_ValueSensorPlatform; // ƽ̨�ʹ������߶ȵ�ƫ��ֵ��

        MC_F64 CameraXAxis;           // ����ͷʶ��X������
        MC_F64 CameraYAxis;           // ����ͷʶ��Y������

        MC_F64 AdjZ_HeadXAxis;        // ��ͷZ��Ե�X�����ꡣ
        MC_F64 AdjZ_HeadYAxis;        // ��ͷZ��Ե�Y�����ꡣ

        MC_F64 Adj_SensorXAxis;       // �������Ը�X�����ꡣ
        MC_F64 Adj_SensorYAxis;       // �������Ը�Y�����ꡣ

        MC_F64 AdjZ_SensorHeightXAxisOffset; // �������Ը�X������ƫ��ֵ��
        MC_F64 Adj_PlatformXAxisOffset; // ƽ̨�Ը�X������ƫ��ֵ��
        MC_F64 Adj_PlatformXAxis;       // ƽ̨�Ը�X�����ꡣ
        MC_F64 Adj_PlatformYAxis;       // ƽ̨�Ը�Y�����ꡣ

        MC_F64 ClearHighHeadXAxis;    // ������ͷ���X�����ꡣ
        MC_F64 ClearHighHeadYAxis;    // ������ͷ���Y�����ꡣ
        MC_F64 ClearLowHeadXAxis;     // ������ͷ���X�����ꡣ
        MC_F64 ClearLowHeadYAxis;     // ������ͷ���Y�����ꡣ

        MC_F64 Z_HeadHeight;          // Z��Ե��߶ȡ�
        MC_F64 Z_HeadOffsetX;         // Z��Ե�������ͷУ׼����X���ꡣ

        MC_F64 TestAdjHighSensorXAxis;  // �Ըߴ���������X���ꡣ
        MC_F64 TestAdjHighSensorYAxis;  // �Ըߴ���������Y���ꡣ
        MC_F64 TestAdjHighSensorZAxis;  // �Ըߴ���������Z���ꡣ
        MC_F64 TestAdjHeadXAxis;        // �Ե�����������X���ꡣ
        MC_F64 TestAdjHeadYAxis;        // �Ե�����������Y���ꡣ
        MC_F64 TestAdjHeadZAxis;        // �Ե�����������Z���ꡣ
        MC_F64 adjZ_HeadCameraZOffset;  // ����ͷ�Ե�Z��ƫ�ơ�
        MC_F64 adjZ_HeadFirstStageAxis;     // Z���ߵ�һ�׶��½�Z�����ꡣĬ��144
        MC_F64 AdjZ_SensorFirstStagAxis;    // ��������ߵ�һ�׶��½�Z�����ꡣĬ��110
        MC_F64 AdjZ_PlatformFirstStageAxis; // ƽ̨��ߵ�һ�׶��½�Z�����ꡣĬ��98

        MC_COM_HEAD_SPEC HeadSpecData[256]; // ��ͬ��ͷ���Ի�������
    } MC_COM_INIT_DATA;

    //typedef struct
    //{
    //    MC_F64 InitMaxXAxis;          // X�����������λ��
    //    MC_F64 InitMaxYAxis;          // Y�����������λ��
    //    MC_F64 InitMaxZAxis;          // Z�����������λ��

    //    MC_F64 SwitchHeadYAxis[5];    // �ĸ�������ͷ�л�Y����ֵ��0��Ԫ��δʹ�á�

    //    MC_F64 D_ValueSensorPlatform; // ƽ̨�ʹ������߶ȵ�ƫ��ֵ��

    //    MC_F64 CameraYAxis;           // ����ͷʶ��Y������,����X�����ɸ��»������ͷ��X���������

    //    MC_F64 AdjZ_HeadYAxis;        // ��ͷZ��Ե�Y�����ꡣ

    //    MC_F64 Adj_SensorYAxis;       // �������Ը�Y�����ꡣ

    //    MC_F64 AdjZ_SensorHeightXAxisOffset; // �������Ը�X������ƫ��ֵ��
    //    MC_F64 Adj_PlatformXAxisOffset; // ƽ̨�Ը�X������ƫ��ֵ��
    //    MC_F64 Adj_PlatformYAxis;       // ƽ̨�Ը�Y�����ꡣ

    //    MC_F64 ClearHighHeadYAxis;    // ������ͷ���Y�����ꡣ
    //    MC_F64 ClearLowHeadYAxis;     // ������ͷ���Y�����ꡣ

    //    MC_F64 Z_HeadHeight;          // Z��Ե��߶ȡ�
    //    MC_F64 Z_HeadOffsetX;         // Z��Ե�������ͷУ׼����X���ꡣ

    //    MC_F64 TestAdjHighSensorXAxis;  // �Ըߴ���������X���ꡣ
    //    MC_F64 TestAdjHighSensorYAxis;  // �Ըߴ���������Y���ꡣ
    //    MC_F64 TestAdjHighSensorZAxis;  // �Ըߴ���������Z���ꡣ
    //    MC_F64 TestAdjHeadXAxis;        // �Ե�����������X���ꡣ
    //    MC_F64 TestAdjHeadYAxis;        // �Ե�����������Y���ꡣ
    //    MC_F64 TestAdjHeadZAxis;        // �Ե�����������Z���ꡣ
    //    MC_F64 adjZ_HeadCameraZOffset;  // ����ͷ�Ե�Z��ƫ�ơ�

    //    MC_COM_HEAD_SPEC HeadSpecData[256]; // ��ͬ��ͷ���Ի�������
    //} MC_COM_INIT_DATA;


    void MC_ComUdcsInit(void);
    MC_BOOL MC_CoreExec(void);
    MC_COM_UDCS_DATA* MC_ComUdcsGetFlag(void);


#ifdef  __cplusplus
}
#endif

#endif // !__MC_COM_UDCS_H__
