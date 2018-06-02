/////////////////////////////////////////////////////////////////////////////
//  �ļ��� : desDlg.cpp
//  ���� : des
//  ���� : enjoy5512   �޸��� : enjoy5512   ����Ż�ע���� : enjoy5512
//  ���˼������� : blog.csdn.net/enjoy5512
//  ����GitHub   : github.com/whu-enjoy
//  ���� : ���ļ�����3DES���ܵĶԻ�����Ҫʵ���ļ�,���Զ��ļ����м���,���ܽ��
//         ������ͬĿ¼��,��׺����Ϊept,Ҳ���Զ�ept�ļ����н���
//  ��Ҫ���� :
//      �Ի�����Ӧ���� :
//	void cmCheck();                                       //����ļ���׺��,ȷ��������ܻ��ǽ��ܰ�ť
//	virtual BOOL OnInitDialog();                          //�Ի����ʼ������
//	afx_msg void OnSysCommand(UINT nID, LPARAM lParam); 
//	afx_msg void OnPaint();
//	afx_msg HCURSOR OnQueryDragIcon();
//	afx_msg void OnButtonOpen();                          //���ļ�ѡ��Ի�����Ӧ����
//	afx_msg void OnDropFiles(HDROP hDropInfo);            //֧���ļ��ϷŹ�����Ӧ����
//	afx_msg void OnButtonEncrypt();                       //���ܺ���
//	afx_msg void OnSetfocusEditPsw1();                    //��ԿһEDIT���ȡ������Ӧ����
//	afx_msg void OnSetfocusEditPsw2();                    //��Կ��EDIT���ȡ������Ӧ����
//	afx_msg void OnKillfocusEditPsw1();                   //��ԿһEDIT��ʧȥ������Ӧ����
//	afx_msg void OnKillfocusEditPsw2();                   //��ԿһEDIT��ʧȥ������Ӧ����
//	afx_msg void OnButtonDecrypt();                       //���ܺ���
//
//       DES���Ա���� :
//  void ByteToBin(const unsigned char c_ucaByte[], int iaBin[], const int c_iCount);  //�ֽ�ת��Ϊ������
//  void BinToByte(const int c_iaBin[], unsigned char ucaByte[], const int c_iCount);  //������ת��Ϊ�ֽ�
//  void Replacement(const int c_iaSource[], const int c_iaReplaceTable[], int iaReplaced[], const int c_iCount);  //�����û�
//  void LeftMove(const int c_ia28Input[28], int ia28Output[28], const int c_iCount);  //��������
//  void SubKey(const int c_ia64Pwd[64], int ia16_48K[16][48]);                        //����Կ��������
//  void F(const int c_ia32A[32], const int c_ia48K[48], int ia32Output[32]);          //���ܺ���F
//  void EncryptBlock(unsigned char uc9Data[9], const int c_ia16_48K[16][48], const bool c_bFlag);  //��8�ֽ����ݼӽ���
//  //�ļ�����
//  bool FileEncrypt(const CString c_csOpenFilePath, const CString c_csSaveFilePath, const unsigned char c_uca9Pwd1[9], const unsigned char c_uca9Pwd2[9]);
//  //�ļ�����
//  bool FileDecrypt(const CString c_csOpenFilePath, CString csSaveFilePath, const unsigned char c_uca9Pwd1[9], const unsigned char c_uca9Pwd2[9]);
//
//  �汾 : ����ȷ����  ������� : 2016��5��30�� 21:35:18
//  �޸� :
//  �ο����� :
//       <<����ѧ����>> �ڶ��� �Ż��� �����˱���
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "des.h"
#include "desDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//  DES class used for Encrypt/Decrypt
class DES : public CDialog{
public:
	//������̬��Ա����
	static int s_ia56PC_1[56];             //����Կ�����㷨�е�PC1����
	static int s_ia16MoveTimes[16];        //����Կ�����㷨�е����ƴ�����
	static int s_ia48PC_2[48];             //����Կ�����㷨�е�PC2����
	static int s_ia64IP[64];               //�����㷨�еĳ�ʼ�û�IP����
	static int s_ia48E[48];                //�����㷨�е���չ�û�E����
	static int s_ia8_4_16S_Box[8][4][16];  //�����㷨�е�S��
	static int s_ia32P[32];                //�����㷨�е�P����
	static int s_ia64IP_1[64];             //�����㷨�е����ʼ�û�IP^-1����

	int ia2_16_48K[2][16][48];             //����Կ

public:
	//����˵����ʼ
	//==================================================================================
	//  ���� : ��������޷����ַ�����ת��Ϊ��Ӧ�Ķ�����,ת��c_iCount���ֽ�
	//  ���� : const unsigned char c_ucaByte[], int iaBin[], const int c_iCount
	//  (���)  c_ucaByte   : ��Ҫת�����޷����ַ�����
	//          c_iCount   : ��Ҫת�����ֽ���
	//  (����)  iaBin : ת����Ķ�������,���������鱣����
	//  ���� : ��
	//  ��Ҫ˼· : ��ÿ���ֽ�ѭ���˴�,��j��ѭ������j��,�ٽ����λ��ȡ����,���ܻ�ȡ���
	//             �ֽڵİ�λ�ϵ���������
	//  ���þ��� : unsigned char uca5Pwd[5] = "test";
	//             int ia32Bin[32];
	//             ByteToBin(uca5Pwd, ia32Bin, 4);
	//  ���� : 2016��5��30�� 19:17:10(ע������)
	//==================================================================================
	//����˵������
	void ByteToBin(const unsigned char c_ucaByte[], int iaBin[], const int c_iCount)
	{
		int i = 0;
		int j = 0;

		//ѭ��ת��c_iCount���ֽ�
		for ( i = 0; i < c_iCount; i++) 
		{
			for(j = 0; j < 8; j++)  
			{
				//��j��ѭ��ʱ,����j��,�ټ�����λ�Ƿ���1,�����,��ֵΪ1,����ֵΪ0
				if (0x80 == ((c_ucaByte[i]<<j)&0x80))
				{
					iaBin[i*8+j] = 1;
				}
				else
				{
					iaBin[i*8+j] = 0;
				}
			}
		} 
	}

	//����˵����ʼ
	//==================================================================================
	//  ���� : ������Ķ�����ת��Ϊ��Ӧ���޷����ַ�����,ת��c_iCount���ֽ�
	//  ���� : const int c_iaBin[], unsigned char ucaByte[], const int c_iCount
	//  (���)  c_iaBin : ��Ҫת���Ķ�������
	//          c_iCount     : ��Ҫת�����ֽ���
	//  (����)  ucaByte       : ת������޷����ַ�����
	//  ���� : ��
	//  ��Ҫ˼· : ��ÿ���ֽ�ѭ���˴�,��j��ѭ����ԭ����ֵ����һλ,�����µ�ֵ�ӵ����λ
	//  ���þ��� : unsigned char uca5Pwd[5] = "";
	//             int ia32Bin[32] = {0,0,1,1,0,0,0,1,0,0,1,1,0,0,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,1,0,0};
	//             BinToByte(ia32Bin, uca5Pwd, 4);
	//  ���� : 2016��5��30�� 19:24:25(ע������)
	//==================================================================================
	//����˵������
	void BinToByte(const int c_iaBin[], unsigned char ucaByte[], const int c_iCount)
	{
		int i = 0;
		int j = 0;

		//ת��c_iCount���ֽ�
		for ( i = 0; i < c_iCount; i++) 
		{
			for(j = 0; j < 8; j++)  
			{
				//ÿ�ν�ԭ����ֵ����һλ,����������ȡ��
				ucaByte[i] = ucaByte[i] * 2 + c_iaBin[i*8+j];
			}
		} 
	}

