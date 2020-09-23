VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.Form Form1 
   Caption         =   "Realtime Image Rotation"
   ClientHeight    =   8310
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   8520
   LinkTopic       =   "Form1"
   ScaleHeight     =   554
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   568
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command3 
      Caption         =   "R"
      Height          =   330
      Left            =   8115
      TabIndex        =   20
      Top             =   6975
      Width           =   330
   End
   Begin VB.CommandButton Command2 
      BackColor       =   &H00FAEED0&
      Caption         =   "T"
      Height          =   405
      Left            =   7785
      Style           =   1  'Graphical
      TabIndex        =   16
      Top             =   7770
      Width           =   435
   End
   Begin VB.CommandButton Command1 
      Caption         =   ".."
      Height          =   300
      Left            =   7035
      TabIndex        =   15
      Top             =   7785
      Width           =   330
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   105
      OLEDropMode     =   1  'Manual
      TabIndex        =   14
      Top             =   7785
      Width           =   6810
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   5925
      Top             =   7740
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.HScrollBar HScroll3 
      Height          =   270
      Index           =   2
      Left            =   4470
      Max             =   200
      TabIndex        =   12
      Top             =   7395
      Value           =   100
      Width           =   2895
   End
   Begin VB.HScrollBar HScroll3 
      Height          =   270
      Index           =   1
      Left            =   4470
      Max             =   200
      TabIndex        =   10
      Top             =   7110
      Value           =   100
      Width           =   2895
   End
   Begin VB.HScrollBar HScroll3 
      Height          =   270
      Index           =   0
      Left            =   4470
      Max             =   360
      TabIndex        =   5
      Top             =   6825
      Width           =   2895
   End
   Begin VB.HScrollBar HScroll2 
      Height          =   270
      Left            =   615
      Max             =   400
      Min             =   100
      TabIndex        =   4
      Top             =   7410
      Value           =   200
      Width           =   2895
   End
   Begin VB.HScrollBar HScroll1 
      Height          =   270
      Left            =   615
      Max             =   100
      TabIndex        =   3
      Top             =   7110
      Value           =   100
      Width           =   2895
   End
   Begin VB.PictureBox S 
      AutoRedraw      =   -1  'True
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   0  'None
      Height          =   5115
      Left            =   2175
      Picture         =   "Form1.frx":0000
      ScaleHeight     =   341
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   279
      TabIndex        =   2
      Top             =   675
      Visible         =   0   'False
      Width           =   4185
   End
   Begin VB.HScrollBar vScroll1 
      Height          =   270
      Left            =   615
      Max             =   360
      TabIndex        =   1
      Top             =   6810
      Width           =   2895
   End
   Begin VB.PictureBox Picture2 
      Appearance      =   0  'Flat
      AutoRedraw      =   -1  'True
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   6795
      Left            =   15
      Picture         =   "Form1.frx":45F2A
      ScaleHeight     =   453
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   565
      TabIndex        =   0
      Top             =   15
      Width           =   8475
   End
   Begin VB.Label Label2 
      Height          =   240
      Index           =   2
      Left            =   7425
      TabIndex        =   19
      Top             =   7425
      Width           =   375
   End
   Begin VB.Label Label2 
      Height          =   240
      Index           =   1
      Left            =   7425
      TabIndex        =   18
      Top             =   7155
      Width           =   375
   End
   Begin VB.Label Label2 
      Height          =   240
      Index           =   0
      Left            =   7425
      TabIndex        =   17
      Top             =   6870
      Width           =   375
   End
   Begin VB.Label Label1 
      Caption         =   "Val"
      Height          =   225
      Index           =   5
      Left            =   3975
      TabIndex        =   13
      Top             =   7440
      Width           =   450
   End
   Begin VB.Label Label1 
      Caption         =   "Sat"
      Height          =   225
      Index           =   4
      Left            =   3975
      TabIndex        =   11
      Top             =   7140
      Width           =   450
   End
   Begin VB.Label Label1 
      Caption         =   "Hue"
      Height          =   225
      Index           =   3
      Left            =   3975
      TabIndex        =   9
      Top             =   6855
      Width           =   450
   End
   Begin VB.Label Label1 
      Caption         =   "Scale"
      Height          =   225
      Index           =   2
      Left            =   120
      TabIndex        =   8
      Top             =   7425
      Width           =   450
   End
   Begin VB.Label Label1 
      Caption         =   "Alpha"
      Height          =   225
      Index           =   1
      Left            =   105
      TabIndex        =   7
      Top             =   7155
      Width           =   450
   End
   Begin VB.Label Label1 
      Caption         =   "Angle"
      Height          =   225
      Index           =   0
      Left            =   105
      TabIndex        =   6
      Top             =   6840
      Width           =   450
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Const Rad As Currency = 1.74532925199433E-02
Const pi As Currency = 3.14159265358979

