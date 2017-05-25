#ifndef __MC_COM_UDCS_H__
#define __MC_COM_UDCS_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "mc_config.h"

    typedef struct
    {
        MC_U8   HeadExistState[5];      // 喷头存在情况，存在：MC_TRUE，不存在：MC_FALSE，默认都不存在。0号元素为Z轴，1-4号元素为刀架。
        MC_BOOL OnMC_CoreExec;          // 进入MC_Exec()函数执行时置为1,退出时置为0。
        MC_F64  CurrentCoordX;
        MC_F64  CurrentCoordY;
        MC_F64  CurrentCoordZ;
        MC_F64  CurrentCoordU;
        MC_BOOL AllAxisStop;            // 插补运动中该标志无效。默认MC_TRUE，完成置为MC_TRUE。
        MC_BOOL ReturnHomeStart;        // 快速指令-回零开始标志。默认MC_FALSE，完成置为MC_TRUE。
        MC_BOOL ReturnHomeFinish;       // 快速指令-回零完成标志。默认MC_FALSE，完成置为MC_TRUE。
        MC_BOOL MoveToCameraCenter;     // 快速、队列指令-移动到摄像头识别位置。默认MC_FALSE，完成置为MC_TRUE。
        MC_BOOL AdjZ_HeadHeightStart;   // 快速指令-Z轴对刀完成。默认MC_FALSE，开始置为MC_TRUE。
        MC_BOOL AdjZ_HeadHeightFinish;  // 快速指令-Z轴对刀完成。默认MC_FALSE，完成置为MC_TRUE。
        MC_F64  Z_HeadHeight;           // Z轴对刀高度。
        MC_U8   Adj_HighSensorEnable;   // 对高传感器工作状态。MC_TRUE-打开对高传感器，MC_FALSE-关闭对高传感器。
        MC_BOOL AdjZ_PlatformAndSensorHeightFinish; // 快速指令-传感器和平台对高完成。默认MC_FALSE，完成置为MC_TRUE。
        MC_F64  PlatformHeight;         // 测得的平台高度。
        MC_BOOL MeasurePlatformHeightFinish;        // 快速指令-平台测高完成。默认MC_FALSE，完成置为MC_TRUE。
        MC_F64  D_ValueSensorPlatform;  // 平台和传感器高度的偏差值。
        MC_BOOL ClearHeadFinish;        // 快速指令-喷头清洁完成标志。默认MC_FALSE，完成置为MC_TRUE。
        MC_BOOL HeadRecognizeEnable;    // 喷头识别使能标志，用于喷头切换过程中暂停喷头识别。默认MC_TRUE，触点接触时，置为MC_FALSE。
        MC_BOOL QueueSwitchHeadStart;   // 队列指令-喷头切换开始。默认MC_FALSE，开始置为MC_TRUE。
        MC_BOOL QueueSwitchHeadFinish;  // 队列指令-喷头切换完成。默认MC_FALSE，完成置为MC_TRUE。
        MC_BOOL FastSwitchHeadStart;    // 快速指令-喷头切换开始。默认MC_FALSE，开始置为MC_TRUE。
        MC_BOOL FastSwitchHeadFinish;   // 快速指令-喷头切换完成。默认MC_FALSE，完成置为MC_TRUE。
        MC_U32  PrintTime;              // 当前累计打印时间，单位s。
        MC_BOOL PrintFinish;            // 打印完成标志。队列指令为空，控制器中指令为空，且所有轴停止时，置为MC_FALSE，否则MC_FALSE。
        MC_BOOL SwitchHeadError;        // 喷头切换出错标志，默认为MC_FALSE，出错置为MC_TRUE。
        MC_BOOL EmergencyStopFlag;      // 紧急停止标志，默认为MC_FALSE，紧急停止之后为MC_TRUE。
        MC_BOOL LineMoveFinish;         // 直线运动完成标志，每执行一次直线运动，完成之后置为MC_TRUE，否则为MC_FALSE。
        MC_BOOL TestAdjHighSensor;      // 对高传感器测试状态，默认MC_FALSE，测试正常，MC_TRUE。
        MC_BOOL TestAdjHeadSensor;      // 对刀传感器测试状态，默认MC_FALSE，测试正常，MC_TRUE。
        MC_BOOL AddHeadFinish;          // 加载喷头完成标志，默认MC_FLASE，移动到加载喷头的点，则置为MC_TRUE。
        MC_BOOL SelfTestFinish;         // 自检完成标志，默认为MC_FALSE，完成置为MC_TRUE。
        MC_F64  Z_HeadOffsetX;          // Z轴对刀和摄像头校准补偿X坐标。
    } MC_COM_UDCS_DATA;
    typedef struct
    {
        MC_U8   ClearModule;       // 喷头清洁模块选择。
        MC_F64  LocateShelfX;      // 喷头在刀架上的X坐标。
        MC_F64  CmpHead3OffsetX;   // 不同喷头相对于3号喷头厚度偏差，该值正常情况下应为喷头厚度的一半，直接用于喷头切换，偏差修正。
    } MC_COM_HEAD_SPEC;

    typedef struct
    {
        MC_F64 InitMaxXAxis;          // X轴正向最大限位。
        MC_F64 InitMaxYAxis;          // Y轴正向最大限位。
        MC_F64 InitMaxZAxis;          // Z轴正向最大限位。

        MC_F64 SwitchHeadYAxis[5];    // 四个刀座喷头切换Y坐标值，0号元素未使用。

        MC_F64 D_ValueSensorPlatform; // 平台和传感器高度的偏差值。

        MC_F64 CameraXAxis;           // 摄像头识别X轴坐标
        MC_F64 CameraYAxis;           // 摄像头识别Y轴坐标

        MC_F64 AdjZ_HeadXAxis;        // 喷头Z轴对刀X轴坐标。
        MC_F64 AdjZ_HeadYAxis;        // 喷头Z轴对刀Y轴坐标。

        MC_F64 Adj_SensorXAxis;       // 传感器对高X轴坐标。
        MC_F64 Adj_SensorYAxis;       // 传感器对高Y轴坐标。

        MC_F64 AdjZ_SensorHeightXAxisOffset; // 传感器对高X轴坐标偏移值。
        MC_F64 Adj_PlatformXAxisOffset; // 平台对高X轴坐标偏移值。
        MC_F64 Adj_PlatformXAxis;       // 平台对高X轴坐标。
        MC_F64 Adj_PlatformYAxis;       // 平台对高Y轴坐标。

        MC_F64 ClearHighHeadXAxis;    // 高温喷头清洁X轴坐标。
        MC_F64 ClearHighHeadYAxis;    // 高温喷头清洁Y轴坐标。
        MC_F64 ClearLowHeadXAxis;     // 低温喷头清洁X轴坐标。
        MC_F64 ClearLowHeadYAxis;     // 低温喷头清洁Y轴坐标。

        MC_F64 Z_HeadHeight;          // Z轴对刀高度。
        MC_F64 Z_HeadOffsetX;         // Z轴对刀和摄像头校准补偿X坐标。

        MC_F64 TestAdjHighSensorXAxis;  // 对高传感器测试X坐标。
        MC_F64 TestAdjHighSensorYAxis;  // 对高传感器测试Y坐标。
        MC_F64 TestAdjHighSensorZAxis;  // 对高传感器测试Z坐标。
        MC_F64 TestAdjHeadXAxis;        // 对刀传感器测试X坐标。
        MC_F64 TestAdjHeadYAxis;        // 对刀传感器测试Y坐标。
        MC_F64 TestAdjHeadZAxis;        // 对刀传感器测试Z坐标。
        MC_F64 adjZ_HeadCameraZOffset;  // 摄像头对刀Z轴偏移。
        MC_F64 adjZ_HeadFirstStageAxis;     // Z轴测高第一阶段下降Z轴坐标。默认144
        MC_F64 AdjZ_SensorFirstStagAxis;    // 传感器测高第一阶段下降Z轴坐标。默认110
        MC_F64 AdjZ_PlatformFirstStageAxis; // 平台测高第一阶段下降Z轴坐标。默认98

        MC_COM_HEAD_SPEC HeadSpecData[256]; // 不同喷头个性化参数。
    } MC_COM_INIT_DATA;

    //typedef struct
    //{
    //    MC_F64 InitMaxXAxis;          // X轴正向最大限位。
    //    MC_F64 InitMaxYAxis;          // Y轴正向最大限位。
    //    MC_F64 InitMaxZAxis;          // Z轴正向最大限位。

    //    MC_F64 SwitchHeadYAxis[5];    // 四个刀座喷头切换Y坐标值，0号元素未使用。

    //    MC_F64 D_ValueSensorPlatform; // 平台和传感器高度的偏差值。

    //    MC_F64 CameraYAxis;           // 摄像头识别Y轴坐标,其中X坐标由高温或低温喷头的X坐标决定。

    //    MC_F64 AdjZ_HeadYAxis;        // 喷头Z轴对刀Y轴坐标。

    //    MC_F64 Adj_SensorYAxis;       // 传感器对高Y轴坐标。

    //    MC_F64 AdjZ_SensorHeightXAxisOffset; // 传感器对高X轴坐标偏移值。
    //    MC_F64 Adj_PlatformXAxisOffset; // 平台对高X轴坐标偏移值。
    //    MC_F64 Adj_PlatformYAxis;       // 平台对高Y轴坐标。

    //    MC_F64 ClearHighHeadYAxis;    // 高温喷头清洁Y轴坐标。
    //    MC_F64 ClearLowHeadYAxis;     // 低温喷头清洁Y轴坐标。

    //    MC_F64 Z_HeadHeight;          // Z轴对刀高度。
    //    MC_F64 Z_HeadOffsetX;         // Z轴对刀和摄像头校准补偿X坐标。

    //    MC_F64 TestAdjHighSensorXAxis;  // 对高传感器测试X坐标。
    //    MC_F64 TestAdjHighSensorYAxis;  // 对高传感器测试Y坐标。
    //    MC_F64 TestAdjHighSensorZAxis;  // 对高传感器测试Z坐标。
    //    MC_F64 TestAdjHeadXAxis;        // 对刀传感器测试X坐标。
    //    MC_F64 TestAdjHeadYAxis;        // 对刀传感器测试Y坐标。
    //    MC_F64 TestAdjHeadZAxis;        // 对刀传感器测试Z坐标。
    //    MC_F64 adjZ_HeadCameraZOffset;  // 摄像头对刀Z轴偏移。

    //    MC_COM_HEAD_SPEC HeadSpecData[256]; // 不同喷头个性化参数。
    //} MC_COM_INIT_DATA;


    void MC_ComUdcsInit(void);
    MC_BOOL MC_CoreExec(void);
    MC_COM_UDCS_DATA* MC_ComUdcsGetFlag(void);


#ifdef  __cplusplus
}
#endif

#endif // !__MC_COM_UDCS_H__