	//����˵����ʼ
	//==================================================================================
	//  ���� : ��������ĵڶ������󽫵�һ���������ת��,ת���Ľ�������ڵ�����������,
	//         ת��c_iCount������
	//  ���� : const int c_iaSource[], const int c_iaReplaceTable[]
	//         int iaReplaced[], const int c_iCount
	//  (���)  c_iaSource         : ��Ҫת���ľ���
	//          c_iaDisplaceTable  : ת���ο�����
	//          c_iCount           : ��Ҫת�������ݸ���
	//  (����)  iaReplaced         : ת����ľ���
	//  ���� : ��
	//  ��Ҫ˼· : iaReplaced����ĵ�i��λ���ϵ�����c_iaSource������
	//             ��c_iaReplaceTable[i]��λ�õ�����
	//  ���þ��� : int ia64Source[64] = {xxxxx};
	//             int ia48Replace[48] = {xxxx};
	//             int ia48Replaced[48] = {0};
	//             Replacement(ia64Source, ia48Replace, ia48Replaced, 48);
	//  ���� : 2016��5��30�� 19:39:24(ע������)
	//==================================================================================
	//����˵������
	void Replacement(const int c_iaSource[], const int c_iaReplaceTable[], int iaReplaced[], const int c_iCount)
	{
		int i = 0;
		
		//ѭ��c_iCount��
		for (i = 0; i < c_iCount; i++)
		{
			//����c_iaReplaceTable[]�û�ԭ��
			iaReplaced[i] = c_iaSource[c_iaReplaceTable[i]-1];
		}
	}

	//����˵����ʼ
	//==================================================================================
	//  ���� : ����������������������c_iCount��,��ia28Output�������ƺ�Ľ��
	//  ���� : const int c_ia28Input[28], int ia28Output[28], const int c_iCount
	//  (���)  c_ia28Input        : ��Ҫ���Ƶ�����
	//          c_iCount           : ��Ҫ���Ƶ����ݸ���
	//  (����)  ia28Output         : ���ƺ������
	//  ���� : ��
	//  ��Ҫ˼· : �Ƚ�ԭ����ǰc_iCount�����ݱ����ھֲ�����i2Temp��,Ȼ����������
	//             ǰ28-c_iCount��������c_iCountλ,�ٽ�i2Temp�е����ݽӵ����������
	//             ��������ʱ��,���������������������ͬһ������,�����ڴ�ռ�ʹ����
	//  ���þ��� : int ia28C[28] = {xxxxx};
	//             LeftMove(ia28C, ia28C, 2);
	//  ���� : 2016��5��30�� 19:49:46(ע������)
	//==================================================================================
	//����˵������
	void LeftMove(const int c_ia28Input[28], int ia28Output[28], const int c_iCount)
	{
		int i2Temp[2] = {0}; //���ڱ���Ҫ�ƶ�����������ǰc_iCount������
		int i = 0;

		//����ǰc_iCount������
		for (i = 0; i < c_iCount; i++)
		{
			i2Temp[i] = c_ia28Input[i];
		}

		//��ԭ�����28-c_iCount����ǰ��c_iCount��λ��
		for (i = 0; i < 28-c_iCount; i++)
		{
			ia28Output[i] = c_ia28Input[i+c_iCount];
		}

		//��ԭ����ǰc_iCount�����ӵ���������
		for (; i < 28; i++)
		{
			ia28Output[i] = i2Temp[c_iCount + i - 28];
		}
	}

	//����˵����ʼ
	//==================================================================================
	//  ���� : ���������64λ��Կ,���16��48λ������Կ
	//  ���� : const int c_ia64Pwd[64], int ia16_48K[16][48]
	//  (���)  c_ia64Pwd          : ����64λ��Կ
	//  (����)  ia16_64K           : 16��48λ����Կ
	//  ���� : ��
	//  ��Ҫ˼· : �Ƚ�64λ��Կͨ��PC1����õ�56λ��Կ,�ٽ���Կ��Ϊ����������,�������Ʊ�
	//             ѭ������16��,ÿ��ѭ����ϲ���56λ�м�����,Ȼ����ͨ��PC2����õ�48λ����Կ
	//  ���þ��� : int ia64Pwd[64] = {xxxxx};
	//             int ia16_48K[16][48] = {0}
	//             SubKey(ia64Pwd, ia16_48K);
	//  ���� : 2016��5��30�� 19:58:32(ע������)
	//==================================================================================
	//����˵������
	void SubKey(const int c_ia64Pwd[64], int ia16_48K[16][48])
	{
		int ia56Key[56] = {0};     //����56λ����Կ
		int ia28C[28] = {0};       //����28λ����Կ�󲿷�
		int ia28D[28] = {0};       //����28λ����Կ�Ҳ���

		int i = 0;
		int j = 0;

		//�ȴӸ�����64λ��Կ��ͨ��PC_1�����ȡ56λ����Կ
		Replacement(c_ia64Pwd, s_ia56PC_1, ia56Key, 56); 

		//�õ���Կ���Ҳ���
		for (i = 0; i < 28; i++)
		{
			ia28C[i] = ia56Key[i];
			ia28D[i] = ia56Key[28+i];
		}

		//ѭ����ȡ16����Կ
		for (i = 0; i < 16; i++)
		{
			//�ֱ��������Ҳ��ֵ���Կ
			LeftMove(ia28C,ia28C,s_ia16MoveTimes[i]);
			LeftMove(ia28D,ia28D,s_ia16MoveTimes[i]);
			
			//��Կ�ϲ�
			for (j = 0; j < 28; j++)
			{
				ia56Key[j] = ia28C[j];
				ia56Key[28+j] = ia28D[j];
			}

			//ͨ���û�ѡ��2�����ȡÿһ�ֲ�������Կ
			Replacement(ia56Key,s_ia48PC_2,ia16_48K[i],48);
		}
	}

