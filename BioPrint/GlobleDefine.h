#ifndef _H_GLOBLE_DEFINE_
#define _H_GLOBLE_DEFINE_

#define PT_MAX_COUNT 4	//���֧����ͷ����

const double EPSINON = 1e-5;

// ϵͳ�汾��Ϣö��
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

// ��ͷ����
enum NozzleType
{
	NozzleCold = 3,
	NozzleHot = 6,
	NozzleNormal = 9,
	NozzleUV = 5,
	NozzleNull = 0,
};

//��ͷ�෵��ֵ
enum RetNozzle
{
	SUCCESS = 0,
	FAIL = 1,
	NONE = -1,
};


// stl�ļ�����
enum STLFILETYPE
{
    NONSTLFILE = -1,                    // ��stl�ļ�
    ASCIISTLFILE = 0,                   // ASCII����ʽ��stl�ļ�
    BINSTLFILE = 1,                     // �����Ƹ�ʽ��stl�ļ�
};


// ģ���ƶ�ö��
enum ModeMoveStyle
{
    MOVE_X,				    // X��
    MOVE_Y,				    // Y��
    MOVE_Z,				    // Z��
    MOVE_TO_PLATFORM,		// �ƶ���ƽ̨
    MOVE_TO_CENTER,			// �ƶ�������
};


// ģ����תö��
enum ModeRotateStyle
{
    X_ROTATE,               // ��X����ת
    Y_ROTATE,               // ��Y����ת
    Z_ROTATE,               // ��Z����ת
};


// ģ������ö��
enum ModeScaleStyle
{
    SCALE_BY_VALUE,         // ��������
    SCALE_BY_VALUE_X,       // ����X�᳤������
    SCALE_BY_VALUE_Y,       // ����Y�᳤������
    SCALE_BY_VALUE_Z,       // ����Z�᳤������
    SCALE_BY_VALUE_XYZ,     // ����XYZ���᲻ͬ����ͬʱ����
};


// ��"��ʼУ׼"ҳ����ʹ��
enum CMoveStyle
{
    M_CONTINOUS,                                // �����˶�(��ʼУ׼)
    M_LENGTH,                                   // �����ƶ�(��ʼУ׼)
};

// ��"��ʼУ׼"ҳ����ʹ��
enum CLengthStyle
{
    L_LENGTH_01MM,                              // ����0.1mm(��ʼУ׼)
    L_LENGTH_1MM,                               // ����1mm(��ʼУ׼)
    L_LENGTH_5MM,                               // ����5m(��ʼУ׼)
};


// ģ�Ϳ�������ö��
enum ModelControlStyle
{
	ON_MODEL_STYLE_CHANGE,			// 
	ON_MODE_SAVE		,
	ON_MODEL_RESTORE	,
	ON_MODEL_SAVE		,
	ON_MODEL_CHECK		,
	ON_MODEL_VIEW		,			    // ģ���ӽ��л�
	ON_MODEL_MOVE		,			    // ģ���ƶ�
	ON_MODEL_ROTATE		,			    // ģ����ת
	ON_MODEL_SCALE		,			    // ģ������
	ON_MODEL_MIRROR		,			    // ģ�;���
	ON_MODEL_SELECT     ,
	ON_MODEL_VISIABLE   ,
	ON_MODEL_VIEW_GCODE	,
	ON_MODEL_VIEW_STL	,

};
// ģ����ͼ����ö��
enum ModelViewStyle
{
	VIEW_FRONT = 0,			            // ����ͼ
	VIEW_LEFT,				            // ����ͼ
	VIEW_TOP,				            // ����ͼ
	VIEW_DEFAULT,			            // Ĭ���ӽ�
};
// ������������ö��
enum MachineControlStyle
{
	MOVE_HOME,				// δʹ��
	MOVE_AXES,				// ���ƶ�
	STOP_MOVE,				// ֹͣ���ƶ�
	HOME,					// ��ͷ��λ
	TURN_RADIOTUBE,			// ���ü���������״̬
	CLEAN_NODDLE,			// �����ͷ
	Z_CHECK,				// Z��Ը�
	Z_CHECK_MANUAL_TOP,		// ��ӡƽ̨�߶ȼ��
	Z_CHECK_MANUAL_BOTTOM,	// �Ե���ƽ̨�߶ȼ��
	LEVEL_TEST,				// ���Ե�A�߶ȼ��
	SET_TP_TOTAL,			// ������ͷ��ƽ̨�¶�
	SET_TP_EXTRUDER,		// ������ͷ�¶�(δʹ��)
	SET_TP_PLATEFORM,		// ����ƽ̨�¶�(δʹ��)
	GET_TP_EXTRUDER,		// ��ȡ��ͷ�¶�(δʹ��)
	GET_TP_PLATFORM,		// ��ȡƽ̨�¶�(δʹ��)
    CHANGE_NODDLE,          // �л���ͷ
    LOAD_NODDLE,            // ������ͷ
    REOPEN_PORT,            // ���´򿪴���
};
//enum CommMessage

#define ON_COM_RECEIVE			0		// ���ݽ��ճɹ�
#define ON_COM_ACKSTATE_CHANGE	1		// ��Ӧ״̬�����ı�
#define ON_COM_FAILD			2		// COM������ʧ��
#define ON_COM_NONE_PORT		3		// �޿��ö˿�

