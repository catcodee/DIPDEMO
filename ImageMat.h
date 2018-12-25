#include<MVGigE.h>
#include<MVImage.h>
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<WinGDI.h>

typedef unsigned char BYTE;
typedef unsigned short WORD;
//typedef unsigned int DWORD;
typedef long LONG;
//λͼ�ļ�ͷ����;
//���в������ļ�������Ϣ�����ڽṹ����ڴ�ṹ������
//Ҫ�Ǽ��˵Ļ���������ȷ��ȡ�ļ���Ϣ��
/*typedef struct  tagBITMAPFILEHEADER{
	//WORD bfType;//�ļ����ͣ�������0x424D�����ַ���BM��
	DWORD bfSize;//�ļ���С
	WORD bfReserved1;//������
	WORD bfReserved2;//������
	DWORD bfOffBits;//���ļ�ͷ��ʵ��λͼ���ݵ�ƫ���ֽ���
}BITMAPFILEHEADER;
 
typedef struct tagBITMAPINFOHEADER{
	DWORD biSize;//��Ϣͷ��С
	LONG biWidth;//ͼ����
	LONG biHeight;//ͼ��߶�
	WORD biPlanes;//λƽ����������Ϊ1
	WORD biBitCount;//ÿ����λ��
	DWORD  biCompression; //ѹ������
	DWORD  biSizeImage; //ѹ��ͼ���С�ֽ���
	LONG  biXPelsPerMeter; //ˮƽ�ֱ���
	LONG  biYPelsPerMeter; //��ֱ�ֱ���
	DWORD  biClrUsed; //λͼʵ���õ���ɫ����
	DWORD  biClrImportant; //��λͼ����Ҫ��ɫ����
}BITMAPINFOHEADER; //λͼ��Ϣͷ����
 
typedef struct tagRGBQUAD{
	BYTE rgbBlue; //����ɫ����ɫ����
	BYTE rgbGreen; //����ɫ����ɫ����
	BYTE rgbRed; //����ɫ�ĺ�ɫ����
	BYTE rgbReserved; //����ֵ
}RGBQUAD;//��ɫ�嶨��*/
 

typedef struct tagIMAGEDATA
{
	BYTE red;
	BYTE green;
	BYTE blue;
}IMAGEDATA;

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
	~ImageMat();

};


