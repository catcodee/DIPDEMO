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
//位图文件头定义;
//其中不包含文件类型信息（由于结构体的内存结构决定，
//要是加了的话将不能正确读取文件信息）
/*typedef struct  tagBITMAPFILEHEADER{
	//WORD bfType;//文件类型，必须是0x424D，即字符“BM”
	DWORD bfSize;//文件大小
	WORD bfReserved1;//保留字
	WORD bfReserved2;//保留字
	DWORD bfOffBits;//从文件头到实际位图数据的偏移字节数
}BITMAPFILEHEADER;
 
typedef struct tagBITMAPINFOHEADER{
	DWORD biSize;//信息头大小
	LONG biWidth;//图像宽度
	LONG biHeight;//图像高度
	WORD biPlanes;//位平面数，必须为1
	WORD biBitCount;//每像素位数
	DWORD  biCompression; //压缩类型
	DWORD  biSizeImage; //压缩图像大小字节数
	LONG  biXPelsPerMeter; //水平分辨率
	LONG  biYPelsPerMeter; //垂直分辨率
	DWORD  biClrUsed; //位图实际用到的色彩数
	DWORD  biClrImportant; //本位图中重要的色彩数
}BITMAPINFOHEADER; //位图信息头定义
 
typedef struct tagRGBQUAD{
	BYTE rgbBlue; //该颜色的蓝色分量
	BYTE rgbGreen; //该颜色的绿色分量
	BYTE rgbRed; //该颜色的红色分量
	BYTE rgbReserved; //保留值
}RGBQUAD;//调色板定义*/
 

typedef struct tagIMAGEDATA
{
	BYTE red;
	BYTE green;
	BYTE blue;
}IMAGEDATA;

class ImageMat {
private:

	int   Width;             //矩阵的宽
	int   Height;            //矩阵的高

	IMAGEDATA **  ColorMat;  //有颜色
	BYTE **  GrayMat;        //无颜色
		
	
public:

	/*!
	 *  \brief 构函
	 *  \param [in]	BITMAP结构图像数据
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
	 *  \brief 将Bitmap结构转化为矩阵形式
	 *  \param [in]	BITMAP结构图像数据
	 *  \retval  	
	 *  \note 
	 */
	void Bitmap2Mat(const BITMAP & bm);

	/*!
	 *  \brief 将bmp格式图像文件加载为
	 *  \param [in]	BITMAP结构图像数据
	 *  \retval  	
	 *  \note 16位和48位图像仅在保存为.tif格式时，保留16位或48位位深。保存为bmp,jpg均被转换为8位或24位图像保存。
	 */
	void Color2Gray();
	int BmpLoad(const char * Filename);
	int BmpSave(const char * Filename,int mode);
	IMAGEDATA GetPixelColor(int x,int y);
	BYTE GetPixelGray(int x,int y);
	~ImageMat();

};