	//����˵����ʼ
	//==================================================================================
	//  ���� : ���ܺ���,�ڵ�i�ε�����������ԿKi��Ri-1���м���
	//  ���� : const int c_ia32A[32], const int c_ia48K[48], int ia32Output[32]
	//  (���)  c_ia32A          : ����32λ����
	//          c_ia48K          : 48λ����Կ
	//  (����)  ia32Output       : 32λ���ܽ��
	//  ���� : ��
	//  ��Ҫ˼· : ����ѡ���������E���������ݽ���ѡ�������,���48λ�м���,��������
	//             48λ����Կ���,Ȼ������S��,�õ�32λ������,�������پ����û�����P,
	//             ��ÿһλ��������,�õ����ܽ��
	//  ���þ��� : int ia32Pwd[32] = {xxxxx};
	//             int ia48K[48] = {xxx}
	//             int ia32Output[32] = {0};
	//             F(ia32Pwd, ia48K, iaOutput);
	//  ���� : 2016��5��30�� 20:07:24(ע������)
	//==================================================================================
	//����˵������
	void F(const int c_ia32A[32], const int c_ia48K[48], int ia32Output[32])
	{
		int ia48Temp[48] = {0};  //48λ���м�����

		int iRow = 0;            //S�е���
		int iCol = 0;            //S�е���
		int i = 0;

		//�Ƚ�32λ����ͨ��ѡ������E��չ��48λ
		Replacement(c_ia32A, s_ia48E, ia48Temp, 48);
		
		//48λ�м���������Կ���
		for (i = 0; i < 48; i++)
		{
			ia48Temp[i] = ia48Temp[i] ^ c_ia48K[i];
		}

		//ѭ����S���л�ȡ32λ��������
		for (i = 0; i < 8; i++)
		{
			//��ȡ����
			iRow = ia48Temp[i*6]*2 + ia48Temp[i*6+5];
			iCol = ia48Temp[i*6+1]*8 + ia48Temp[i*6+2]*4 + ia48Temp[i*6+3]*2 + ia48Temp[i*6+4];

			//��ȡS���е�����,��ת������λ���
			ia48Temp[i*4+0] = (s_ia8_4_16S_Box[i][iRow][iCol]&8)/8;
			ia48Temp[i*4+1] = (s_ia8_4_16S_Box[i][iRow][iCol]&4)/4;
			ia48Temp[i*4+2] = (s_ia8_4_16S_Box[i][iRow][iCol]&2)/2;
			ia48Temp[i*4+3] = (s_ia8_4_16S_Box[i][iRow][iCol]&1);
		}

		//��S�е�32λ���ͨ��P�����ȡ���յ�32λ���
		Replacement(ia48Temp, s_ia32P, ia32Output, 32);
	}

	//����˵����ʼ
	//==================================================================================
	//  ���� : ��8�ֽڵ����ݽ��мӽ���,c_bFlagΪfalse������ܲ���,Ϊtrue������ܲ���
	//  ���� : unsigned char uc9PlainText[9], const int c_ia16_48K[16][48], const bool c_bFlag
	//  (���)  c_ia_16_48K      : 16������Կ
	//          c_bFlag          : �ӽ��ܱ�־
	//  (����)  uc9Data          : 32λ���ܽ��
	//  ���� : ��
	//  ��Ҫ˼· : �Ƚ�����İ��ֽ�����ת��Ϊ64λ������,Ȼ��64λ�����������ó�ʼ�û�
	//             ����IP����,��ȡ���Ұ벿��,Ȼ�����16�ּ���,ÿ�ּ�����,��һ�ֵ��󲿷�
	//             ����һ�ֵ��Ҳ���,Ȼ����F����ʵ����ԿK����һ���Ҳ��ּ���,�õ��Ľ����
	//             ����һ�ֵ��󲿷����,�õ���һ�ֵ��Ҳ�������,����ѭ��16��.��ʮ���ε���
	//             ������,��������󲿷ֽӵ��Ҳ�����,�õ�64λ�����,Ȼ��64λ���ݾ�����
	//             ��ʼ������IP^-1��������,�õ���������
	//  ���þ��� : unsigned char uc9Str = "12346578";
	//             int ia16_48K[16][48] = {xxx}
	//             EncryptBlock(uc9Str, ia16_48K, false);  //����
	//             EncryptBlock(uc9Str, ia16_48K, true);   //����
	//  ���� : 2016��5��30�� 20:20:41(ע������)
	//==================================================================================
	void EncryptBlock(unsigned char uc9Data[9], const int c_ia16_48K[16][48], const bool c_bFlag)
	{
		int ia64Data[64] = {0};       //���ܵ����ݵ�64λ������
		int ia64Bin[64] = {0};        //��ʱ����64λ����������
		int ia32L_BK[32] = {0};       //ÿ�ּ��ܵ��󲿷�
		int ia32R_BK[32] = {0};       //ÿ�ּ��ܵ��Ҳ���
		int ia32L[32] = {0};          //ÿ�ּ��ܽ�����󲿷�
		int ia32R[32] = {0};          //ÿ�ּ��ܽ�����Ҳ���

		int i = 0;
		int j = 0;

		//�������8�ֽ�ת����64λ������
		ByteToBin(uc9Data, ia64Data, 8);

		//��64λ����������ͨ����ʼ�û�����IP����
		Replacement(ia64Data,s_ia64IP,ia64Bin,64);

		//��ȡÿ�ּ��ܵ�64λ���ݵ����Ҳ���
		for (i = 0; i < 32; i++)
		{
			ia32L_BK[i] = ia64Bin[i];
			ia32R_BK[i] = ia64Bin[32+i];
		}

		//16�ּ���
		for (i = 0; i < 16; i++)
		{
			//��ȡÿ�ּ��ܺ���󲿷�
			for (j = 0; j < 32; j++)
			{
				ia32L[j] = ia32R_BK[j];
			}

			//���c_bFlagΪfalse,�����,Ϊtrue�����
			if (0 == c_bFlag)
			{
				F(ia32R_BK,c_ia16_48K[i],ia32R);     //����
			}
			else
			{
				F(ia32R_BK,c_ia16_48K[15-i],ia32R);  //����
			}

			//��ȡÿ�ּ��ܺ���Ҳ���
			for (j = 0; j < 32; j++)
			{
				ia32R[j] = ia32R[j] ^ ia32L_BK[j];
			}

			//���浱ǰ���Ҳ��ֵ�����
			for (j = 0; j < 32; j++)
			{
				ia32L_BK[j] = ia32L[j];
				ia32R_BK[j] = ia32R[j];
			}
		}

		//16�ּ��ܺ�,�Ѽ��ܽ�����󲿷ֽӵ��Ҳ��ֺ���
		for (i = 0; i < 32; i++)
		{
			ia64Bin[i] = ia32R[i];
			ia64Bin[i+32] = ia32L[i];
		}

		//ͨ�����ʼ������,��ȡ���ܺ��64λ����
		Replacement(ia64Bin, s_ia64IP_1, ia64Data, 64);

		//��64λ����ת��Ϊ8λ���
		BinToByte(ia64Data, uc9Data, 8);
	}