//enum PROGRESS
#define PROGRESS_STYLE			0		//��������
#define PROGRESS_VALUE			1		//����ֵ
#define PROGRESS_CMD_VALUE_ODD	2		//ʣ��ָ����Ŀ
#define PROGRESS_TIME_USED		3		//ָ��ʱ������

// �����������¼�ö��
enum Progress_Style
{
	//STL�ļ�����
	STL_LOADING = 0,					//STL�ļ�����
	STL_RECONSTRUCT,					//STL�ļ��ع�(δʹ��)
	STL_LOADED,							//STL�ļ��������
	STL_UNLOAD,							//STL�ļ�δ����
    STL_LOADFAILED,                     //STL�ļ�����ʧ��
	//GCode�ļ�����
	GCODE_LOADING,						//GCode�ļ�����
	GCODE_LOADED,						//GCode�ļ��������
	GCODE_UNLOAD,						//GCode�ļ�����ʧ��
	//ʹ�ó����Դ��㷨����GCode
	STL_I_PATH_SLICE,					//STL�ļ���Ƭ
	STL_I_PATH_GENERATE,				//����·��
	STL_I_PATH_SAVED,					//�������
	STL_I_PATH_UNGENERATE,				//����ʧ��
	//����Python����GCode
	STL_O_PATH_GENERATING,				//��ʼ����·��
	STL_O_PATH_GENERATING_LOOP,			//·��������
	STL_O_PATH_GENERATED,				//·�����ɳɹ�
	STL_O_PATH_UNGENERATE,				//·������ʧ��
	//����S3G�ļ�
	S3G_SAVING,							//��ʼ
	S3G_SAVED,							//���
	S3G_UNSAVE,							//ʧ��
	//��ӡ��
	MACHINE_BUILDING,					//��ӡ��
};

//������������ö��
enum RsCmdStyle
{
	INIT					,			// ��ʼ��
    GET_TEMP                ,			// ��ȡ�¶�
    GET_FLOW1               ,			// ��ȡˮ���1����
    GET_FLOW2               ,			// ��ȡˮ���2����
	SET_PLATFORM_TEMP		,			// ����ƽ̨�¶�
	WAIT_TEMP				,			// �ȴ��¶ȴﵽ�趨ֵ
    FINISH_CONTROL_TEMP     ,           // ��������
    //SET_PRESSURE            ,		    // �ı�����ģ�����ѹ��
    AXES_STOP               ,			// 
	PAUSED					,			// ��ͣ
	RESUME					,			// ����
	FILELIST				,			// 
	//SET_DIFF_Z				,           // ����Z��ƫ��ֵ
	START_HIGHTEST  		,           // ��ʼƽ̨���(�Ƴ�����)
	FINISH_HIGHTEST			,           // ����ƽ̨���(�ջ�����)
	VERSION					,
	SERIALNO				,
	HOMING					,
	HOMED					,
	ENPOSITION				,
	//��ʼ�Ե�
	START_ZCHECK            ,
	//�Ե����
	FINISH_ZCHECK           ,
	//��ƽ
	TEST_START              ,
	FINISH_TEST_LEVELING    ,
	MOVE_FINISH             ,
	TEST_ZCHECK             ,
    VECT_END                ,       //!< �岹��ͣ
    PODIUM_END              ,       //!< ��ӡƽ̨������
    CAMERA_END              ,       //!< �Ե���ƽ̨������
    PRINT_END               ,       //!< ��ӡ����
    GET_EXTRUDE_NUM         ,       //!< ��ȡ��ǰ��ͷ���
};
// ��������״̬
enum MachineState
{
    MS_OFFLINE = -1,                // �豸δ����
    MS_CONNECTING,                  // ������
    MS_READY,                       // �豸����
    MS_CONTROLING,                  // ��Ϊ������(�ֶ�ͨ����λ������XYZ��)
    MS_BUILDING,                    // ��ӡ��
    MS_PAUSING,                     // ��ͣ��
    MS_PAUSED,                      // ����ͣ
    MS_WAIT_TEMP,                   // �ȴ��ﵽָ���¶�
    MS_WAIT_HOMING,                 // ������
    MS_WAIT_Z_CHECK_MANUAL,         // Z��Ը���
    MS_WAIT_LEVELTEST,              // ƽ̨ˮƽ�����
    MS_ENDBUILDING,                 // ������ӡ
    MS_DISCONNECTING,               // �Ͽ�������
    MS_NOZZLECHANGING,              // �л���ͷ��
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
// ������ö��
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


//�ؼ������궨��
#define DELETE_CONTROL(P) if(P) delete P
#define SHOW_CONTROL(P) P->ShowWindow(SW_SHOW)
#define MOVE_CONTROL(P, X, Y, W, H) if(P) P->MoveWindow(CRect(CPoint(X,Y), CSize(W,H)), FALSE)
#define SET_FONT(P, F) P->SetFont(F)
#define SET_ICON(IDB, IDI) ((CMFCButton*)GetDlgItem(IDB))->SetIcon( AfxGetApp()->LoadIcon(IDI))
#define ENABLEFULLTEXTTOOLTIP(IDB, isEnable) (((CMFCButton*)GetDlgItem(IDB))->EnableFullTextTooltip(isEnable))
#define SETTOOLTIP(str, IDB, IDS) str.LoadString(IDS); ((CMFCButton*)GetDlgItem(IDB))->SetTooltip(str);


#endif //_H_GLOBLE_DEFINE_