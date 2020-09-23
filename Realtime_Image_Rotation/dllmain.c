/* Standalone Rotation Function 
AlphaBlending, TransparentColor, Scaling, Hue, (Saturation, Luminocity)
Author: Lefteris Eleftheriades
Thanks to: keith(LaVolpe) - for helping me optimize the code
Akiti Yadav - for reporting a bug (fixed)
been_lucky, pietro ing. cecchi, Agustin Rodriguez,
Mark, Steppenwolfe -for supporting the first posting

Created with DevC++ 4.9.9.2
*/

//project options>parameters>Linker
//-lgdi32
#pragma comment(linker, "/DEFAULTLIB:kernel32.lib /DEFAULTLIB:gdi32.lib")

#include "dll.h"
#include "cc.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BPC 4 //Weird behaviour if set to 3Bytes per color
#define LEFT BPC
#define FAILED_GETTING_BACKGROUND_BITS -1
#define FAILED_GETTING_IMAGE_BITS -2
#define FAILED_TO_ALLOCATE_MEMORY -3
#define FAILED_TO_DRAWIMAGE -4
double norm(double);
double enclose(double a);

__declspec (dllexport) int __stdcall rotatedc(HDC DestDC, float Angle, int x, int y, int w, int h, HDC SrcDC, int srcx, int srcy, float pScale, int TranspColor, float Alpha, float Hue, float Sat, float Lum){
	int px, py, CX, CY, XX, YY, ix, iy, dw, dh;
	BYTE *BackgroundImg, *OriginalImg, *RotatedImg, *TransparancyMap;
	BYTE tR, tG, tB;
	BITMAPINFO BackBmp, PicBmp, RotBmp; 
	HDC BackDC, PicDC;
	HBITMAP iBitmap, ImgHandle;
	HGDIOBJ iOldPicDCBitmap, iOldBackDCBitmap;

	LPBYTE pBits;
	double PCos, PSin, tx, ty, dx, dy, hh, ss, vv, rr, gg, bb;
	double TopL, TopR, BotL, BotR, TopLV, TopRV, BotLV, BotRV;
	int Pixel, DestPixel, Bixel;
	BYTE BackgroundCol;
	int DDown, DOWN;

	//Calculate the trigonometry in order to find destination dimensions
	PCos = cos(Angle) * pScale;
	PSin = sin(Angle) * pScale;

	//Find destination width and height
	dw = (int)ceil(fabs(h * PSin) + fabs(w * PCos));
	dh = (int)ceil(fabs(h * PCos) + fabs(w * PSin));

	//Precalculate the trigonometry to use in rotation
	PCos = cos(Angle) / pScale;
	PSin = sin(Angle) / pScale;

	//used to move through the 3D array in a 1D style                  
	DDown = dw * BPC;     //DDown = 1 Row Down on the Dest Image
	DOWN = w * BPC ;      //DOWN = 1 Row Down on the Original Image
	//LEFT = 1 Colum Left on either image

	//Pivot coordinates
	px = w / 2;
	py = h / 2;

	//Allocate memory for each pixel (4 Bytes for color * Width * Heighr)
	BackgroundImg = (BYTE*)malloc(BPC * dw * dh);
	OriginalImg = (BYTE*)malloc(BPC * w * h); 
	TransparancyMap = (BYTE*)malloc(w * h); 
	RotatedImg = (BYTE*)malloc(BPC * dw * dh);
	//If a pointer returns NULL then memory was not allocated
	if (!BackgroundImg || !OriginalImg|| !RotatedImg || !TransparancyMap) 
		return FAILED_TO_ALLOCATE_MEMORY;
	//Clear the Rotated image memory (no need because it will be initialized with memcpy later)
	//ZeroMemory(RotatedImg, BPC *  dw * dh);

	//Create a bitmap descriptor for the background
	//Set all BackBmp Elements to zero 44bytes
	ZeroMemory(&BackBmp, sizeof(BITMAPINFO)); 
	BackBmp.bmiHeader.biBitCount = BPC * 8;
	BackBmp.bmiHeader.biPlanes = 1;
	BackBmp.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	BackBmp.bmiHeader.biWidth = dw;
	BackBmp.bmiHeader.biHeight = -dh;   //Height negative meaning top to bottom image

	//Create an identical descriptor for the rotated bitmap as well
	memcpy(&RotBmp, &BackBmp, sizeof(BITMAPINFO));

	//Create a context and a  bitmap handle to hold the part of the background behind the desination image
	BackDC = CreateCompatibleDC(DestDC);
	iBitmap =  CreateDIBSection(BackDC, &BackBmp, DIB_RGB_COLORS,(void **)&pBits, NULL, 0);
	iOldBackDCBitmap = SelectObject(BackDC, iBitmap);

	//Draw the background to our context
	BitBlt(BackDC, 0, 0, dw, dh, DestDC, (int)(x - dw / 2.0), (int)(y - dh / 2.0), SRCCOPY);

	//get background pixel information and store to the BackgroundImg array.
	if (!GetDIBits(BackDC, iBitmap , 0, dh, BackgroundImg, &BackBmp, DIB_RGB_COLORS))
		return(FAILED_GETTING_BACKGROUND_BITS);

	//Copy the background pixels to the destination image
	memcpy(RotatedImg, BackgroundImg, BPC * dw * dh);

	//Create a bitmap descriptor for the original image
	ZeroMemory(&PicBmp, sizeof(BITMAPINFO));
	PicBmp.bmiHeader.biBitCount = BPC * 8;
	PicBmp.bmiHeader.biPlanes = 1;
	PicBmp.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	PicBmp.bmiHeader.biWidth = w;
	PicBmp.bmiHeader.biHeight = -h;

	//Create a context and a  bitmap handle to hold the original image
	PicDC = CreateCompatibleDC(DestDC);

	ImgHandle =  CreateDIBSection(PicDC, &PicBmp, DIB_RGB_COLORS,(void **)&pBits, NULL, 0);
	iOldPicDCBitmap = SelectObject(PicDC, ImgHandle);

	//Draw the original image to our context
	BitBlt(PicDC, 0, 0, w, h, SrcDC, srcx, srcy, SRCCOPY);

	//get original image pixel information and store to the OriginalImg array.
	if (!GetDIBits(PicDC, ImgHandle , 0, h, OriginalImg, &PicBmp, DIB_RGB_COLORS))
		return FAILED_GETTING_IMAGE_BITS;

	//Get the min values to scan
	CX = (dw - w) / 2;  
	CY = (dh - h) / 2;  

	//Convert to R,G,B format the transparent color
	if (TranspColor >= 0) {
		tR = TranspColor & 0xFF;
		tG = (TranspColor & 0xFF00) >> 8;
		tB = (TranspColor & 0xFF0000) >> 16;
		Bixel = Pixel = 0;
		for (YY = 0; YY < h; YY++) { 
			for (XX = 0; XX < w; XX++) { 
				//0 If transparent, 1 if Opaque
				TransparancyMap[Bixel++] = !(OriginalImg[Pixel] == tB && OriginalImg[1+Pixel] == tG || OriginalImg[2+Pixel] == tR);
				Pixel += LEFT;
			}    
		} 
	}

	//If Hue, Sat or Lum parameters have changed then change original image bits
	if (Hue != 0 || Sat != 1 || Lum != 1) {
		//Change Hue of original Image pixel by pixel
		Pixel = 0;
		for (YY = 0; YY < h; YY++)
			for (XX = 0; XX < w; XX++) 
			{
				RGBtoHSL(OriginalImg[Pixel+2]/255.0,
					OriginalImg[Pixel+1]/255.0,
					OriginalImg[Pixel]/255.0,
					&hh , &ss, &vv);                
				HSLtoRGB(norm(hh + Hue), enclose(ss*Sat), enclose(vv*Lum), &rr, &gg, &bb);     
				OriginalImg[Pixel+2] = (BYTE)(rr*255);
				OriginalImg[Pixel+1] = (BYTE)(gg*255);
				OriginalImg[Pixel]= (BYTE)(bb*255);
				Pixel += LEFT;     
			}  
	}   

	//ROTATION
	//For all Lines of the destination image
	for (YY = -CY; YY < dh - CY; YY++) { 
		//Get the rotation translation (gives the SourceImage coordinate for each DestImage x,y)
		tx = (-CX - px) * PCos - (YY - py) * PSin + px;
		ty = (-CX - px) * PSin + (YY - py) * PCos + py;
		DestPixel = (YY + CY)*DDown;
		for (XX = -CX; XX < dw - CX; XX++) {

			//Get nearest to the left pixel
			ix = (int)tx;
			iy = (int)ty;

			if (ix >= 0 && ix + 1 < w && iy >= 0 && iy + 1 < h) {
				//Get the digits after the decimal point
				dx = fabs(tx - ix);
				dy = fabs(ty - iy);             

				//Holds PixelXY index in the array
				Pixel = ix * LEFT + iy * DOWN;
				Bixel = ix + iy * w;

				if (TranspColor >= 0) {
					//Get Alpha if the color is not transparent, 0 if it is
					TopLV = TransparancyMap[Bixel] * Alpha;
					TopRV = TransparancyMap[Bixel+1] * Alpha;
					BotLV = TransparancyMap[Bixel+w] * Alpha;
					BotRV = TransparancyMap[Bixel+w+1] * Alpha;  
				} else TopLV = TopRV = BotLV = BotRV = Alpha;
				//Calculate the destination color getting color information from four neigbouring source pixels

				//Calculate percendage of pixel used
				TopL = (1 - dx) * (1 - dy);
				TopR = dx * (1 - dy);
				BotL = (1 - dx) * dy;
				BotR = dx * dy;

				//Blue
				BackgroundCol = BackgroundImg[DestPixel];
				RotatedImg[DestPixel] = (BYTE)(  
					(OriginalImg[Pixel]           * TopLV + BackgroundCol * (1 - TopLV)) * TopL 
					+ (OriginalImg[Pixel+LEFT]      * TopRV + BackgroundCol * (1 - TopRV)) * TopR 
					+ (OriginalImg[Pixel+DOWN]      * BotLV + BackgroundCol * (1 - BotLV)) * BotL 
					+ (OriginalImg[Pixel+LEFT+DOWN] * BotRV + BackgroundCol * (1 - BotRV)) * BotR);
				//Green
				BackgroundCol = BackgroundImg[DestPixel+1];           
				RotatedImg[1+DestPixel] = (BYTE)(
					(OriginalImg[1+Pixel]           * TopLV + BackgroundCol * (1 - TopLV)) * TopL 
					+ (OriginalImg[1+Pixel+LEFT]      * TopRV + BackgroundCol * (1 - TopRV)) * TopR 
					+ (OriginalImg[1+Pixel+DOWN]      * BotLV + BackgroundCol * (1 - BotLV)) * BotL 
					+ (OriginalImg[1+Pixel+LEFT+DOWN] * BotRV + BackgroundCol * (1 - BotRV)) * BotR);
				//Red
				BackgroundCol = BackgroundImg[DestPixel+2];           
				RotatedImg[2+DestPixel] = (BYTE)(
					(OriginalImg[2+Pixel]           * TopLV + BackgroundCol * (1 - TopLV)) * TopL 
					+ (OriginalImg[2+Pixel+LEFT]      * TopRV + BackgroundCol * (1 - TopRV)) * TopR 
					+ (OriginalImg[2+Pixel+DOWN]      * BotLV + BackgroundCol * (1 - BotLV)) * BotL 
					+ (OriginalImg[2+Pixel+LEFT+DOWN] * BotRV + BackgroundCol * (1 - BotRV)) * BotR);          
			}      
			tx += PCos;
			ty += PSin;
			DestPixel += LEFT;
		}
	}


	//Draw the array
	if (!StretchDIBits(DestDC, (int)(x - dw / 2.0), (int)(y - dh / 2.0), dw, dh, 0, 0, dw, dh, RotatedImg, &RotBmp, DIB_RGB_COLORS, SRCCOPY))
		return FAILED_TO_DRAWIMAGE;

	//Clean up
	free(RotatedImg);
	free(OriginalImg);
	free(BackgroundImg);
	free(TransparancyMap);

	//replace the new objects with the original
	SelectObject(BackDC, iOldBackDCBitmap);
	SelectObject(PicDC, iOldPicDCBitmap);

	DeleteObject(iBitmap);
	DeleteObject(ImgHandle);
	//ReleaseDC(Dc acquired by GetDC)
	DeleteDC(PicDC);
	DeleteDC(BackDC);
	return 0;
}


double norm(double a){
	if (a > 1.0) 
		return a - 1.0;
	else if (a < 0.0) 
		return a + 1.0;
	else  
		return a;
}

double enclose(double a){
	if (a > 1.0) 
		return 1.0;
	else if (a < 0.0) 
		return 0;
	else  
		return a;
}