	//����˵����ʼ
	//==================================================================================
	//  ���� : ���ļ����м���
	//  ���� : const CString c_csOpenFilePath, const CString c_csSaveFilePath
	//         const unsigned char c_uca9Pwd1[9], const unsigned char c_uca9Pwd2[9]
	//  (���)  c_csOpenFilePath      : Ҫ���ܵ��ļ�·��
	//          c_csSaveFilePath      : ���ܺ���ļ�����·��
	//          c_uca9Pwd1            : ��Կһ
	//          c_uca9Pwd2            : ��Կ��
	//  (����)  ��
	//  ���� : true������ܳɹ�, false����򿪼����ļ��򴴽�������ܽ�����ļ�ʧ��
	//  ��Ҫ˼· : 1.�ȴ��ļ�ָ��
	//             2.���������������Կ,��ȡ����16*48λ������Կ
	//             3.��ȡ�����ļ�����,д�뱣���ļ���ǰ���ֽ�
	//             4.��ȡ�����ļ�����,д�뱣���ļ���9-16�ֽ�
	//             5.ѭ����ȡ�����ļ�,ÿ�ζ�ȡ���ֽ�,�ļ�β��������0��䵽8�ֽ�.
	//               ��ÿ��ѭ����,��������Կһ�����ݼ���,Ȼ������Կ�������ݽ���
	//               Ȼ��������Կһ�����ݼ���,֮�󽫼��ܺ������д���ļ�
	//  ���þ��� : CString csOpenFilePath = L"c:\test.txt";
	//             CString csSaveFilePath = L"c:\test.ept":
	//             unsigned char uca9Pwd1[9] = "12345678";
	//             unsigned char uca9Pwd2[9] = "98756412";
	//             DES CcmDes;
	//             CcmDes.FileEncrypt(csOpenFilePath, csSaveFilePath, uca9Pwd1, uca9Pwd2);
	//  ���� : 2016��5��30�� 20:36:32(ע������)
	//==================================================================================
	bool FileEncrypt(const CString c_csOpenFilePath, const CString c_csSaveFilePath, const unsigned char c_uca9Pwd1[9], const unsigned char c_uca9Pwd2[9])
	{
		CString csFileExt = L"";               //������ܺ���ļ��ĺ�׺��
		unsigned char uc9PlainText[9] = {0};   //����8�ֽڵ�����
		int ia64Bin[64] = {0};                 //����64λ�м���

		bool bStatus = true;                   //���÷���״̬Ϊtrue

		FILE *pOpenFile = NULL;                //�����ļ�ָ��
		FILE *pSaveFile = NULL;                //���ܽ���ļ�ָ��

		int iCharNum = 0;                      //��ȡ���ֽ���
		int i = 0;     
		int j = 0;
		int iFileLen = 0;                      //�����ļ�����

		//�򿪼����ļ�ָ��
		if (NULL == (pOpenFile = fopen(c_csOpenFilePath,"rb")))
		{
			MessageBox("�򿪽����ļ�ʧ�ܣ�");
			return false;
		}

		//�򿪼��ܺ���ļ�ָ��
		if (NULL == (pSaveFile = fopen(c_csSaveFilePath,"wb")))
		{
			MessageBox("�����ļ�ʧ�ܣ�");
			return false;
		}

		//��8�ֽ���Կһת��Ϊ64λ������
		ByteToBin(c_uca9Pwd1, ia64Bin, 8);
		
		//��ȡ16������Կһ
		SubKey(ia64Bin,ia2_16_48K[0]);
		
		//��8�ֽ���Կ��ת��Ϊ64λ������
		ByteToBin(c_uca9Pwd2, ia64Bin, 8);

		//��ȡ16������Կ2
		SubKey(ia64Bin,ia2_16_48K[1]);

		//���ļ�ָ���ƶ����ļ�β
		fseek(pOpenFile, 0, SEEK_END);

		//��ȡ�ļ�����
		iFileLen = ftell(pOpenFile);

		//���ļ�ָ�����û��ļ�ͷ
		fseek(pOpenFile, 0, SEEK_SET);

		//���ļ����ȱ���,Ϊ��������ֽ�,����д������
		fwrite(&iFileLen,4,1,pSaveFile);
		fwrite(&iFileLen,4,1,pSaveFile);

		//��ȡ�����ļ��ĺ�׺��
		csFileExt = c_csOpenFilePath.Mid(c_csOpenFilePath.ReverseFind('.')+1);

		//�������ļ���׺��д����ܺ���ļ�,�Ա��ڽ���ʱ�ָ�Դ�ļ�
		fwrite(csFileExt,1,8,pSaveFile);

		//���ö�ȡ���ֽ���Ϊ0
		iCharNum = 0;

		//ѭ����ȡ�����ļ�,ֱ���ļ�β
		while(0 != (iCharNum = fread(uc9PlainText,1,8,pOpenFile)))
		{
			//�����ȡ���Ĳ���8���ֽ�,˵�����ļ�β��,���0�����ֽڳ�
			if (8 != iCharNum)
			{
				for (i = iCharNum; i < 8; i++)
				{
					uc9PlainText[i] = 0;
				}
			}

			//����Կһ����
			EncryptBlock(uc9PlainText, ia2_16_48K[0], false);
			//����Կ������
			EncryptBlock(uc9PlainText, ia2_16_48K[1], true);
			//������Կһ����
			EncryptBlock(uc9PlainText, ia2_16_48K[0], false);

			//�����ܽ��д���ļ�
			fwrite(uc9PlainText, 1, 8, pSaveFile);
		}

		//�ر��ļ�ָ��,����
		fclose(pOpenFile);
		fclose(pSaveFile);
		return bStatus;
	}

