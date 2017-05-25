#ifndef __MC_CONFIG_H__
#define __MC_CONFIG_H__

#define MC_NULL                 0
#define MC_FALSE                0
#define MC_TRUE                 1
#define CONST                   const

typedef unsigned char           MC_BOOL;
typedef char                    MC_C8;
typedef unsigned char           MC_U8;
typedef signed char             MC_S8;

typedef unsigned short int      MC_U16;
typedef unsigned int            MC_U32;
typedef unsigned long int       MC_U64;

typedef short int               MC_S16;
typedef int                     MC_S32;
typedef long int                MC_S64;

typedef float                   MC_F32;
typedef double                  MC_F64;

/** @brief The struct of MC_CODE_ID_TO_TWO_BYTE */
typedef struct
{
    MC_S8 Byte1;
    MC_S8 Byte2;
} MC_CODE_ID_TO_TWO_BYTE, MC_TEMP_TO_TWO_BYTE;

/** @brief The struct of MC_COORD_TO_FOUR_BYTE */
typedef struct
{
    MC_S8 Byte1;
    MC_S8 Byte2;
    MC_S8 Byte3;
    MC_S8 Byte4;
} MC_COORD_TO_FOUR_BYTE, MC_MOVE_SPEED_TO_FOUR_BYTE;

#define __compiler_offsetof(TYPE, MEMBER)       offsetof(TYPE, MEMBER)
#define __mc_assert                             assert
#define __mc_glue(x, y)                         x ## y                       
#define __static_mc_assert(exp)                 typedef char __mc_glue(static_assert, __LINE__) [(exp) ? 1 : -1]

#define MC_CodeOneByteToTrueValue(a)            (((MC_S8)(a)  & 0x40 ? -((MC_S8)(a) & 0x3F) : ((MC_S8)(a) & 0x3F)) )
#define MC_CodeTwoByteToTrueValue(a, b)	        (((MC_S16)(a) & 0x40 ? -((((MC_S16)(a) & 0x3F) << 7) | ((MC_S16)(b) & 0x7F)) : (((MC_S16)(a) & 0x3F) << 7) | ((MC_S16)(b) & 0x7F)) )
#define MC_CodeFourByteToTrueValue(a, b, c, d)  (((MC_S32)(a) & 0x40 ? -((((MC_S32)(a) & 0x3F) << 21) | (((MC_S32)(b) & 0x7F) << 14) | (((MC_S32)(c) & 0x7F) << 7) | ((MC_S32)(d) & 0x7F)) : (((MC_S32)(a) & 0x3F) << 21) | (((MC_S32)(b) & 0x7F) << 14) | (((MC_S32)(c) & 0x7F) << 7) | ((MC_S32)(d) & 0x7F)))
#define MC_CODE_CODE_ID_NULL                    8192
#define MC_CODE_SET_UNIT_PULSE_NULL             MC_CODE_CODE_ID_NULL
#define MC_CODE_COORD_TO_MM                     1000
#define MC_CODE_MOVE_SPEED_TO_MMS               MC_CODE_COORD_TO_MM
#define MC_CODE_ANALOG_V_TO_MA                  MC_CODE_COORD_TO_MM
#define MC_CODE_COORD_NULL                      0x07FFFFFF
#define MC_CODE_MOVE_SPEED_NULL                 MC_CODE_COORD_NULL
#define MC_CODE_ANALOG_V_NULL                   MC_CODE_COORD_NULL

#define MC_DATA_COM_SEND_BUF_NUM                100
#define MC_DATA_COM_START_FLAG			        0x80
#define MC_DATA_COM_END_FLAG			        0x81
#define MC_DATA_COM_RECE_OK                     0x82
#define MC_DATA_COM_RECE_FAIL                   0x83
#define MC_DATA_COM_SEND_FORMAT_SIZE		    24
#define MC_DATA_COM_CRC_16_GX                   0x18003             

#define MC_CODE_FORMAT_SIZE                     20
#define MC_QUEUE_CODE_BUF_NUM			        1000
#define MC_FAST_CODE_BUF_NUM                    1000
#define MC_SUPER_CODE_BUF_NUM                   1000
#define MC_CODE_WAY_QUEUE_CODE_FLAG             'Q'
#define MC_CODE_WAY_FAST_CODE_FLAG              'F'
#define MC_CODE_WAY_SUPER_CODE_FLAG				'S'

#define MC_LOCK_STATE_POWER_OFF                 0
#define MC_LOCK_STATE_POWER_ON                  1
#define MC_LOCK_STATE_POWER_DOWN                2
#define MC_LOCK_STATE_POWER_UNCHANGED           3

#define MC_UI_CODE_SIZE                         100

#define MC_ALLOW_MOT_EMPTY_CODE_NUM             2038

#define MC_GET_CODE_FROM_BUF                    0
#define MC_GET_CODE_FROM_SD_CARD                1

#define MC_ETHER_NET_IP					        "192.168.1.11"

#define MC_X_LEN_TO_PULSE                       5.0
#define MC_Y_LEN_TO_PULSE                       5.0
#define MC_Z_LEN_TO_PULSE                       5.0
#define MC_U_LEN_TO_PULSE                       5.0
#define MC_MOVE_SPEED_TO_PULSE                 (1.0 / 60.0 * 5.0)
#define MC_DEFUALT_HOME_MOVE_SPEED             (1800.0 * MC_MOVE_SPEED_TO_PULSE)

MC_CODE_ID_TO_TWO_BYTE MC_CFG_CodeIdToTwoByte(MC_S16 id);
MC_COORD_TO_FOUR_BYTE MC_CFG_CoordToFourByte(MC_S32 coord);
MC_MOVE_SPEED_TO_FOUR_BYTE MC_CFG_MoveSpeedToTourByte(MC_S32 speed);

#endif // !__MC_CONFIG_H__
