VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Main"
   ClientHeight    =   9585
   ClientLeft      =   2070
   ClientTop       =   2850
   ClientWidth     =   16035
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MouseIcon       =   "Form1.frx":030A
   ScaleHeight     =   9585
   ScaleWidth      =   16035
   Begin VB.CommandButton Ketqua 
      Caption         =   "Result :D"
      BeginProperty Font 
         Name            =   ".VnTime"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   14640
      TabIndex        =   13
      ToolTipText     =   "Click here to display Graph & Results"
      Top             =   120
      Width           =   1335
   End
   Begin VB.CommandButton Exit 
      Caption         =   "EXIT  >_<"
      BeginProperty Font 
         Name            =   ".VnTime"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   14640
      TabIndex        =   12
      ToolTipText     =   "Click here to Exit the Program"
      Top             =   1080
      Width           =   1335
   End
   Begin VB.Frame Frame3 
      Caption         =   "NhËp sè liÖu"
      BeginProperty Font 
         Name            =   ".VnTime"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1575
      Left            =   11040
      TabIndex        =   3
      Top             =   0
      Width           =   3495
      Begin VB.TextBox txta 
         Alignment       =   2  'Center
         Height          =   285
         Left            =   600
         TabIndex        =   7
         Text            =   "0.1"
         ToolTipText     =   "Nhap a :"
         Top             =   480
         Width           =   855
      End
      Begin VB.TextBox txtk 
         Alignment       =   2  'Center
         Height          =   285
         Left            =   600
         TabIndex        =   6
         Text            =   "50"
         ToolTipText     =   "Nhap K :"
         Top             =   1080
         Width           =   855
      End
      Begin VB.TextBox k 
         Alignment       =   2  'Center
         Height          =   285
         Left            =   2400
         TabIndex        =   5
         Text            =   "10000"
         ToolTipText     =   "Neu nhu khong thay Tod thi hay TANG gia tri nay"
         Top             =   480
         Width           =   855
      End
      Begin VB.TextBox saiso 
         Alignment       =   2  'Center
         Height          =   285
         Left            =   2400
         TabIndex        =   4
         Text            =   "0.05"
         ToolTipText     =   "Sai lech so voi gia tri mong muon"
         Top             =   1080
         Width           =   855
      End
      Begin VB.Label Label1 
         Alignment       =   2  'Center
         Caption         =   "a = "
         BeginProperty Font 
            Name            =   ".VnTime"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   11
         Top             =   480
         Width           =   375
      End
      Begin VB.Label Label2 
         Alignment       =   2  'Center
         Caption         =   "K = "
         BeginProperty Font 
            Name            =   ".VnTime"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   10
         Top             =   1080
         Width           =   495
      End
      Begin VB.Label Label3 
         Alignment       =   2  'Center
         Caption         =   "Sè b­íc tÝnh ="
         BeginProperty Font 
            Name            =   ".VnTime"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   1560
         TabIndex        =   9
         Top             =   360
         Width           =   855
      End
      Begin VB.Label label4 
         Alignment       =   2  'Center
         Caption         =   "Sai sè ="
         BeginProperty Font 
            Name            =   ".VnTime"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   1560
         TabIndex        =   8
         Top             =   1080
         Width           =   855
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "About this program"
      BeginProperty Font 
         Name            =   ".VnTime"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   5895
      Left            =   120
      TabIndex        =   2
      Top             =   3600
      Width           =   10815
      Begin VB.Image Image2 
         Height          =   5460
         Left            =   120
         Picture         =   "Form1.frx":0614
         ToolTipText     =   "About us"
         Top             =   360
         Width           =   10500
      End
   End
   Begin VB.ListBox List1 
      BeginProperty Font 
         Name            =   ".VnTime"
         Size            =   11.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   7500
      Left            =   11040
      TabIndex        =   1
      ToolTipText     =   "Results Table"
      Top             =   2040
      Width           =   4935
   End
   Begin VB.Frame Frame1 
      Caption         =   "S¬ ®å cÊu tróc hÖ §KT§ - Nhãm 5 - T§H1 - K49"
      BeginProperty Font 
         Name            =   ".VnTime"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3495
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   10815
      Begin VB.Timer Timer1 
         Interval        =   30
         Left            =   10440
         Top             =   2400
      End
      Begin VB.Image Image1 
         Height          =   3075
         Left            =   360
         Picture         =   "Form1.frx":1070C
         ToolTipText     =   "Automatic Control System_Structure Diagram"
         Top             =   360
         Width           =   10245
      End
   End
   Begin VB.Label Label5 
      Alignment       =   2  'Center
      Caption         =   "- KÕt qu¶ thu ®­îc -"
      BeginProperty Font 
         Name            =   ".VnTimeH"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   12720
      TabIndex        =   14
      Top             =   1680
      Width           =   2175
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Exit_Click()
MsgBox "Thank you for using our first software written in VB. Take Care ! ^-*", vbInformation, "Cam on"
Unload frmDoThi
Unload frmXuly
Unload Form1
End Sub
Private Sub Form_Load()
Form1.Caption = Space(100) & "Main Program _ We are active men _ GROUP 5 _ Call us if you have any questions"
SetIcon Me.hWnd, "AAA"
End Sub
Private Sub Ketqua_Click()
tinh_ket_qua
End Sub
Sub tinh_ket_qua()
Dim T, km, tg, Sovachkhacy, Sovachkhacx, Xichma
Dim ny, deltay, dtdy, ytd(1000000), nx, deltax, dtdx, xtd(1000000) As Double
Dim A, B, C, D As Double
Dim Y(1000000), X(1000000), Tmax, Tod As Double
Dim Ymax, Ymin, Yod As Double
Dim ktx(100), ktxtd(100), kty(100), ktytd(100) As Double
Dim I, j As Long
'--------------------------------------------------------------------------
If (txtk < 0) Or (txtk = 0) Then
frmXuly.Show
Else
'--------------------------------------------------------------------------
frmDoThi.Show
frmDoThi.Cls
T = 0.001
'--------------------------------------------------------------------------
'Thiet dat cac gia tri dau cua mang y
Y(0) = Y(1) = Y(2) = 0
' Tinh A , B , C , D
A = 8 + 8 * txta * T * Sqr(txtk) + 2 * txtk * T * T + txtk * T * T * T
B = -24 - 8 * txta * T * Sqr(txtk) + 2 * txtk * T * T + 3 * txtk * T * T * T
C = 24 - 8 * txta * T * Sqr(txtk) - 2 * txtk * T * T + 3 * txtk * T * T * T
D = -8 + 8 * txta * T * Sqr(txtk) - 2 * txtk * T * T + txtk * T * T * T
'Da Thuc Dac Tinh = (1,2*txta*sqr(txtk),txtk,txtk)
'--------------------------------------------------------------------------
'Xet tinh On Dinh :
Dim OnDinh As Boolean
If (txtk > 0) And (2 * txta * Sqr(txtk) > 1) Then
 OnDinh = True
 MsgBox "Your system are stable with these 'a' & 'K' values which you've entered!"
