#include "QGCodeSolid.h"

// �ж�GCode�ļ��Ƿ�ɼ���(�Ƿ����)
//     ����                       ����
//isShowWarnBox     ���ļ�������ʱ�Ƿ񵯳��Ի�����ʾ
bool QGCodeSolid::isGCodeLoadAble(bool isShowWarnBox)
{
	//if (!PathFileExists(m_strPathName_GCode))           // �ж�GCode�ļ��Ƿ����
	//{// GCode������
	//	if (isShowWarnBox)                              // ��GCode�ļ��������Ƿ񵯳��Ի�����ʾ
	//	{
	//		AfxMessageBox(_T("û���ҵ�GCode�ļ�, GCode�ļ�����ʧ��!"), MB_OK | MB_ICONINFORMATION);
	//	}
	//	SetCurrState(this, STATE_GCODE_UNLOAD);         // ����GCode����״̬,�������¼���Ϣ

	//	return false;
	//}
	return true;
}
// ����GCode�ļ�
//     ����                       ����
//isShowWarnBox     ���ļ�������ʱ�Ƿ񵯳��Ի�����ʾ
void QGCodeSolid::LoadGCode(bool isShowWarnBox)
{
	if (isGCodeLoadAble(isShowWarnBox))         // �ж�GCode�ļ��Ƿ����
	{//GCode·����ȷ 
		//if (IsThreadRunning())                  // �ж��Ƿ����ڼ���GCode�ļ�
		//{// �߳�������
		//	if (AfxMessageBox(_T("GCode�ļ�������, �Ƿ�ֹͣ?"), MB_YESNO | MB_ICONSTOP) == IDYES)
		//	{
		//		EndThread();
		//	}
		//	else
		//	{
		//		return;
		//	}
		//}
		//BeginThread();
		m_fRunFlag = true;				// ��Ϊ����Ҫ�����̲߳����У�����Ƚ��߳����б�־��Ϊtrue(���������ڷ���,��Ϊ�߳̿��ܴ���ʧ��)
		run();
	}

}