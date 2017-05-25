#ifndef __MC_GSTR_H__
#define __MC_GSTR_H__

#include "smc6200.h"
#include "mc_com_udcs.h"


#ifdef __cplusplus
extern "C" {
#endif 

    //void MC_CoreInit(void);
    void MC_CoreInit(CONST MC_COM_INIT_DATA* pInitData);
    void MC_MotContrClose(void);
    MC_BOOL MC_GStrCodeExec(const char *);


#ifdef  __cplusplus
}
#endif

#endif // !__MC_GFILE_H__