Else
 OnDinh = False
 MsgBox "What a pity! You've typed 'a' & 'K' values which make the system not stable any more!"
End If
'--------------------------------------------------------------------------
'Xoa du lieu tren list1.
List1.Clear
'--------------------------------------------------------------------------
' Tinh Y(3) -> Y(30000)
For I = 0 To k - 3
    'Phuong trinh sai phan cua he thong
    Y(I + 3) = (-B * Y(I + 2) - C * Y(I + 1) - D * Y(I) + 8 * txtk * T * T * T) / A
Next I
'--------------------------------------------------------------------------
'Tim ymax
Ymax = Y(0)
For I = 0 To k
    If Y(I) > Ymax Then
    Ymax = Y(I)
    km = I 'km la bien de tinh tmax
    End If
Next I
Tmax = km * T
' Tim Ymin
Ymin = Y(0)
For I = 1 To k
If Ymin > Y(I) Then Ymin = Y(I)
Next
'--------------------------------------------------------------------------
'Tinh cac gia tri cua mang x (mang x phuc vu cho viec tim hoanh do cac diem va khac do truc hoanh)
 For I = 1 To k
 X(I) = I * T
 Next
' Xac dinh khoang cach diem cao nhat va thap nhat (ymax va ymin)
If Ymin < 0 Then
deltay = Ymax - Ymin
Else
deltay = Ymax
End If
'Xac dinh toa do cac diem
'Toa do cua y(i) va ytd(i)
ny = 6500 / deltay
dtdy = Int(Ymax * ny) + 700
For I = 1 To k
ytd(I) = dtdy - Int(Y(I) * ny)
Next
'Toa do cua x(i) ~ xtd(i)
deltax = k * T
nx = 7500 / deltax
dtdx = 1000
For I = 1 To k
xtd(I) = Int(X(I) * nx) + dtdx
Next
'Tinh Xichma_Do qua Dieu Chinh %
Yod = Abs(D / (A + B + C))
Xichma = (Ymax - Yod) * 100 / Yod
'--------------------------------------------------------------------------
' Ve duong sai lech khi he thong la on dinh
If OnDinh = True Then
frmDoThi.Line1.Visible = True
frmDoThi.Line2.Visible = True
    frmDoThi.Line1.BorderStyle = 2
    frmDoThi.Line1.BorderColor = QBColor(2)
    frmDoThi.Line1.X1 = dtdx
    frmDoThi.Line1.Y1 = dtdy - Int((Yod + saiso * Yod) * ny)
    frmDoThi.Line1.X2 = 8500
    frmDoThi.Line1.Y2 = dtdy - Int((Yod + saiso * Yod) * ny)
