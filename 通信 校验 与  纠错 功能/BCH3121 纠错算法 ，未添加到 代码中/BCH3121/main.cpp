#include "bch3121.h"

//	ʹ��˵��
//	1����main.cpp
//	2������F7(�����������͹���)
//	3����bch3121.h��bch3121.cpp��ӵ����̣�ֱ�����г��򼴿�
//
//	Author	:	waitsha
//	QQ		:	507491840
//	E-mail	:	woijal520@163.com
//
//	��ϸ�ɲο�http://blog.csdn.net/woijal520/article/details/6790204
unsigned long test = 0xa8a0a000;
unsigned long secret = 0;
unsigned long text = 0; 

int main()
{
	secret = BchEncode(test);
	RevBit(secret,20);
	BchDecode(secret);

	secret = BchEncode(test);
	RevBit(secret,16);
	RevBit(secret,17);
	BchDecode(secret);

	secret = BchEncode(test);
	RevBit(secret,16);
	RevBit(secret,17);
	RevBit(secret,18);
	BchDecode(secret);

	return TRUE;
}
