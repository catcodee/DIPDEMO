#include "stdafx.h"
#include "ImageMat.h"



ImageMat::ImageMat()
{
	Width = 0;
	Height = 0;
}

ImageMat::ImageMat(const BITMAP & bm)
{
	Create(bm.bmHeight,bm.bmWidth);
	Bitmap2Mat(bm);
}

ImageMat::ImageMat(const char * Filename)
{
	Width = 0;
	Height = 0;
	BmpLoad(Filename);
}

void ImageMat::Bitmap2Mat(const BITMAP & bm)
{
	IMAGEDATA * MatRow;
	BYTE * DataLine;
	BYTE * Data = (BYTE *)bm.bmBits;
	int WidthBytes = bm.bmWidthBytes;
	int i,j,k;
	//bmp从左下到右上
	//Mat从右上到左下
	for (i = 0; i < Height; i++)
	{
		MatRow = ColorMat[i];//矩阵第一行
		DataLine = Data + WidthBytes*i;   //即图像最上面一行
		for (j = 0; j < Width; j++)
		{
			MatRow[j].blue = DataLine[3*j+0];
			MatRow[j].green = DataLine[3*j+1];
			MatRow[j].red = DataLine[3*j+2];
		}
	}
}


void ImageMat::Create(int height,int width)
{
	int i ,j;
	Width = width;
	Height = height;
	
	ColorMat = new (IMAGEDATA * [Height]);
	GrayMat = new (BYTE * [Height]);
	for (i = 0; i < Height; i++)
	{
		ColorMat[i] = (IMAGEDATA *)new (IMAGEDATA [Width]);
		GrayMat[i] = (BYTE *)new(BYTE [Width]);
	}
}

void ImageMat::Destroy()
{
	if (Width != 0 && Height != 0)
	{
		int i = 0;
		for (i = 0; i < Height ; i++)
		{
			delete [] ColorMat[i];
			delete [] GrayMat[i];
		}
		delete [] ColorMat;
		delete [] ColorMat;
	}

}

void ImageMat::Reshape(int width,int height)
{
	if ((width != Width) | (height != Height))
	{
		Destroy();
		Create(height,width);
	}
	
}

IMAGEDATA ImageMat::GetPixelColor(int x,int y)
{
	return ColorMat[x][y];
}

BYTE ImageMat::GetPixelGray(int x,int y)
{
	return GrayMat[x][y];
}

void ImageMat::Color2Gray()
{
	int i,j;
	for (i = 0; i < Height; i++)
	{
		for (j = 0; j < Width; j++)
		{
			GrayMat[i][j] = ColorMat[i][j].red*0.3 + 0.59*ColorMat[i][j].green + 0.11*ColorMat[i][j].blue;
		}
	}
}


int ImageMat::BmpLoad(const char* Filename)
{
	BITMAPFILEHEADER strHead;
	RGBQUAD strPla[256]; //256色调色板
	BITMAPINFOHEADER strInfo;

	BITMAPFILEHEADER wtHead;
	BITMAPINFOHEADER wtInfo;
	//文件读写指针
	FILE *fpi;
	FILE *fpw;
	fpi = fopen(Filename,"rb");
	if(fpi != NULL){
		fread(&strHead.bfType,1,sizeof(WORD),fpi);
		if(0x4d42 != strHead.bfType)
		{
			cout<< "Not Bmp File!"<< endl;
			return NULL;
		}
		//读取文件头
		fread(&strHead.bfSize,1,sizeof(DWORD),fpi);
		fread(&strHead.bfReserved1,1,sizeof(WORD),fpi);
		fread(&strHead.bfReserved2,1,sizeof(WORD),fpi);
		fread(&strHead.bfOffBits,1,sizeof(DWORD),fpi);
		//读取文件信息头
		fread(&strInfo,1,sizeof(tagBITMAPINFOHEADER),fpi);

		for(unsigned int nCounti=0;nCounti<strInfo.biClrUsed;nCounti++)
		{
			//存储的时候，一般去掉保留字rgbReserved
			fread((char *)&strPla[nCounti].rgbBlue,1,sizeof(BYTE),fpi);
			fread((char *)&strPla[nCounti].rgbGreen,1,sizeof(BYTE),fpi);
			fread((char *)&strPla[nCounti].rgbRed,1,sizeof(BYTE),fpi);
			cout<<"strPla[nCounti].rgbBlue"<<strPla[nCounti].rgbBlue<<endl;
			cout<<"strPla[nCounti].rgbGreen"<<strPla[nCounti].rgbGreen<<endl;
			cout<<"strPla[nCounti].rgbRed"<<strPla[nCounti].rgbRed<<endl;
		}

		Reshape(strInfo.biWidth,strInfo.biHeight);

		int skip = 4 - ((Width * 3) % 4);
		if(skip == 4)
		{
			skip = 0;
		}
		for(int i = Height - 1; i >= 0; i--)
		{
			for(int j = 0; j< Width; j++)
			{
				fread(&ColorMat[i][j].blue,1,sizeof(BYTE),fpi);
				fread(&ColorMat[i][j].green,1,sizeof(BYTE),fpi);
				fread(&ColorMat[i][j].red,1,sizeof(BYTE),fpi);
			}
			fseek(fpi,skip,SEEK_CUR);
		}
	}
	fclose(fpi);
}

