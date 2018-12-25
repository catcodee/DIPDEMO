#include<MVGigE.h>
#include<MVImage.h>
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<WinGDI.h>
#include<stack>
#include<vector>
using namespace std;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef long LONG;
 
typedef struct tagIMAGEDATA
{
	BYTE red;
	BYTE green;
	BYTE blue;
}IMAGEDATA;

typedef struct tagPosition
{
	int x;
	int y;
}POS;

typedef struct tagConnenctedDomain
{
	vector<POS> D;
	int Label;
}CONNECTDOMAIN;

class ImageMat {
private:

	int   Width;             //����Ŀ�
	int   Height;            //����ĸ�

	IMAGEDATA **  ColorMat;  //����ɫ
	BYTE **  GrayMat;        //����ɫ
		
	
public:

	/*!
	 *  \brief ����
	 *  \param [in]	BITMAP�ṹͼ������
	 *  \retval  	
	 *  \note 
	 */
	ImageMat();
	ImageMat(const BITMAP & bm);
	ImageMat(const char * Filename);
	void Create(int height,int width);
	void Destroy();
	void Reshape(int width,int height);
	/*!
	 *  \brief ��Bitmap�ṹת��Ϊ������ʽ
	 *  \param [in]	BITMAP�ṹͼ������
	 *  \retval  	
	 *  \note 
	 */
	void Bitmap2Mat(const BITMAP & bm);

	/*!
	 *  \brief ��bmp��ʽͼ���ļ�����Ϊ
	 *  \param [in]	BITMAP�ṹͼ������
	 *  \retval  	
	 *  \note 16λ��48λͼ����ڱ���Ϊ.tif��ʽʱ������16λ��48λλ�����Ϊbmp,jpg����ת��Ϊ8λ��24λͼ�񱣴档
	 */
	void Color2Gray();
	int BmpLoad(const char * Filename);
	int BmpSave(const char * Filename,int mode);
	
	IMAGEDATA GetPixelColor(int x,int y);
	BYTE GetPixelGray(int x,int y);
	void FindConnectedDomain(vector<CONNECTDOMAIN> &C);
	void FullFill(vector<CONNECTDOMAIN> &C);
	~ImageMat();

};