	//����˵����ʼ
	//==================================================================================
	//  ���� : ���ļ����н���
	//  ���� : const CString c_csOpenFilePath, CString csSaveFilePath
	//         const unsigned char c_uca9Pwd1[9], const unsigned char c_uca9Pwd2[9]
	//  (���)  c_csOpenFilePath      : Ҫ���ܵ��ļ�·��
	//          c_uca9Pwd1            : ��Կһ
	//          c_uca9Pwd2            : ��Կ��
	//  (����)  csSaveFilePath        : ���ܺ���ļ�����·��
	//  ���� : true������ܳɹ�, false����򿪽����ļ��򴴽�������ܽ�����ļ�ʧ��
	//  ��Ҫ˼· : 1.�ȴ򿪽����ļ�ָ��
	//             2.��ȡ�����ļ�ǰ4�ֽڻ�ȡ���ܺ���ļ���С
	//             3.��ȡ�����ļ�8-16�ֽڻ�ȡ���ܺ���ļ�����
	//             4.�������ܺ���ļ�
	//             5.���������������Կ,��ȡ����16*48λ������Կ
	//             8.ѭ����ȡ�����ļ�,ÿ�ζ�ȡ���ֽ�,�ѽ��ܵ����ݳ��ȼ�8
	//               ��ÿ��ѭ����,��������Կһ�����ݽ���,Ȼ������Կ�������ݼ���
	//               Ȼ��������Կһ�����ݽ���
	//               ����ѽ��ܵ����ݳ���С���ļ���,��д����������
	//               ����,д�����ݵ�ԭ�ļ�����(ԭ�ļ�����һ����8�ֽڶ���
  //               ���Ǽ��ܺ���ļ�ȴ��䵽8�ֽڶ���״̬),���˳�����
	//  ���þ��� : CString csOpenFilePath = L"c:\test.ept";
	//             CString csSaveFilePath = L"c:\test.":
	//             unsigned char uca9Pwd1[9] = "12345678";
	//             unsigned char uca9Pwd2[9] = "98756412";
	//             DES CcmDes;
	//             CcmDes.FileDecrypt(csOpenFilePath, csSaveFilePath, uca9Pwd1, uca9Pwd2);
	//  ���� : 2016��5��30�� 20:49:46(ע������)
	//==================================================================================
	bool FileDecrypt(const CString c_csOpenFilePath, CString csSaveFilePath, const unsigned char c_uca9Pwd1[9], const unsigned char c_uca9Pwd2[9])
	{
		char ca8FileExt[8] = {0};             //������ܺ���ļ��ĺ�׺��
		unsigned char uc9PlainText[9] = {0};  //����8�ֽ�����
		int ia64PlainText[64] = {0};          //����64λ����
		int ia64Bin[64] = {0};                //����64Ϊ�м�����

		bool bStatus = true;                  //���÷���״̬Ϊtrue

		FILE *pOpenFile = NULL;               //Ҫ���ܵ��ļ�ָ��
		FILE *pSaveFile = NULL;               //���ܺ���ļ�ָ��

		int iFileLen = 0;                     //�ļ�����
		int iDecryptedCharNum = 0;            //�ѽ��ܵ����ݳ���
		int i = 0;
		int j = 0;

		//��Ҫ���ܵ��ļ�ָ��
		if (NULL == (pOpenFile = fopen(c_csOpenFilePath,"rb")))
		{
			MessageBox("�򿪽����ļ�ʧ�ܣ�");
			return false;
		}

		//��ȡҪ���ܵ��ļ�ͷ�ĸ��ֽ�,��ȡ���ܺ���ļ��ĳ���
		//��ȡ������Ϊ��8�ֽڶ���
		fread(&iFileLen,4,1,pOpenFile);
		fread(&iFileLen,4,1,pOpenFile);

		//��ȡҪ���ܵ��ļ���9-16�ֽ�����,��ȡ���ܺ���ļ���׺��
		fread(ca8FileExt,1,8,pOpenFile);

		//����׺�����ӵ����ܺ���ļ�·����
		csSaveFilePath = csSaveFilePath + ca8FileExt;

		//�򿪽��ܺ���ļ�ָ��
		if (NULL == (pSaveFile = fopen(csSaveFilePath,"wb")))
		{
			MessageBox("�����ļ�ʧ�ܣ�");
			return false;
		}

		//����Կһת��Ϊ64λ������
		ByteToBin(c_uca9Pwd1, ia64Bin, 8);

		//��ȡ16������Կһ
		SubKey(ia64Bin, ia2_16_48K[0]);

		//����Կ��ת��Ϊ64λ������
		ByteToBin(c_uca9Pwd2, ia64Bin, 8);

		//��ȡ16������Կ��
		SubKey(ia64Bin, ia2_16_48K[1]);
		
		//�����ѽ��ܵ����ݳ���Ϊ0
		iDecryptedCharNum = 0;

		//ѭ������
		while(1)
		{
			//��ȡ8�ֽ�����
			fread(uc9PlainText,1,8,pOpenFile);

			//�ѽ������ݳ��ȼ�8
			iDecryptedCharNum += 8;

			//������Կһ����
			EncryptBlock(uc9PlainText, ia2_16_48K[0], true);

			//������Կ������
			EncryptBlock(uc9PlainText, ia2_16_48K[1], false);

			//������Կһ����
			EncryptBlock(uc9PlainText, ia2_16_48K[0], true);
			
			//����ѽ��ܵ����ݳ���С���ļ���,��д����������
			//����,д�����ݵ�ԭ�ļ�����(ԭ�ļ�����һ����8�ֽڶ���
			//���Ǽ��ܺ���ļ�ȴ��䵽8�ֽڶ���״̬),���˳�����
			if (iDecryptedCharNum < iFileLen)
			{
				fwrite(uc9PlainText, 1, 8, pSaveFile);
			}
			else
			{
				fwrite(uc9PlainText, 1, 8 + iFileLen - iDecryptedCharNum, pSaveFile);
				break;
			}
		}

		//�ر��ļ�ָ��,���˳�
		fclose(pOpenFile);
		fclose(pSaveFile);
		return bStatus;
	}
};

//����Կ�����㷨�е��û�ѡ��2����
int DES::s_ia56PC_1[56] = 
{
	   57, 49, 41, 33, 25, 17,  9,
		1, 58, 50, 42, 34, 26, 18,
	   10,  2, 59, 51, 43, 35, 27,
	   19, 11,  3, 60, 52, 44, 36,

	   63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
	   14,  6, 61, 53, 45, 37, 29,
	   21, 13,  5, 28, 20, 12,  4
};

