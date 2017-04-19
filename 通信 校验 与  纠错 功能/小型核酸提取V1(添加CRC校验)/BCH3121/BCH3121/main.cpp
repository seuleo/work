#include "bch3121.h"

//	使用说明
//	1、打开main.cpp
//	2、按下F7(建立工作区和工程)
//	3、将bch3121.h和bch3121.cpp添加到工程，直接运行程序即可
//
//	Author	:	waitsha
//	QQ		:	507491840
//	E-mail	:	woijal520@163.com
//
//	详细可参考http://blog.csdn.net/woijal520/article/details/6790204
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
