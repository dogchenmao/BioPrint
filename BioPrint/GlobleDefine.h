#ifndef _H_GLOBLE_DEFINE_
#define _H_GLOBLE_DEFINE_

#define PT_MAX_COUNT 4	//最多支持喷头数量

const double EPSINON = 1e-5;

// 系统版本信息枚举
enum StatusInfo
{
    MAINSTATUS,
    PROGRESS_STATE,
    PROGRESS_PANE,
};

enum TimeEventStyle
{
	TIMER_ID_CAPTION,
	TIMER_ID_INFINITE,
};


enum LevelTestMode
{
    TestLevel_A,
    TestLevel_B,
    TestLevel_C,
    ZCheck,
};

// 喷头类型
enum NozzleType
{
	NozzleCold = 3,
	NozzleHot = 6,
	NozzleNormal = 9,
	NozzleUV = 5,
	NozzleNull = 0,
};

//喷头类返回值
enum RetNozzle
{
	SUCCESS = 0,
	FAIL = 1,
	NONE = -1,
};


// stl文件类型
enum STLFILETYPE
{
    NONSTLFILE = -1,                    // 非stl文件
    ASCIISTLFILE = 0,                   // ASCII码形式的stl文件
    BINSTLFILE = 1,                     // 二进制格式的stl文件
};


// 模型移动枚举
enum ModeMoveStyle
{
    MOVE_X,				    // X轴
    MOVE_Y,				    // Y轴
    MOVE_Z,				    // Z轴
    MOVE_TO_PLATFORM,		// 移动到平台
    MOVE_TO_CENTER,			// 移动到中心
};


// 模型旋转枚举
enum ModeRotateStyle
{
    X_ROTATE,               // 绕X轴旋转
    Y_ROTATE,               // 绕Y轴旋转
    Z_ROTATE,               // 绕Z轴旋转
};


// 模型缩放枚举
enum ModeScaleStyle
{
    SCALE_BY_VALUE,         // 三轴缩放
    SCALE_BY_VALUE_X,       // 根据X轴长度缩放
    SCALE_BY_VALUE_Y,       // 根据Y轴长度缩放
    SCALE_BY_VALUE_Z,       // 根据Z轴长度缩放
    SCALE_BY_VALUE_XYZ,     // 根据XYZ三轴不同比例同时缩放
};


// 在"初始校准"页面中使用
enum CMoveStyle
{
    M_CONTINOUS,                                // 连续运动(初始校准)
    M_LENGTH,                                   // 定距移动(初始校准)
};

// 在"初始校准"页面中使用
enum CLengthStyle
{
    L_LENGTH_01MM,                              // 步长0.1mm(初始校准)
    L_LENGTH_1MM,                               // 步长1mm(初始校准)
    L_LENGTH_5MM,                               // 步长5m(初始校准)
};


// 模型控制类型枚举
enum ModelControlStyle
{
	ON_MODEL_STYLE_CHANGE,			// 
	ON_MODE_SAVE		,
	ON_MODEL_RESTORE	,
	ON_MODEL_SAVE		,
	ON_MODEL_CHECK		,
	ON_MODEL_VIEW		,			    // 模型视角切换
	ON_MODEL_MOVE		,			    // 模型移动
	ON_MODEL_ROTATE		,			    // 模型旋转
	ON_MODEL_SCALE		,			    // 模型缩放
	ON_MODEL_MIRROR		,			    // 模型镜像
	ON_MODEL_SELECT     ,
	ON_MODEL_VISIABLE   ,
	ON_MODEL_VIEW_GCODE	,
	ON_MODEL_VIEW_STL	,

};
// 模型视图类型枚举
enum ModelViewStyle
{
	VIEW_FRONT = 0,			            // 主视图
	VIEW_LEFT,				            // 左视图
	VIEW_TOP,				            // 俯视图
	VIEW_DEFAULT,			            // 默认视角
};
// 机器控制类型枚举
enum MachineControlStyle
{
	MOVE_HOME,				// 未使用
	MOVE_AXES,				// 轴移动
	STOP_MOVE,				// 停止轴移动
	HOME,					// 喷头复位
	TURN_RADIOTUBE,			// 设置挤出机开关状态
	CLEAN_NODDLE,			// 清洁喷头
	Z_CHECK,				// Z轴对高
	Z_CHECK_MANUAL_TOP,		// 打印平台高度检测
	Z_CHECK_MANUAL_BOTTOM,	// 对刀仪平台高度检测
	LEVEL_TEST,				// 测试点A高度检测
	SET_TP_TOTAL,			// 设置喷头和平台温度
	SET_TP_EXTRUDER,		// 设置喷头温度(未使用)
	SET_TP_PLATEFORM,		// 设置平台温度(未使用)
	GET_TP_EXTRUDER,		// 获取喷头温度(未使用)
	GET_TP_PLATFORM,		// 获取平台温度(未使用)
    CHANGE_NODDLE,          // 切换喷头
    LOAD_NODDLE,            // 加载喷头
    REOPEN_PORT,            // 重新打开串口
};
//enum CommMessage

#define ON_COM_RECEIVE			0		// 数据接收成功
#define ON_COM_ACKSTATE_CHANGE	1		// 响应状态发生改变
#define ON_COM_FAILD			2		// COM口连接失败
#define ON_COM_NONE_PORT		3		// 无可用端口

//enum PROGRESS
#define PROGRESS_STYLE			0		//进度类型
#define PROGRESS_VALUE			1		//进度值
#define PROGRESS_CMD_VALUE_ODD	2		//剩余指令数目
#define PROGRESS_TIME_USED		3		//指令时间消耗