//����Կ�����㷨������λ����
int DES::s_ia16MoveTimes[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

//����Կ�����㷨�е��û�ѡ��2����
int DES::s_ia48PC_2[48] =
{
	   14, 17, 11, 24,  1,  5,
		3, 28, 15,  6, 21, 10,
	   23, 19, 12,  4, 26,  8,
	   16,  7, 27, 20, 13,  2,
	   41, 52, 31, 37, 47, 55,
	   30, 40, 51, 45, 33, 48,
	   44, 49, 39, 56, 34, 53,
	   46, 42, 50, 36, 29, 32
};

//��ʼ�û�IP����
int DES::s_ia64IP[64] = 
{
	   58, 50, 42, 34, 26, 18, 10,  2,
	   60, 52, 44, 36, 28, 20, 12,  4,
	   62, 54, 46, 38, 30, 22, 14,  6,
	   64, 56, 48, 40, 32, 24, 16,  8,
	   57, 49, 41, 33, 25, 17,  9,  1,
	   59, 51, 43, 35, 27, 19, 11,  3,
	   61, 53, 45, 37, 29, 21, 13,  5,
	   63, 55, 47, 39, 31, 23, 15,  7
};

//��չ�û�E����
int DES::s_ia48E[48] =
{
	   32,  1,  2,  3,  4,  5,
		4,  5,  6,  7,  8,  9,
		8,  9, 10, 11, 12, 13,
	   12, 13, 14, 15, 16, 17,
	   16, 17, 18, 19, 20, 21,
  	   20, 21, 22, 23, 24, 25,
	   24, 25, 26, 27, 28, 29,
	   28, 29, 30, 31, 32,  1
};

//S��
int DES::s_ia8_4_16S_Box[8][4][16] = 
{  
	//S1 
	{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},   
	{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},   
	{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},  
	{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},  
    
	//S2  
    {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},  
	{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},  
	{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},  
	{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},  
    
	//S3  
    {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},  
	{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},  
	{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},  
	{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},  
             
	//S4  
    {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},  
    {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
	{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},  
	{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},  

	//S5  
	{{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},  
	{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},  
	{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},  
	{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},  
     
	//S6  
	{{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},  
	{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},  
	{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},  
	{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},  
			  		  
	//S7  
	{{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},  
	{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},  
	{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},  
	{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},  
   
	//S8  
	{{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},  
	{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},  
	{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},  
	{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}
};

//�û�����P����
int DES::s_ia32P[32] =
{
	   16,  7, 20, 21,
	   29, 12, 28, 17,
		1, 15, 23, 26,
		5, 18, 31, 10,
		2,  8, 24, 14,
	   32, 27,  3,  9,
	   19, 13, 30,  6,
	   22, 11,  4, 25
};

//���ʼ�û�IP^-1
int DES::s_ia64IP_1[64] =
{
	   40,  8, 48, 16, 56, 24, 64, 32,
	   39,  7, 47, 15, 55, 23, 63, 31,
	   38,  6, 46, 14, 54, 22, 62, 30,
	   37,  5, 45, 13, 53, 21, 61, 29,
	   36,  4, 44, 12, 52, 20, 60, 28,
	   35,  3, 43, 11, 51, 19, 59, 27,
	   34,  2, 42, 10, 50, 18, 58, 26,
	   33,  1, 41,  9, 49, 17, 57, 25
};

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDesDlg dialog

CDesDlg::CDesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDesDlg)
	m_editPath = _T("�ļ�������·��");
	m_editPsw1 = _T("������˸��ֽڵ���Կ");
	m_editPsw2 = _T("������˸��ֽڵ���Կ");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAINFRAME);
}

void CDesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDesDlg)
	DDX_Control(pDX, IDC_BUTTON_DECRYPT, m_buttonDecrypt);
	DDX_Control(pDX, IDC_BUTTON_ENCRYPT, m_buttonEncrypt);
	DDX_Text(pDX, IDC_EDIT_PATH, m_editPath);
	DDX_Text(pDX, IDC_EDIT_PSW1, m_editPsw1);
	DDX_Text(pDX, IDC_EDIT_PSW2, m_editPsw2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDesDlg, CDialog)
	//{{AFX_MSG_MAP(CDesDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_ENCRYPT, OnButtonEncrypt)
	ON_EN_SETFOCUS(IDC_EDIT_PSW1, OnSetfocusEditPsw1)
	ON_EN_SETFOCUS(IDC_EDIT_PSW2, OnSetfocusEditPsw2)
	ON_EN_KILLFOCUS(IDC_EDIT_PSW1, OnKillfocusEditPsw1)
	ON_EN_KILLFOCUS(IDC_EDIT_PSW2, OnKillfocusEditPsw2)
	ON_BN_CLICKED(IDC_BUTTON_DECRYPT, OnButtonDecrypt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDesDlg message handlers

BOOL CDesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDesDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDesDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

	//����˵����ʼ
	//==================================================================================
	//  ���� : ��Ӧ���ļ���ť
	//  ���� : ��
	//  ���� : ��
	//  ��Ҫ˼· : ����һ��CFileDialog��,Ȼ����DoModal()�������ļ�ѡ��Ի���,��������
	//             ȷ����ť,���ȡ�ļ�·��,Ȼ�����ļ���׺���Ƿ񳬹��߸��ֽ�,���������
	//             �������û���֧����������,��������,��������ļ�·�����ֵ,Ȼ��������
	//             ��Կ�ĳ����Ƿ�Ϊ8,�����������üӽ��ܰ�ť���˳�,����ǵ�,�����ļ�����
	//  ���þ��� : ��
	//  ���� : 2016��5��30�� 20:59:18(ע������)
	//==================================================================================
	//����˵������
void CDesDlg::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	CString csFilePath = L"";                       //�����ļ�·��
	CString csPassword1 = L"";                      //������Կ1
	CString csPassword2 = L"";                      //������Կ2
	CString csFileExt = L"";                        //�����ļ���׺��

	CFileDialog CcmFileOpenDlg(TRUE,NULL,NULL,NULL,NULL,NULL);  //��ȡ���ļ��Ի������

	if (IDOK == CcmFileOpenDlg.DoModal())           //�ļ�ѡ��Ի���
	{
		csFilePath = CcmFileOpenDlg.GetPathName();  //��ȡ�ļ�·��

		//��ȡ�ļ���׺��
		csFileExt = csFilePath.Mid(csFilePath.ReverseFind('.')+1);

		//�ж��ļ���׺������,��������߸��ֽ�,����ʾ�����˳�������
		if (7 < csFileExt.GetLength())
		{
			MessageBox("��֧���߸��ֽڵĺ�׺�����ļ�\n�������������!","������ʾ");
			return;
		}

		SetDlgItemText(IDC_EDIT_PATH,csFilePath);   //����EDIT���ֵ

		//��ȡ������Կ
		GetDlgItem(IDC_EDIT_PSW1)->GetWindowText(csPassword1);
		GetDlgItem(IDC_EDIT_PSW2)->GetWindowText(csPassword2);

		//�ж���Կ����,���������Կ���ȶ�Ϊ8,������ļ������ж�,���򽫼ӽ��ܰ�ť����
		if (8 == csPassword1.GetLength() && 8 == csPassword2.GetLength())
		{
			cmCheck();
		}
		else
		{
			m_buttonEncrypt.EnableWindow(false);
			m_buttonDecrypt.EnableWindow(false);
		}
	}
}

	//����˵����ʼ
	//==================================================================================
	//  ���� : ���ļ��ϵ��Ի�����,��ȡ�ļ�·��
	//  ���� : ��
	//  ���� : ��
	//  ��Ҫ˼· : ͨ��DragQueryFile������ȡ���϶����ļ�·��,Ȼ��ת��ΪCString��.�ٻ�ȡ
	//             ������Կ,��鳤���Ƿ�Ϊ8,�����������üӽ��ܰ�ť,�����,�����ļ�
	//             ����
	//  ���þ��� : ��
	//  ���� : 2016��5��30�� 21:01:00(ע������)
	//==================================================================================
	//����˵������
void CDesDlg::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default
	char szFilePath[200] = {0};                               //�����ļ�·��
	CString csPassword1 = L"";				                  //������Կ1
	CString csPassword2 = L"";                                //������Կ2
	CString csFilePath = L"";                                 //�����ļ�·��
	CString csFileExt = L"";                                  //�����ļ���׺��

	DragQueryFile(hDropInfo,0,szFilePath,sizeof(szFilePath)); //��ȡ�ļ�·��

	//���ļ�·��ת��ΪCString����
	csFilePath.Format("%s",szFilePath);

	//��ȡ�ļ��ĺ�׺��
	csFileExt = csFilePath.Mid(csFilePath.ReverseFind('.')+1);

	//�жϺ�׺������,��������߸��ֽ�����ʾ�������û���������
	if (7 < csFileExt.GetLength())
	{
		MessageBox("��֧���߸��ֽڵĺ�׺�����ļ�\n�������������!","������ʾ");
		return;
	}


	SetDlgItemText(IDC_EDIT_PATH,csFilePath);                 //����EDIT��
	DragFinish(hDropInfo);                                    //�ϷŽ�����,�ͷ��ڴ�

	//��ȡ������Կ
	GetDlgItem(IDC_EDIT_PSW1)->GetWindowText(csPassword1);
	GetDlgItem(IDC_EDIT_PSW2)->GetWindowText(csPassword2);

	//�ж���Կ����,���������Կ���ȶ�Ϊ8,������ļ������ж�,���򽫼ӽ��ܰ�ť����
	if (8 == csPassword1.GetLength() && 8 == csPassword2.GetLength())
	{
		cmCheck();
	}
	else
	{
		m_buttonEncrypt.EnableWindow(false);
		m_buttonDecrypt.EnableWindow(false);
	}

	CDialog::OnDropFiles(hDropInfo);
}

	//����˵����ʼ
	//==================================================================================
	//  ���� : �����ڵ�һ����Կ�༭��ʱ����Ӧ����
	//  ���� : ��
	//  ���� : ��
	//  ��Ҫ˼· : ����EN_SETFOCUS��Ϣ,�ж���Կ�Ƿ��ǳ�ʼ���,�����,�����,�����˳�
	//  ���þ��� : ��
	//  ���� : 2016��5��30�� 21:04:17(ע������)
	//==================================================================================
	//����˵������
void CDesDlg::OnSetfocusEditPsw1() 
{
	// TODO: Add your control notification handler code here
	CString csStr = L"";     //�����һ����Կ

	//��ȡ��Կ
	GetDlgItem(IDC_EDIT_PSW1)->GetWindowText(csStr);

	//�����Կ�ǳ�ʼ�ַ���,�����
	if (0 == strcmp(csStr,"������˸��ֽڵ���Կ"))
	{
		SetDlgItemText(IDC_EDIT_PSW1,"");
	}
}

	//����˵����ʼ
	//==================================================================================
	//  ���� : �����ڵڶ�����Կ�༭��ʱ����Ӧ����
	//  ���� : ��
	//  ���� : ��
	//  ��Ҫ˼· : ����EN_SETFOCUS��Ϣ,�ж���Կ�Ƿ��ǳ�ʼ���,�����,�����,�����˳�
	//  ���þ��� : ��
	//  ���� : 2016��5��30�� 21:06:33(ע������)
	//==================================================================================
	//����˵������
void CDesDlg::OnSetfocusEditPsw2() 
{
	// TODO: Add your control notification handler code here
	CString csStr = L"";     //����ڶ�����Կ

	//��ȡ��Կ
	GetDlgItem(IDC_EDIT_PSW2)->GetWindowText(csStr);

	//�����Կ�ǳ�ʼ�ַ���,�����
	if (0 == strcmp(csStr,"������˸��ֽڵ���Կ"))
	{
		SetDlgItemText(IDC_EDIT_PSW2,"");
	}
}

	//����˵����ʼ
	//==================================================================================
	//  ���� : �����뿪��һ����Կ�༭��ʱ����Ӧ����
	//  ���� : ��
	//  ���� : ��
	//  ��Ҫ˼· : ����EN_KILLFOCUS��Ϣ,�ж���Կ�����Ƿ�Ϊ8,���������������Կ�༭��Ϊ
	//             ��ʼ���������,�����üӽ��ܰ�ť, �����,������Կ���ĳ���,�����Կ
	//             ������Ҳ��8,���������ļ�������,����������˳�
	//  ���þ��� : ��
	//  ���� : 2016��5��30�� 21:08:45(ע������)
	//==================================================================================
	//����˵������
void CDesDlg::OnKillfocusEditPsw1() 
{
	// TODO: Add your control notification handler code here
	CString csPassword1 = L"";            //�����һ����Կ
	CString csPassword2 = L"";            //����ڶ�����Կ

	//��ȡ������Կ
	GetDlgItem(IDC_EDIT_PSW1)->GetWindowText(csPassword1);
	GetDlgItem(IDC_EDIT_PSW2)->GetWindowText(csPassword2);

	//�������ĵ�һ����Կ���Ȳ�Ϊ8,����ʾ����˸��ֽڵ���Կ
	//�����ӽ��ܰ�ť����,����������ڶ�����Կ����
	if (8 != csPassword1.GetLength())
	{
		SetDlgItemText(IDC_EDIT_PSW1,"������˸��ֽڵ���Կ");
		m_buttonEncrypt.EnableWindow(false);
		m_buttonDecrypt.EnableWindow(false);
	}
	else
	{
		//����ڶ�����Կ�ĳ���Ҳ��8,������ļ������ж�
		if (8 == csPassword2.GetLength())
		{
			cmCheck();
		}
	}
}

	//����˵����ʼ
	//==================================================================================
	//  ���� : �����뿪�ڶ�����Կ�༭��ʱ����Ӧ����
	//  ���� : ��
	//  ���� : ��
	//  ��Ҫ˼· : ����EN_KILLFOCUS��Ϣ,�ж���Կ�����Ƿ�Ϊ8,���������������Կ�༭��Ϊ
	//             ��ʼ���������,�����üӽ��ܰ�ť, �����,������Կһ�ĳ���,�����Կ
	//             һ����Ҳ��8,���������ļ�������,����������˳�
	//  ���þ��� : ��
	//  ���� : 2016��5��30�� 21:10:09(ע������)
	//==================================================================================
	//����˵������
void CDesDlg::OnKillfocusEditPsw2() 
{
	// TODO: Add your control notification handler code here
	CString csPassword1 = L"";           //�����һ����Կ
	CString csPassword2 = L"";           //����ڶ�����Կ

	//��ȡ������Կ
	GetDlgItem(IDC_EDIT_PSW1)->GetWindowText(csPassword1);
	GetDlgItem(IDC_EDIT_PSW2)->GetWindowText(csPassword2);

	//�������ĵڶ�����Կ���Ȳ�Ϊ8,����ʾ����˸��ֽڵ���Կ
	//�����ӽ��ܰ�ť����,�����������һ����Կ����
	if (8 != csPassword2.GetLength())
	{
		SetDlgItemText(IDC_EDIT_PSW2,"������˸��ֽڵ���Կ");
		m_buttonEncrypt.EnableWindow(false);
		m_buttonDecrypt.EnableWindow(false);
	}
	else
	{
		//�����һ����Կ�ĳ���Ҳ��8,������ļ������ж�
		if (8 == csPassword1.GetLength())
		{
			cmCheck();
		}
	}
}

	//����˵����ʼ
	//==================================================================================
	//  ���� : ����ļ�����,�����ӽ��ܰ�ť�Ƿ�Ҫ������
	//  ���� : ��
	//  ���� : ��
	//  ��Ҫ˼· : ��ȡ�ļ�·��,��ȡ�ļ�����,�������ept����,��ֻ������ܰ�ť,���򼤻�ӽ��ܰ�ť
	//  ���þ��� : ��
	//  ���� : 2016��5��30�� 21:13:25(ע������)
	//==================================================================================
	//����˵������
void CDesDlg::cmCheck()
{
	CString csFilePath = L"";                 //�����ļ�·��
	CString csFileExt = L"";                  //�����ļ���չ��

	//��ȡ���ļ���·��,��ȡ���һ��.������ַ���Ϊ�ļ���׺��
	GetDlgItem(IDC_EDIT_PATH)->GetWindowText(csFilePath);
	csFileExt = csFilePath.Mid(csFilePath.ReverseFind('.')+1);

	//����ļ���׺���Ƿ���ept,�����,����Լ��ܺͽ���,�������,��ֻ�ܼ���
	if (0 != strcmp(csFileExt,"ept"))
	{
		m_buttonEncrypt.EnableWindow(true);
		m_buttonDecrypt.EnableWindow(false);
	}
	else
	{
		m_buttonEncrypt.EnableWindow(true);
		m_buttonDecrypt.EnableWindow(true);
	}
}

	//����˵����ʼ
	//==================================================================================
	//  ���� : ���ܰ�ť��Ӧ����
	//  ���� : ��
	//  ���� : ��
	//  ��Ҫ˼· : ��ȡ�����ļ�·��,Ȼ�󽫼����ļ�·����׺����Ϊept������Ϊ���ܺ���ļ�
	//             ����·��,��ȡ������Կ,����֮ǰ���浱ǰϵͳʱ��,Ȼ����ü��ܺ������ļ�
	//             ����,���ܳɹ���,��ȡϵͳʱ��,����ʱ���õ����������ĵ�ʱ��,Ȼ�󵯿�
	//             ��ʾ���ܳɹ��ͼ�������ʱ��,�������ʧ��,����ʾ����ʧ��
	//  ���þ��� : 
	//  ���� : 2016��5��30�� 21:17:04(ע������)
	//==================================================================================
	//����˵������
void CDesDlg::OnButtonEncrypt() 
{
	// TODO: Add your control notification handler code here
	unsigned char uca9Pwd1[9] = {0};       //�����һ����Կ
	unsigned char uca9Pwd2[9] = {0};       //����ڶ�����Կ
	CString csOpenFilePath = L"";          //����Ҫ���ܵ��ļ�·��
	CString csSaveFilePath = L"";          //������ܺ���ļ�·��
	CString csPassword = L"";              //������Կ
	CString csTip = L"";                   //������ʾ�ַ�
	CString csTemp = L"";                  //������ʱ�ַ���
	long lEncryptStartTime = 0;            //������ʼʱ��
	long lEncryptEndTime = 0;              //���ܽ������ʱ��
	long lTime = 0;                        //��ʱʱ�����

	DES CcmDes;                            //DES��

	//��ȡҪ���ܵ��ļ���·��
	GetDlgItem(IDC_EDIT_PATH)->GetWindowText(csOpenFilePath);
	
	//��ȡ�����ļ�·��,��ȡ���һ��.֮ǰ���ַ���,��������.ept��Ϊ���ܺ���ļ�����·��
	csSaveFilePath = csOpenFilePath.Left(csOpenFilePath.ReverseFind('.')) + ".ept";

	//��ȡ��Կһ,unsigned char���͵ı����Ѿ������ַ���������,����Ҫ����ת��
	GetDlgItem(IDC_EDIT_PSW1)->GetWindowText(csPassword);
	strncpy((char *)uca9Pwd1,csPassword,8);

	//��ȡ��Կ��
	GetDlgItem(IDC_EDIT_PSW2)->GetWindowText(csPassword);
	strncpy((char *)uca9Pwd2,csPassword,8);
	
	//��ȡ����ǰ��ϵͳʱ��
	lEncryptStartTime = GetTickCount();

	//���ü��ܺ���,���ܳɹ�����true,ʧ�ܷ���false
	if (CcmDes.FileEncrypt(csOpenFilePath, csSaveFilePath, uca9Pwd1, uca9Pwd2))
	{
		//���ܳɹ�,��ȡ���ܺ��ϵͳʱ��
		lEncryptEndTime = GetTickCount();

		//�������ʱ���
		lTime = lEncryptEndTime - lEncryptStartTime;

		//��ȡСʱ����
		csTemp.Format("���ܳɹ�!!\n���ܺķ� %dʱ",lTime/3600000);
		lTime = lTime%3600000;
		csTip = csTemp;

		//��ȡ���Ӳ���
		csTemp.Format(" %d��",lTime/60000);
		lTime = lTime%60000;
		csTip += csTemp;

		//��ȡ�벿��
		csTemp.Format(" %d��",lTime/1000);
		lTime = lTime%1000;
		csTip += csTemp;

		//��ȡ���벿��
		csTemp.Format(" %d",lTime);
		csTip += csTemp;

		//������ʾ
		MessageBox(csTip,"��ʾ");
	}
	else
	{
		//����ʧ����ʾ
		MessageBox("����ʧ��!!","��ʾ");
	}
}

	//����˵����ʼ
	//==================================================================================
	//  ���� : ���ܰ�ť��Ӧ����
	//  ���� : ��
	//  ���� : ��
	//  ��Ҫ˼· : ��ȡ�����ļ�·��,Ȼ�󽫽����ļ�·��ȥ����׺��,����(����).������Ϊ����
	//             ����ļ�����·��,��ȡ������Կ,����֮ǰ���浱ǰϵͳʱ��,Ȼ����ý���
	//             �������ļ�����,���ܳɹ���,��ȡϵͳʱ��,����ʱ���õ����������ĵ�ʱ��
	//             Ȼ�󵯿���ʾ���ܳɹ��ͽ�������ʱ��,�������ʧ��,����ʾ����ʧ��
	//  ���þ��� : 
	//  ���� : 2016��5��30�� 21:19:18(ע������)
	//==================================================================================
	//����˵������
void CDesDlg::OnButtonDecrypt() 
{
	// TODO: Add your control notification handler code here
	unsigned char uca9Pwd1[9] = {0};       //�����һ����Կ
	unsigned char uca9Pwd2[9] = {0};       //����ڶ�����Կ
	CString csOpenFilePath = L"";          //����Ҫ���ܵ��ļ�·��
	CString csSaveFilePath = L"";          //������ܺ���ļ�·��
	CString csPassword = L"";              //������Կ
	CString csTip = L"";                   //������ʾ�ַ�
	CString csTemp = L"";                  //������ʱ�ַ���
	long lEncryptStartTime = 0;            //����ʼʱ��
	long lEncryptEndTime = 0;              //���ܽ������ʱ��
	long lTime = 0;                        //��ʱʱ�����

	DES CcmDes;                            //DES��

	//��ȡҪ���ܵ��ļ���·��
	GetDlgItem(IDC_EDIT_PATH)->GetWindowText(csOpenFilePath);
	
	//��ȡ�����ļ�·��,��ȡ���һ��.֮ǰ���ַ���,��������(����).��Ϊ���ܺ���ļ�����·��
	//�ڽ��ܺ������ȡ���ܺ󱣴��ļ��ĺ�׺��
	csSaveFilePath = csOpenFilePath.Left(csOpenFilePath.ReverseFind('.')) + "(����).";

	//��ȡ��Կһ,unsigned char���͵ı����Ѿ������ַ���������,����Ҫ����ת��
	GetDlgItem(IDC_EDIT_PSW1)->GetWindowText(csPassword);
	strncpy((char *)uca9Pwd1,csPassword,8);

	//��ȡ��Կ��
	GetDlgItem(IDC_EDIT_PSW2)->GetWindowText(csPassword);
	strncpy((char *)uca9Pwd2,csPassword,8);
	
	//��ȡ����ǰ��ϵͳʱ��
	lEncryptStartTime = GetTickCount();

	//���ý��ܺ���,���ܳɹ�����true,ʧ�ܷ���false
	if (CcmDes.FileDecrypt(csOpenFilePath, csSaveFilePath, uca9Pwd1, uca9Pwd2))
	{
		//���ܳɹ�,��ȡ���ܺ��ϵͳʱ��
		lEncryptEndTime = GetTickCount();

		//�������ʱ���
		lTime = lEncryptEndTime - lEncryptStartTime;

		//��ȡСʱ����
		csTemp.Format("���ܳɹ�!!\n���ܺķ� %dʱ",lTime/3600000);
		lTime = lTime%3600000;
		csTip = csTemp;

		//��ȡ���Ӳ���
		csTemp.Format(" %d��",lTime/60000);
		lTime = lTime%60000;
		csTip += csTemp;

		//��ȡ�벿��
		csTemp.Format(" %d��",lTime/1000);
		lTime = lTime%1000;
		csTip += csTemp;

		//��ȡ���벿��
		csTemp.Format(" %d",lTime);
		csTip += csTemp;

		//������ʾ
		MessageBox(csTip,"��ʾ");
	}
	else
	{
		//����ʧ����ʾ
		MessageBox("����ʧ��!!","��ʾ");
	}
}