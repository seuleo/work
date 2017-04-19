#include "BCH3121.h"
#include <stdio.h>
#include <memory.h>

char GeneraPloy[BCH_LENGTH_GENERATPLOY] =	//	BCH(31,21)的生成多项式
{1,1,1,0,1,1,0,1,0,0,1};					//	x^10+x^9+x^8+x^6+x^5+x^3^+1，即1110 1101 001

char h[BCH_LENGTH_GENERATPLOY-1][BCH_LENGTH_CODEWORD-1]=
{
	1,0,0,1,0,1,0,0,1,0,0,1,1,1,1,0,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,
	1,1,0,1,1,1,1,0,1,1,0,1,0,0,0,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,
	1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,
	0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,
	1,0,1,0,1,0,1,0,0,1,1,0,0,0,1,1,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,
	1,1,0,0,0,0,0,1,1,0,1,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,
	0,1,1,0,0,0,0,0,1,1,0,1,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,0,0,0,
	1,0,1,0,0,1,0,0,1,1,1,1,0,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,1,0,0,
	0,1,0,1,0,0,1,0,0,1,1,1,1,0,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,1,0,
	0,0,1,0,1,0,0,1,0,0,1,1,1,1,0,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,1
};

//---------------------------------------------------------
//	
//	对原始数据的某连续的20个位进行编码
//	source	:
//				最前面21位为需要进行编码的内容
//				应该是一个四字节大小的数据的首地址
//	返回	:
//				最前面21位为参数传递的信息+10的BCH校验码+1位奇偶校验位
//
//---------------------------------------------------------
ulong BchEncode(ulong da)
{
	ulong value = 0;						//	返回值
	uchar ret[BCH_LENGTH_CODEWORD];			//	每次迭代过程的校验结果
	uchar data[BCH_LENGTH_CODEWORD];		//	将参数的位映射成字节便于引用

	memset(ret,0,BCH_LENGTH_CODEWORD);
	memset(data,0,BCH_LENGTH_CODEWORD);
	
	Long2Bytes(da,data);					//	构造与数据对应的32个值的字节型数组
	memcpy(ret,data,BCH_LENGTH_GENERATPLOY);//	循环进行迭代求校验值的运算

	for(int k=0;k<BCH_LENGTH_INFO;k++)
	{
		BCHXor(data+k,ret+k,k);
		ret[BCH_LENGTH_GENERATPLOY+k] = data[BCH_LENGTH_GENERATPLOY+k];
	}

	for(;k<BCH_LENGTH_CODEWORD;k++)			//	将校验值添加到原始数据末尾
		data[k] = ret[k];
	for(k=0;k<BCH_LENGTH_CODEWORD-1;k++)	//	将奇偶校验值添加到原始数据末尾
		data[BCH_LENGTH_CODEWORD-1] ^= data[k]; 

	for(k=0;k<BCH_LENGTH_CODEWORD;k++)		//	根据数组构造返回值
	{
		if(data[k] == 1)
			value |= 1 << (BCH_LENGTH_CODEWORD-1-k);
	}
	return value;
}

//---------------------------------------------------------
//	
//	执行encode的逆向操作
//	此函数只执行数据是否出错的校验工作，而不对数据进行修正
//	source	:
//				接收到的原始数据
//				应该是一个四字节大小的数据的首地址
//	check	:
//				接收到的数据的伴随式
//	返回	:
//				1		数据没有发生错误
//				0		数据发生了错误
//---------------------------------------------------------
uchar	BchCheck(ulong da,	uchar *check)
{
	uchar data[BCH_LENGTH_CODEWORD];
	
	memset(data,0,BCH_LENGTH_CODEWORD);
	memset(check,0,BCH_LENGTH_CHECKCODE);

	Long2Bytes(da,data);

	int r;	//	矩阵的行索引
	int c;	//	矩阵的列索引
	for(r=0;r<BCH_LENGTH_CHECKCODE;r++)
	{
		for(c=0;c<BCH_LENGTH_CODEWORD-1;c++)
			check[r] ^= (data[c] && h[r][c]);
	}

	for(c=0;c<BCH_LENGTH_CHECKCODE;c++)
		if(check[c] != 0)
			return FALSE;
	return TRUE;
}

//---------------------------------------------------------
//	
//	对接收到的数据进行译码
//	source	:
//				应该是一个四字节大小的数据的首地址
//	返回	:
//				修正以后的正确结果
//				最前面21位为参数传递的信息，后面的11位用'0'填充
//---------------------------------------------------------
ulong BchDecode(ulong data)
{
	uchar c,r;
	uchar Erroroccur = FALSE;
	uchar check[BCH_LENGTH_CHECKCODE];

	if(TRUE == BchCheck(data,check))			//	data no error
		return data & 0xfffff800;				//	return the front 21 bits
	else										//	data with error
	{
		for(c=0;c<BCH_LENGTH_INFO;c++)
		{
			for(r=0;r<BCH_LENGTH_CHECKCODE;r++)
			{
				if(h[r][c] == check[r])
					Erroroccur = TRUE;
				else
				{
					Erroroccur = FALSE;
					break;
				}
			}
			if(TRUE == Erroroccur)
			{
				RevBit(data,(31-c));
				printf("Error occur at %d(th) bit!\n",31-c);
				data &= 0xfffff800;
				return data;
			}
		}
		for(c=0;c<BCH_LENGTH_INFO;c++)
		{
			for(r=c;r<BCH_LENGTH_INFO;r++)
			{
				for(int e=0;e<BCH_LENGTH_CHECKCODE;e++)
				{
					if(check[e] == (h[e][c] ^ h[e][r]))
						Erroroccur = TRUE;
					else
					{
						Erroroccur = FALSE;
						break;
					}
				}
				if(Erroroccur == TRUE)
				{
					RevBit(data,(31-c));
					RevBit(data,(31-r));
					printf("Error occur at %d(th) and %d(th) bit!\n",31-c,31-r);
					data &= 0xfffff800;
					return data;
				}
			}
		}
	}
	printf("More than 2 error occured or the checkcode is not right!\n");
	return 0xffffffff;
}

//---------------------------------------------------------
//	
//	BCH产生校验码过程中对位进行异或去处的迭代处理过程
//                 --------------------------------------------	
// 1110 1101 001  /0100 0011 0000 1100 0011 0000 0000 0000		//	数据1
//                 1110 1101 001								//	数据2
//               -------------------------------------------
//                 0110 1011 001								//	数据3
//	数据是常量，用全局变量控制
//	data	:	
//				数据1的前面BCH_LENGTH_GENERATPLOY位的首地址
//	ret		:
//				数据3的首地址
//
//---------------------------------------------------------


void BCHXor(uchar *data,uchar *ret,uchar begin)
{
	if(*ret == 0)
		return;
	for(int a=0,i=0;i<BCH_LENGTH_GENERATPLOY;i++)
		ret[i] ^= GeneraPloy[a++];
}

//---------------------------------------------------------
//	
//	将长整型的数据转换为一个0/1形式长度为32的数据
//	data的最高位转换后成为array的第一个元素
//
//---------------------------------------------------------
void Long2Bytes(ulong data,uchar* array)
{

	for(int i=0;i<BCH_LENGTH_CODEWORD;i++)	//	参数位表示与data数组左右顺序一致
	{										//	即*source的最高位与data[0]对应
		if(0x80000000 & (data << i))
			array[i] = 1;
	}
}