frmDoThi.Line2.BorderStyle = 2
frmDoThi.Line2.BorderColor = QBColor(2)
frmDoThi.Line2.X1 = dtdx
frmDoThi.Line2.Y1 = dtdy - Int((Yod - saiso * Yod) * ny)
frmDoThi.Line2.X2 = 8500
frmDoThi.Line2.Y2 = dtdy - Int((Yod - saiso * Yod) * ny)
End If
'--------------------------------------------------------------------------
' In gia tri Ymax tren do thi khi he thong on dinh
If OnDinh = True Then
frmDoThi.Ymax.Caption = "Ymax = " & Format$(Ymax, "###0.0##")
frmDoThi.Ymax.Move dtdx + Int(Tmax * nx) - 300, dtdy - Int(Ymax * ny) - 350
' Ke duong dong Ymax
frmDoThi.Line (dtdx + Int(Tmax * nx), dtdy - Int(Ymax * ny))-(dtdx + Int(Tmax * nx), 7200), QBColor(9)
frmDoThi.Line (dtdx + Int(Tmax * nx), dtdy - Int(Ymax * ny))-(dtdx, dtdy - Int(Ymax * ny)), QBColor(9)
'In gia tri Tmax tren do thi
frmDoThi.Tmax.Caption = "Tmax = " & Format$(Tmax, "###0.0###")
frmDoThi.Tmax.Move Int(Tmax * nx) + dtdx + 60, dtdy - 700
' khi he thong khong on dinh thi khong in ymax va tmax
Else
frmDoThi.Tmax.Caption = " "
frmDoThi.Ymax.Caption = " "
End If
'--------------------------------------------------------------------------
' Ve truc toa do
frmDoThi.Line (dtdx, 200)-(dtdx, dtdy)
frmDoThi.Line (dtdx, dtdy)-(9200, dtdy)
' Ve mui ten truc tung
frmDoThi.Line (dtdx, 200)-(dtdx - 50, 400)
frmDoThi.Line (dtdx, 200)-(dtdx + 50, 400)
' Ve mui ten truc hoanh
frmDoThi.Line (9200, dtdy)-(9000, dtdy - 50)
frmDoThi.Line (9200, dtdy)-(9000, dtdy + 50)
'Dua label y(t) va t,sec vao hai truc
frmDoThi.tentrucx.Caption = "t(sec)"
frmDoThi.tentrucx.Move 8900, dtdy + 90
frmDoThi.tentrucy.Caption = "y(t)"
frmDoThi.tentrucy.Move dtdx - 50, 0
'--------------------------------------------------------------------------
' Xac dinh t on dinh
If OnDinh = True Then
For I = 1 To k
If (Abs(Y(I) - Yod) > (saiso * Yod)) Then j = I + 1
Next I
' Thu xem neu den k ma chua co Tod
If j < k Then
Tod = j * T
  'Ke duong Tod va dua label Yod va Tod len do thi
