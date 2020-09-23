VERSION 5.00
Begin VB.Form Form1 
   AutoRedraw      =   -1  'True
   Caption         =   "Form1"
   ClientHeight    =   6945
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   7995
   LinkTopic       =   "Form1"
   ScaleHeight     =   463
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   533
   StartUpPosition =   3  'Windows Default
   Begin VB.PictureBox S 
      AutoRedraw      =   -1  'True
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   0  'None
      Height          =   5115
      Left            =   0
      Picture         =   "autorotate.frx":0000
      ScaleHeight     =   341
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   279
      TabIndex        =   0
      Top             =   0
      Visible         =   0   'False
      Width           =   4185
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function rotatedc Lib "rotate.dll" Alias "rotatedc@60" (ByVal aHDC As Long, ByVal Angle As Single, ByVal X As Long, ByVal Y As Long, ByVal W As Long, ByVal H As Long, ByVal PicDC As Long, Optional ByVal SrcX As Long = 0, Optional ByVal SrcY As Long = 0, Optional ByVal pScale As Single = 1, Optional ByVal TraspColor As Long = -1, Optional ByVal Alpha As Single = 1, Optional ByVal Hue As Single = 0, Optional ByVal Sat As Single = 1, Optional ByVal Lum As Single = 1) As Long
'Use this if compiled with microsoft visual C++ 6.0
'Private Declare Function rotatedc Lib "rotate.dll" Alias "_rotatedc@60" (ByVal aHDC As Long, ByVal Angle As Single, ByVal X As Long, ByVal Y As Long, ByVal W As Long, ByVal H As Long, ByVal PicDC As Long, Optional ByVal SrcX As Long = 0, Optional ByVal SrcY As Long = 0, Optional ByVal pScale As Single = 1, Optional ByVal TraspColor As Long = -1, Optional ByVal Alpha As Single = 1, Optional ByVal Hue As Single = 0, Optional ByVal Sat As Single = 1, Optional ByVal Lum As Single = 1) As Long
Const Rad As Currency = 1.74532925199433E-02
Dim ExitFlag As Boolean
Private Sub Form_Load()
   Dim ret As Long
   Dim r As Currency
   Me.Show
   Do
     Me.Cls
     ret = rotatedc(Me.hDC, r, Me.ScaleWidth / 2, Me.ScaleHeight / 2, S.Width, S.Height, S.hDC, 0, 0, 1, &HFAEED0)
     r = r + Rad
     Me.Refresh
     Me.Caption = r
     DoEvents
   Loop While (ret = 0 And Not ExitFlag)
   MsgBox ret
End Sub

Private Sub Form_Unload(Cancel As Integer)
ExitFlag = True
End Sub
