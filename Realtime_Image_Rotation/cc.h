/*
  From The website of Dr. Marcelo Gattass
  http://www.tecgraf.puc-rio.br/~mgattass/color/
  
  Color Conversion Routines
*/

#ifndef _CC_H_
#define _CC_H_

enum {
  ccTA_2, ccTC_2, D50_2, D55_2, D65_2, D75_2, F2_2, F7_2, F11_2,
  ccTA_10, ccTC_10, D50_10, D55_10, D65_10, D75_10, F2_10, F7_10, F11_10,
  ccNTristimulus
};

enum { ccX, ccY, ccZ};

#define PI 3.14159265

/*
 *	Function Headers
 */

int ccXYZtoRGB(double x, double y, double z, double* r, double* g, double* b, char ObsIll); //

int ccRGBtoXYZ(double r, double g, double b, double* x, double* y, double* z, char ObsIll); //

int XYZtoYxy(double x, double y, double z, double* rY, double* rx, double* ry);//

int YxytoXYZ(double Y, double x, double y, double* rx, double* ry, double* rz);//

int XYZtoHunterLab(double x, double y, double z, double* L, double* a, double* b); //

int HunterLabtoXYZ(double L, double a, double b, double* x, double* y, double* z); //

int XYZtoCIE_Lab(double x, double y, double z, double* L, double* a, double* b, char ObsIll); //

int CIE_LabtoXYZ(double L, double a, double b, double* x, double* y, double* z, char ObsIll); //

int CIE_LabtoCIE_LCH(double L, double a, double b, double* rL, double* rC, double* rH);

int CIE_LCHtoCIE_Lab(double L, double C, double H, double* rL, double* ra, double* rb);

int XYZtoCIE_Luv(double x, double y, double z, double* L, double* u, double* v, char ObsIll);

int CIE_LuvtoXYZ(double L, double u, double v, double* x, double* y, double* z, char ObsIll);

int RGBtoHSL(double L, double a, double b, double* h, double* s, double* l); //

int HSLtoRGB(double h, double s, double l, double* r, double* g, double* b); //

int RGBtoHSV(double r, double g, double b, double* h, double* s, double* v); //

int HSVtoRGB(double h, double s, double v, double* r, double* g, double* b); //

int fRGBtoCMY(double r, double g, double b, double* c, double* m, double* y); //

int iRGBtoCMY(int r, int g, int b, double* c, double* m, double* y); //

int CMYtofRGB(double c, double m, double y, double* r, double* g, double* b); //

int CMYtoiRGB(double c, double m, double y, int* r, int* g, int* b); //

int CMYtoCMYK(double c, double m, double y, double* C, double* M, double* Y, double* K); //

int CMYKtoCMY(double c, double m, double y, double k, double* C, double* M, double* Y); //


#endif