frmDoThi.Line (dtdx + Int(Tod * nx), dtdy - Int(Y(j) * ny))-(dtdx + Int(Tod * nx), dtdy), QBColor(3)
frmDoThi.Tod.Caption = "Tod=" & Format$(Tod, "##0.0##")
frmDoThi.Tod.Move dtdx + Int(Tod * nx) + 50, dtdy - 400
frmDoThi.Yod.Caption = "Yod=" & Format$(Yod, "##0.0##")
frmDoThi.Yod.Move 8500, dtdy - Int((Yod + saiso * Yod) * ny)
frmDoThi.loiTod.Caption = " "
List1.AddItem "Thêi gian æn ®Þnh Tod = " & Tod & " s"
    Else
  frmDoThi.Yod.Caption = "Yod=" & Format$(Yod, "##0.0##")
  frmDoThi.Yod.Move 8500, dtdy - Int((Yod + saiso * Yod) * ny)
  frmDoThi.Tod.Caption = " "
  frmDoThi.loiTod.Caption = "Tod lon qua ! Nen Tang 'SO BUOC TINH' trong Main"
  frmDoThi.loiTod.Move 8700, dtdy - 700
  List1.AddItem "Thêi gian æn ®Þnh Tod :  Hay Tang 'SO BUOC TINH'"
    End If
Else
    frmDoThi.Tod.Caption = " "
    frmDoThi.Yod.Caption = " "
    frmDoThi.loiTod.Caption = " "
End If
'--------------------------------------------------------------------------
' Khac do truc hoanh
Sovachkhacx = 10
tg = X(k) / Sovachkhacx
ktx(1) = tg
' Xac dinh gia tri khac
For I = 1 To (Sovachkhacx - 1)
ktx(I + 1) = ktx(I) + tg
Next
' Toa do cac vach khac
For I = 1 To Sovachkhacx
ktxtd(I) = Int(ktx(I) * nx) + dtdx
Next
' Ve vach khac
For I = 1 To Sovachkhacx
frmDoThi.Line (ktxtd(I), dtdy - 50)-(ktxtd(I), dtdy + 50)
Next
' Di chuyen  cac label ghi gia tri tren truc gia tri tren truc hoanh
frmDoThi.xkhac(0).Move dtdx - 300, dtdy + 100
frmDoThi.xkhac(0).Caption = 0
For I = 1 To Sovachkhacx
frmDoThi.xkhac(I).Move ktxtd(I) - 170, dtdy + 100
frmDoThi.xkhac(I).Caption = Format$(ktx(I), "##0.0#")
Next
'--------------------------------------------------------------------------
' Khac do truc tung neu he thong on dinh
Sovachkhacy = 10
If OnDinh = True Then
tg = Yod / Sovachkhacy
            For I = 1 To (Sovachkhacy + 1)
            If I * tg < Ymax Then
            kty(I) = I * tg
            Else
            kty(I) = 0
            End If
            Next
        For I = 1 To (Sovachkhacy + 1)
        If kty(I) <> 0 Then
        ktytd(I) = dtdy - Int(kty(I) * ny) - 100
        End If
        Next
'Khac cac vach chia truc tung
            For I = 1 To (Sovachkhacy + 1)
            If kty(I) <> 0 Then
            frmDoThi.Line (950, ktytd(I) + 100)-(1050, ktytd(I) + 100)
              End If
            Next
'Dua cac gia tri y len truc tung
            For I = 1 To (Sovachkhacy + 1)
              If kty(I) <> 0 Then
            frmDoThi.ykhac(I).Caption = Format$(kty(I), "###0.0###")
            frmDoThi.ykhac(I).Move 450, ktytd(I)
              Else
            frmDoThi.ykhac(I).Caption = " "
              End If
            Next
