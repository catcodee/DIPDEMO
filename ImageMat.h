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
	void FindConnectedDomain(vector<CONNECTDOMAIN> &C);
	void FullFill(vector<CONNECTDOMAIN> &C);
	~ImageMat();

};