Private Declare Function rotatedc Lib "rotate.dll" Alias "rotatedc@60" (ByVal aHDC As Long, ByVal Angle As Single, ByVal X As Long, ByVal Y As Long, ByVal W As Long, ByVal H As Long, ByVal PicDC As Long, Optional ByVal SrcX As Long = 0, Optional ByVal SrcY As Long = 0, Optional ByVal pScale As Single = 1, Optional ByVal TraspColor As Long = -1, Optional ByVal Alpha As Single = 1, Optional ByVal Hue As Single = 0, Optional ByVal Sat As Single = 1, Optional ByVal Lum As Single = 1) As Long
'Private Declare Function rotatedc Lib "rotate.dll" Alias "_rotatedc@60" (ByVal aHDC As Long, ByVal Angle As Single, ByVal X As Long, ByVal Y As Long, ByVal W As Long, ByVal H As Long, ByVal PicDC As Long, Optional ByVal SrcX As Long = 0, Optional ByVal SrcY As Long = 0, Optional ByVal pScale As Single = 1, Optional ByVal TraspColor As Long = -1, Optional ByVal Alpha As Single = 1, Optional ByVal Hue As Single = 0, Optional ByVal Sat As Single = 1, Optional ByVal Lum As Single = 1) As Long
Dim T As Long

Private Sub Command1_Click()
  CommonDialog1.Filter = "All Supported Images|*.bmp;*.dib;*.gif;*.jpg;*.wmf;*.emf;*.ico;*.cur|Bitmaps|*.bmp;*.dib|JPEG Images|*.jpg|Metafiles|*.wmf;*.emf|Icons|*.ico;*.cur"
  CommonDialog1.ShowOpen
  Text1.Text = CommonDialog1.FileName
  If Dir(Text1.Text) <> "" Then
     S.Picture = LoadPicture(Text1.Text)
     Draw
  End If
End Sub

Private Sub Command2_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
  If Button = 1 Then
     CommonDialog1.ShowColor
     Command2.BackColor = CommonDialog1.Color
     T = CommonDialog1.Color
     Draw
  Else
     Command2.BackColor = &H8000000F
     T = -1
     Draw
  End If
End Sub

Private Sub Command3_Click()
  HScroll3(0).Value = 0
  HScroll3(1).Value = 100
  HScroll3(2).Value = 100
End Sub

Private Sub Form_Load()
   T = &HFAEED0
   Command1.Enabled = App.LogMode <> 0
   Draw
End Sub

Sub Draw()
   Picture2.Cls
   rotatedc Picture2.hDC, 2 * pi - vScroll1.Value * Rad, Picture2.Width / 2, Picture2.Height / 2, S.Width, S.Height, S.hDC, 0, 0, HScroll2.Value / 200, T, HScroll1.Value / 100, HScroll3(0).Value / 360, HScroll3(1).Value / 100, HScroll3(2).Value / 100
   Picture2.Refresh
   DoEvents
End Sub

Private Sub Picture2_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
  If Button = 2 Then
     T = Picture2.Point(X, Y)
     Command2.BackColor = T
     Draw
  End If
End Sub

Private Sub Text1_OLEDragDrop(Data As DataObject, Effect As Long, Button As Integer, Shift As Integer, X As Single, Y As Single)
If Data.Files.Count > 0 Then
     Select Case LCase(Right(Data.Files(1), 3))
     Case "bmp", "dib", "gif", "jpg", "wmf", "emf", "ico", "cur"
        Text1.Text = Data.Files(1)
        S.Picture = LoadPicture(Text1.Text)
        Draw
     End Select
End If
End Sub

Private Sub HScroll1_Change(): Draw: End Sub
Private Sub HScroll1_Scroll(): Draw: End Sub
Private Sub HScroll2_Change(): Draw: End Sub
Private Sub HScroll2_Scroll(): Draw: End Sub
Private Sub vScroll1_Change(): Draw: End Sub
Private Sub vScroll1_Scroll(): Draw: End Sub
Private Sub HScroll3_Change(Index As Integer):
  Draw
  Label2(Index) = HScroll3(Index).Value
End Sub
Private Sub HScroll3_Scroll(Index As Integer)
  Draw
  Label2(Index) = HScroll3(Index).Value
End Sub
