Purpose:

Rotate a picture at any given angle in realtime. Also scale it, use transparent color and alphablending.
Plus hue,sat,lum change
*Bugfix: memory leak caused by GetDC

DLL File (1 export rotatedc)
=========================================================================================================
Compatibility:

Windows 98 - Windows Vista

compile dll using Dev-C++ (or any other C compiler using proper modifications)
compile test executeable using Visual Basic 6 or 5.
=========================================================================================================
Files Contained:

rotate.dev  -> C project file (open with dev-C++)
rotate.dsw  -> C workspace file (open with Visual-C++ 6)
rotate.dsp  -> Visual C++ 6 project file
dllmain.c   -> Main rotation function
dll.h       -> header file (function prototype)
cc.c        -> Auxiliary functions for color conversion
cc.h        -> header file for auxiliary functions

hostapp.vbp -> Visual Basic 6 (VB6) project file
form1.frm   -> VB6 form code
form1.frx   -> VB6 form resource file

==========================================================================================================
Function parameters:

Private Declare Function rotatedc Lib "rotate.dll" Alias "rotatedc@60" (ByVal aHDC As Long, ByVal Angle As Single, ByVal X As Long, ByVal Y As Long, ByVal W As Long, ByVal H As Long, ByVal PicDC As Long, Optional ByVal SrcX As Long = 0, Optional ByVal SrcY As Long = 0, Optional ByVal pScale As Single = 1, Optional ByVal TraspColor As Long = -1, Optional ByVal Alpha As Single = 1, Optional ByVal Hue As Single = 0, Optional ByVal Sat As Single = 1, Optional ByVal Lum As Single = 1) As Long

      aHDC : Destination device context (.hdc of picturebox with scalemode=pixels and autoredraw=true)
     Angle : a real number expressing the rotation angle in Rads (360 deg = 2*pi rad)
         X : the destination X coordinate
         Y : the destination Y coordinate
         W : the width of the original image
         H : the height of the original image
      PicDC: The device context of the original image (.hdc of picturebox with scalemode=pixels and autoredraw=true)
       SrcX: x of the upperleft corner of the source rectangle. (where to copy from. useful for copying a part of the bitmap)
       SrcY: y of the upperleft corner of the source rectangle.
    pScale : a real number expressing the scale (use 1 for 100%, 0.5 for 50%, 2 for 200% etc)
TraspColor : an integer (3 bytes) expressing the RGB value of the transparent color
     Alpha : a real number between 0 and 1 indicating the alphablend percendage value 1 = solid
       Hue : the Hue Offset of the Image (Hue is like the wavelength of a color)
       Sat : saturation percendage 
       Lum : luminocity percendage