 #include <windows.h>
 //Exported Function
 __declspec (dllexport) int __stdcall rotatedc(HDC DestDC, float Angle, int x, int y, int w, int h, HDC SrcDC, int srcx, int srcy, float pScale, int TranspColor, float Alpha, float Hue, float Sat, float Lum);
