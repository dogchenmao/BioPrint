#include "QGCodeSolid.h"

// 判断GCode文件是否可加载(是否存在)
//     参数                       描述
//isShowWarnBox     若文件不存在时是否弹出对话框提示
bool QGCodeSolid::isGCodeLoadAble(bool isShowWarnBox)
{
	//if (!PathFileExists(m_strPathName_GCode))           // 判断GCode文件是否存在
	//{// GCode不存在
	//	if (isShowWarnBox)                              // 若GCode文件不存在是否弹出对话框提示
	//	{
	//		AfxMessageBox(_T("没有找到GCode文件, GCode文件加载失败!"), MB_OK | MB_ICONINFORMATION);
	//	}
	//	SetCurrState(this, STATE_GCODE_UNLOAD);         // 更新GCode加载状态,并发送事件消息

	//	return false;
	//}
	return true;
}
// 加载GCode文件
//     参数                       描述
//isShowWarnBox     若文件不存在时是否弹出对话框提示
void QGCodeSolid::LoadGCode(bool isShowWarnBox)
{
	if (isGCodeLoadAble(isShowWarnBox))         // 判断GCode文件是否存在
	{//GCode路径正确 
		//if (IsThreadRunning())                  // 判断是否正在加载GCode文件
		//{// 线程已运行
		//	if (AfxMessageBox(_T("GCode文件加载中, 是否停止?"), MB_YESNO | MB_ICONSTOP) == IDYES)
		//	{
		//		EndThread();
		//	}
		//	else
		//	{
		//		return;
		//	}
		//}
		//BeginThread();
		m_fRunFlag = true;				// 因为下面要创建线程并运行，因此先将线程运行标志置为true(这样做存在风险,因为线程可能创建失败)
		run();
	}

}