'--------------------------------------------------------------------------
'Ve duong Yod
frmDoThi.Line (dtdx, dtdy - Int(Yod * ny))-(8500, dtdy - Int(Yod * ny)), QBColor(12)
'--------------------------------------------------------------------------
'Khi he thong khong on dinh van khac do phan truc tung duong
Else
tg = deltay / Sovachkhacy
            For I = 1 To (Sovachkhacy + 1)
            If I * tg < Ymax Then
            kty(I) = I * tg
            Else
            kty(I) = 0
            End If
            Next
        For I = 1 To (Sovachkhacy + 1)
        If kty(I) <> 0 Then
        ktytd(I) = dtdy - Int(kty(I) * ny) - 100
        End If
        Next
'Khac cac vach chia truc tung
            For I = 1 To (Sovachkhacy + 1)
            If kty(I) <> 0 Then
            frmDoThi.Line (950, ktytd(I) + 100)-(1050, ktytd(I) + 100)
              End If
            Next
'Dua cac gia tri y len truc tung
            For I = 1 To (Sovachkhacy + 1)
              If kty(I) <> 0 Then
            frmDoThi.ykhac(I).Caption = Format$(kty(I), "##0.0##")
            frmDoThi.ykhac(I).Move 450, ktytd(I)
              Else
            frmDoThi.ykhac(I).Caption = " "
              End If
            Next
End If
'--------------------------------------------------------------------------
If OnDinh = False Then
frmDoThi.Line1.Visible = False
frmDoThi.Line2.Visible = False
End If
'--------------------------------------------------------------------------
' Ve do thi
For I = 1 To k - 1
frmDoThi.Line (xtd(I), ytd(I))-(xtd(I + 1), ytd(I + 1)), QBColor(12)
Next
'--------------------------------------------------------------------------
'In Ket qua
If OnDinh = True Then
List1.AddItem "Gi¸ trÞ cùc ®¹i Ymax = " & Ymax
List1.AddItem "Thêi gian ®¹t cùc ®¹i tmax = " & Tmax & " s"
List1.AddItem "Gi¸ trÞ æn ®Þnh Yod = " & Round(Yod, 0)
List1.AddItem "§é qu¸ ®iÒu chØnh = " & Format$(Xichma, "##0.0##") & " %"
List1.AddItem " "
List1.AddItem "----------------------the Beginning Values-----------------------------------"
End If
List1.AddItem "100 Gi¸ trÞ tÝnh to¸n, mçi gi¸ trÞ c¸ch nhau 10, lµ: "
List1.AddItem ""
For I = 1 To 100
List1.AddItem "Y [" & (I * 10) & "] = " & Y(10 * I)
Next I
List1.AddItem " "
List1.AddItem "-----------------------the Ending Values--------------------------------------"
'--------------------------------------------------------------------------
End If
End Sub
Private Sub Ketqua_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
    KeyAscii = 0 ' Swallow keyEnter to avoid side effect
    Ketqua_Click 'Goi lai ham Ketqua_Click
    End If
End Sub
Private Sub saiso_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
    KeyAscii = 0 ' Swallow keyEnter to avoid side effect
    Ketqua_Click 'Goi lai ham Ketqua_Click
    End If
End Sub
Private Sub Timer1_Timer()
Form1.Caption = Right(Form1.Caption, Len(Form1.Caption) - 1)
    If Form1.Caption = "" Then
        Form1.Caption = Space(100) & "Main Program _ We are ACTive men _ GROUP 5 _ Call us if you have any questions"
    End If
End Sub
Private Sub txta_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
    KeyAscii = 0 ' Swallow keyEnter to avoid side effect
    Ketqua_Click 'Goi lai ham Ketqua_Click
    End If
End Sub
Private Sub txtk_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
    KeyAscii = 0 ' Swallow keyEnter to avoid side effect
    Ketqua_Click 'Goi lai ham Ketqua_Click
    End If
End Sub
Private Sub k_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
    KeyAscii = 0 ' Swallow keyEnter to avoid side effect
    Ketqua_Click 'Goi lai ham Ketqua_Click
    End If
End Sub