int ImageMat::BmpSave(const char* Filename, int mode)
{
	BITMAPFILEHEADER strHead;
	RGBQUAD strPla[256]; //256色调色板
	BITMAPINFOHEADER strInfo;

	BITMAPFILEHEADER wtHead;
	BITMAPINFOHEADER wtInfo;
	//文件读写指针
	FILE *fpi;
	FILE *fpw;
	if((fpw=fopen(Filename,"wb"))==NULL)
	{
		cout<<"create the bmp file error!"<<endl;
		return NULL;
	}
	int skip = 4 - ((Width * 3) % 4);
	if(skip == 4)
	{
		skip = 0;
	}

	//HEADER信息初始
	wtHead.bfType = 0x4d42;
	wtHead.bfSize = (((Width * 3) + skip)* Height)+54;
	wtHead.bfReserved1 = 0;
	wtHead.bfReserved2 = 0;
	wtHead.bfOffBits = 54;

	//INFO信息初始
	wtInfo.biSize = 40;
	wtInfo.biWidth = Width;
	wtInfo.biHeight = Height;
	wtInfo.biPlanes = 1;
	wtInfo.biBitCount = 24;
	wtInfo.biCompression = 0;
	wtInfo.biSizeImage = ((Width * 3) + skip)* Height;
	wtInfo.biXPelsPerMeter = 3780;
	wtInfo.biYPelsPerMeter = 3780;
	wtInfo.biClrUsed = 0;
	wtInfo.biClrImportant = 0;

	fwrite(&wtHead.bfType,1,sizeof(WORD),fpw);
	fwrite(&wtHead.bfSize,1,sizeof(DWORD),fpw);
	fwrite(&wtHead.bfReserved1,1,sizeof(WORD),fpw);
	fwrite(&wtHead.bfReserved2,1,sizeof(WORD),fpw);
	fwrite(&wtHead.bfOffBits,1,sizeof(DWORD),fpw);
	fwrite(&wtInfo,1,sizeof(tagBITMAPINFOHEADER),fpw);
	BYTE blank = 0;
	if(mode == 0)
	{
		for(int i = Height - 1; i>=0; i--)
		{
			for(int j = 0;j < Width;j++)
			{
				fwrite(&ColorMat[i][j].blue,1,sizeof(BYTE),fpw);
				fwrite(&ColorMat[i][j].green,1,sizeof(BYTE),fpw);
				fwrite(&ColorMat[i][j].red,1,sizeof(BYTE),fpw);
			}
			for(int k = 0;k < skip;k++)
			{
				fwrite(&blank,1,sizeof(BYTE),fpw);
			}
		}
	}
	else if(mode==1)
	{
		for(int i = Height - 1; i>=0; i--)
		{
			for(int j = 0;j < Width;j++)
			{
				fwrite(&GrayMat[i][j],1,sizeof(BYTE),fpw);
				fwrite(&GrayMat[i][j],1,sizeof(BYTE),fpw);
				fwrite(&GrayMat[i][j],1,sizeof(BYTE),fpw);
			}
			for(int k = 0;k < skip;k++)
			{
				fwrite(&blank,1,sizeof(BYTE),fpw);
			}
		}
	}
	fclose(fpw);
}	

ImageMat::~ImageMat()
{
	Destroy();
}



void ImageMat::FindConnectedDomain(vector<CONNECTDOMAIN> &C)
{
	int **LabelMat;
	BYTE **Mat = GrayMat;
	int Height = Height;
	int Width = Width;
	int i = 0 ;
	int j = 0;
	int CurrentLabelNum = 1;

	POS currentPosition;
	POS tmpPosition;
	CONNECTDOMAIN tmpConnectDomain;
	stack<POS> st;

	int x = 0;
	int y = 0;

	LabelMat = new (int * [Height]);
	for (i = 0; i < Height; i++)
		LabelMat[i] = new (int[Width]);

	for (i = 0; i < Height; i++) 
		for (j = 0; j < Width; j++)
			LabelMat = 0;

	for (i = 0; i < Height - 1; i++) //检查每个像素的左侧，正下和右侧
	{
		for (j = 1; j < Width - 1; j++)
		{
			if (Mat[i][j] == 255 && LabelMat[i][j] == 0) //未被标记的白色初始点
			{
				currentPosition.x = i;
				currentPosition.y = j;
				st.push(currentPosition); //压入初始点
				while (!st.empty())
				{
					currentPosition = st.top();
					st.pop();
					x = currentPosition.x;
					y = currentPosition.y;

					LabelMat[x][y] = CurrentLabelNum;
					tmpConnectDomain.D.push_back(currentPosition);

					if (Mat[x - 1][y] == 255 && LabelMat[x - 1][y] == 0)
					{
						tmpPosition.x = x - 1;
						tmpPosition.y = y;
						st.push(tmpPosition);
					}
					if (Mat[x][y + 1] == 255 && LabelMat[x][y + 1] == 0)
					{
						tmpPosition.x = x;
						tmpPosition.y = y + 1;
						st.push(tmpPosition);
					}
					if (Mat[x + 1][y] == 255 && LabelMat[x + 1][y] == 0)
					{
						tmpPosition.x = x + 1;
						tmpPosition.y = y;
						st.push(tmpPosition);
					}
				}
				
				C.push_back(tmpConnectDomain);
				CurrentLabelNum++;
			}
		}
	}

	for (i = 0; i < Height; i++)
		delete[] LabelMat[i];
	delete[] LabelMat;
}
