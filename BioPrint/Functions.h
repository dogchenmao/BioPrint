#pragma once
#ifndef _CN_SP_H_
#define _CN_SP_H_

#pragma warning( disable : 4996)

#pragma region 测试-加密解密
//	char* szSource = "test_string";
//	int nCount = strlen(szSource) ;
//	byte *szDest = new byte[nCount+ 1];
//	byte *szDeci = new byte[nCount+ 1];
//	memset(szDest, 0, nCount+ 1);
//	memset(szDeci, 0, nCount+ 1);
//
//	enciphering(szDest, (byte*)szSource, nCount,"password1");
//
//	deciphering(szDeci, (byte*)szDest, nCount,"psasword1");
//
//	delete []szDeci;
//	delete []szDest;
#pragma endregion 测试-加密解密





/*
* count the number of a character in a string
*/
static int count_char(const char *str, char c, char not)
{
	int count = 0;
	char *p = (char *)str;
	while (*p)
	{
		if (*p == c)
		{
			count++;
		}
		else if (*p == not)
		{
			break;
		}
		p++;
	}
	return count;
}
/*
* split a string into words, must free after use
*/
static int split(char ***words, const char *line, char delim, char not)
{
	int word_counter = count_char(line, delim, not) + 1;
	*words = (char **)malloc(sizeof(char *)* word_counter);
	int i = 0;
	char* p = (char*)line;

	while (1)
	{
		char* s = p;
		p = strchr(p, delim);
		int len = (p) ? p - s : strlen(s);
		(*words)[i] = (char *)malloc(sizeof(char)* (len + 1));
		strncpy((*words)[i], s, len);
		(*words)[i][len] = 0;
		if (!p) break;
		p++;
		i++;
		if (i >= word_counter)
		{
			break;
		}
	}
	return word_counter;
}



//添加一个字节参与crc计算
//[in-out]	crc
//[in]		data
static void update(unsigned char& crc, unsigned char data)
{
	crc = (crc ^ data) & 0xff; // i loathe java's promotion rules
	for (int j = 0; j < 8; j++)
	{
		if ((crc & 0x01) != 0)
		{
			crc = (((crc >> 1) & 0x7F) ^ 0x8c) & 0xff;
		}
		else
		{
			crc = ((crc >> 1) & 0x7F) & 0xff;
		}
	}
}

//计算字符串CRC
//[in]		word    需要计算CRC的字符串
//[return]			字符串的crc码
static unsigned char checkCRC(unsigned char* word)
{
	int nLen = wcslen((const wchar_t *)word);
	unsigned char crc = 0;
	for (int i = 0; i < nLen; i++)
	{
		update(crc, word[i]);
	}
	return crc;
}

//加密字符串
//[in-out]		bDest		输出加密后的字符串
//[in]			bSource		源字符串
//[in]			nCount		源字符串加密长度
//[in]			word		密码字符串
static void enciphering(unsigned char* bDest, unsigned char* bSource, int nCount, unsigned char* word)
{
	Q_ASSERT(bDest);
	Q_ASSERT(bSource);
	int nLen = wcslen((const wchar_t *)word) * 2;
	unsigned char crc = checkCRC(word);


	for (int i = 0, j = 0; i < nCount; i++, j++)
	{
		bDest[i] = bSource[i] ^ (crc ^ word[j++]);
		j %= nLen;
	}
}

//解密字符串
//[in-out]		bDest		输出解密后的字符串
//[in]			bSource		源字符串
//[in]			nCount		源字符串解密长度
//[in]			word		密码字符串
static void deciphering(unsigned char* bDest, unsigned char* bSource, int nCount, unsigned char* word)
{
	Q_ASSERT(bDest);
	Q_ASSERT(bSource);
	int nLen = wcslen((const wchar_t *)word) * 2;
	unsigned char crc = checkCRC(word);
	for (int i = 0, j = 0; i < nCount; i++, j++)
	{
		bDest[i] = (bSource[i]) ^ (crc ^ word[j++]);
		j %= nLen;
	}
}

static bool isAviliableNo(unsigned long nSource)
{
	return nSource > 10000 && nSource % 2 == 1;
}

//
//QString strSerialNo;
//unsigned long ulSerialNo = 0xab0fef;
//QString strPassword = _T("Password");
//MakeSerialNo(strSerialNo, ulSerialNo, strPassword);
//
//bool _isSerialNo = isSerialNo(strSerialNo,strPassword);
//

//static bool MakeSerialNo(QString& strDest, unsigned long nSource, QString strPassword)
//{
//	QString strSerialNo;
//	if (!isAviliableNo(nSource))
//	{
//		return false;
//	}
//	//序列号转换为字符串
//	strSerialNo = QString::number(nSource);
//	//序列号字符串加密
//	int nLength = strSerialNo.GetLength();
//	enciphering((unsigned char*)strDest.GetBuffer(nLength), (unsigned char*)strSerialNo.GetBuffer(nLength), nLength * 2, (unsigned char*)strPassword.GetBuffer());
//	strDest.ReleaseBuffer(nLength);
//	strSerialNo.ReleaseBuffer(nLength);
//	strPassword.ReleaseBuffer();
//
//	return true;
//}
//
//
//static bool isSerialNo(QString strSecSerialNo, QString strPassword)
//{
//	//序列号
//	unsigned long m_ulSerialNo = 0;
//	//解密后的序列号
//	QString strSerialNo;
//	//解密序列号
//	int nLength = strSecSerialNo.GetLength();
//	deciphering((unsigned char*)strSerialNo.GetBuffer(nLength), (unsigned char*)strSecSerialNo.GetBuffer(nLength), nLength * 2, (unsigned char*)strPassword.GetBuffer());
//	strSerialNo.ReleaseBuffer(nLength);
//	strSecSerialNo.ReleaseBuffer(nLength);
//	strPassword.ReleaseBuffer();
//	//提取序列号
//	swscanf_s(strSerialNo, _T("%x"), &m_ulSerialNo);
//	//检查序列号是否符合要求
//	return isAviliableNo(m_ulSerialNo);//大于10000 且 是奇数
//}

#endif //_CN_SP_H_