// 进度条更新事件枚举
enum Progress_Style
{
	//STL文件加载
	STL_LOADING = 0,					//STL文件加载
	STL_RECONSTRUCT,					//STL文件重构(未使用)
	STL_LOADED,							//STL文件加载完成
	STL_UNLOAD,							//STL文件未加载
    STL_LOADFAILED,                     //STL文件加载失败
	//GCode文件加载
	GCODE_LOADING,						//GCode文件加载
	GCODE_LOADED,						//GCode文件加载完成
	GCODE_UNLOAD,						//GCode文件记载失败
	//使用程序自带算法生成GCode
	STL_I_PATH_SLICE,					//STL文件切片
	STL_I_PATH_GENERATE,				//生成路径
	STL_I_PATH_SAVED,					//处理完成
	STL_I_PATH_UNGENERATE,				//处理失败
	//调用Python生成GCode
	STL_O_PATH_GENERATING,				//开始生成路径
	STL_O_PATH_GENERATING_LOOP,			//路径生成中
	STL_O_PATH_GENERATED,				//路径生成成功
	STL_O_PATH_UNGENERATE,				//路径生成失败
	//保存S3G文件
	S3G_SAVING,							//开始
	S3G_SAVED,							//完成
	S3G_UNSAVE,							//失败
	//打印中
	MACHINE_BUILDING,					//打印中
};

//串口命令类型枚举
enum RsCmdStyle
{
	INIT					,			// 初始化
    GET_TEMP                ,			// 获取温度
    GET_FLOW1               ,			// 获取水冷机1流量
    GET_FLOW2               ,			// 获取水冷机2流量
	SET_PLATFORM_TEMP		,			// 设置平台温度
	WAIT_TEMP				,			// 等待温度达到设定值
    FINISH_CONTROL_TEMP     ,           // 结束控温
    //SET_PRESSURE            ,		    // 改变气动模块输出压力
    AXES_STOP               ,			// 
	PAUSED					,			// 暂停
	RESUME					,			// 继续
	FILELIST				,			// 
	//SET_DIFF_Z				,           // 设置Z轴偏移值
	START_HIGHTEST  		,           // 开始平台测高(推出气缸)
	FINISH_HIGHTEST			,           // 结束平台测高(收回气缸)
	VERSION					,
	SERIALNO				,
	HOMING					,
	HOMED					,
	ENPOSITION				,
	//开始对刀
	START_ZCHECK            ,
	//对刀完成
	FINISH_ZCHECK           ,
	//测平
	TEST_START              ,
	FINISH_TEST_LEVELING    ,
	MOVE_FINISH             ,
	TEST_ZCHECK             ,
    VECT_END                ,       //!< 插补暂停
    PODIUM_END              ,       //!< 打印平台测高完成
    CAMERA_END              ,       //!< 对刀仪平台测高完成
    PRINT_END               ,       //!< 打印结束
    GET_EXTRUDE_NUM         ,       //!< 获取当前喷头编号
};
// 机器工作状态
enum MachineState
{
    MS_OFFLINE = -1,                // 设备未连接
    MS_CONNECTING,                  // 连接中
    MS_READY,                       // 设备就绪
    MS_CONTROLING,                  // 人为控制中(手动通过上位机操作XYZ轴)
    MS_BUILDING,                    // 打印中
    MS_PAUSING,                     // 暂停中
    MS_PAUSED,                      // 已暂停
    MS_WAIT_TEMP,                   // 等待达到指定温度
    MS_WAIT_HOMING,                 // 回零中
    MS_WAIT_Z_CHECK_MANUAL,         // Z轴对高中
    MS_WAIT_LEVELTEST,              // 平台水平检测中
    MS_ENDBUILDING,                 // 结束打印
    MS_DISCONNECTING,               // 断开连接中
    MS_NOZZLECHANGING,              // 切换喷头中
};

enum ACK_STATE
{
	BEERROR = 0,
	BERIGHT = 1,
	TIMEOUT = 2,
	CRCERROR = 3,
	BUFFER_OVERFLOW = 4,
	POWER_OFF_ACK = 7,
};
// 轴类型枚举
enum AxisId 
{
	/** The X axis */
	X = 0,
	/** The Y axis */
	Y = 1,
	/** The Z axis */
	Z = 2,
	/** The A axis  = traditionally, rotational around X */
	A = 3,
	/** The B axis  = traditionally, rotational around Y */
	B = 4,
	/** The C axis  = traditionally, rotational around Z */
	C = 5,
	/** The U axis  = traditionally, parallel to X */
	U = 6,
	/** The V axis  = traditionally, parallel to Y */
	V = 7,
	/** The W axis  = traditionally, parallel to Z */
	W = 8
};


//控件操作宏定义
#define DELETE_CONTROL(P) if(P) delete P
#define SHOW_CONTROL(P) P->ShowWindow(SW_SHOW)
#define MOVE_CONTROL(P, X, Y, W, H) if(P) P->MoveWindow(CRect(CPoint(X,Y), CSize(W,H)), FALSE)
#define SET_FONT(P, F) P->SetFont(F)
#define SET_ICON(IDB, IDI) ((CMFCButton*)GetDlgItem(IDB))->SetIcon( AfxGetApp()->LoadIcon(IDI))
#define ENABLEFULLTEXTTOOLTIP(IDB, isEnable) (((CMFCButton*)GetDlgItem(IDB))->EnableFullTextTooltip(isEnable))
#define SETTOOLTIP(str, IDB, IDS) str.LoadString(IDS); ((CMFCButton*)GetDlgItem(IDB))->SetTooltip(str);


#endif //_H_GLOBLE_DEFINE_