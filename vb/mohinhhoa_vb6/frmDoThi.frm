VERSION 5.00
Begin VB.Form frmDoThi 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Graph"
   ClientHeight    =   7770
   ClientLeft      =   360
   ClientTop       =   885
   ClientWidth     =   11070
   Icon            =   "frmDoThi.frx":0000
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   ScaleHeight     =   7770
   ScaleWidth      =   11070
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton refresh 
      Caption         =   "Refresh"
      Height          =   375
      Left            =   9840
      TabIndex        =   29
      Top             =   360
      Width           =   975
   End
   Begin VB.Line Line2 
      X1              =   11160
      X2              =   11520
      Y1              =   4680
      Y2              =   4680
   End
   Begin VB.Line Line1 
      X1              =   11400
      X2              =   11760
      Y1              =   4800
      Y2              =   4800
   End
   Begin VB.Label ykhac 
      Alignment       =   2  'Center
      Height          =   255
      Index           =   11
      Left            =   0
      TabIndex        =   28
      Top             =   0
      Width           =   495
   End
   Begin VB.Label ykhac 
      Alignment       =   2  'Center
      Caption         =   "ykhac"
      Height          =   255
      Index           =   10
      Left            =   0
      TabIndex        =   27
      Top             =   0
      Width           =   495
   End
   Begin VB.Label ykhac 
      Alignment       =   2  'Center
      Caption         =   "ykhac"
      Height          =   255
      Index           =   9
      Left            =   0
      TabIndex        =   26
      Top             =   0
      Width           =   495
   End
   Begin VB.Label ykhac 
      Alignment       =   2  'Center
      Caption         =   "ykhac"
      Height          =   255
      Index           =   8
      Left            =   0
      TabIndex        =   25
      Top             =   0
      Width           =   495
   End
   Begin VB.Label ykhac 
      Alignment       =   2  'Center
      Caption         =   "ykhac"
      Height          =   255
      Index           =   7
      Left            =   0
      TabIndex        =   24
      Top             =   0
      Width           =   495
   End
   Begin VB.Label ykhac 
      Alignment       =   2  'Center
      Caption         =   "ykhac"
      Height          =   255
      Index           =   6
      Left            =   0
      TabIndex        =   23
      Top             =   0
      Width           =   495
   End
   Begin VB.Label ykhac 
      Alignment       =   2  'Center
      Caption         =   "ykhac"
      Height          =   255
      Index           =   5
      Left            =   0
      TabIndex        =   22
      Top             =   0
      Width           =   495
   End
   Begin VB.Label ykhac 
      Alignment       =   2  'Center
      Caption         =   "ykhac"
      Height          =   255
      Index           =   4
      Left            =   0
      TabIndex        =   21
      Top             =   0
      Width           =   495
   End
   Begin VB.Label ykhac 
      Alignment       =   2  'Center
      Caption         =   "ykhac"
      Height          =   255
      Index           =   3
      Left            =   0
      TabIndex        =   20
      Top             =   0
      Width           =   495
   End
   Begin VB.Label ykhac 
      Alignment       =   2  'Center
      Caption         =   "ykhac"
      Height          =   255
      Index           =   2
      Left            =   0
      TabIndex        =   19
      Top             =   0
      Width           =   495
   End
   Begin VB.Label ykhac 
      Alignment       =   2  'Center
      Caption         =   "ykhac"
      Height          =   255
      Index           =   1
      Left            =   0
      TabIndex        =   18
      Top             =   0
      Width           =   495
   End
   Begin VB.Label xkhac 
      Height          =   255
      Index           =   10
      Left            =   6240
      TabIndex        =   17
      Top             =   120
      Width           =   495
   End
   Begin VB.Label xkhac 
      Height          =   255
      Index           =   9
      Left            =   6120
      TabIndex        =   16
      Top             =   120
      Width           =   495
   End
   Begin VB.Label xkhac 
      Height          =   255
      Index           =   8
      Left            =   6120
      TabIndex        =   15
      Top             =   120
      Width           =   495
   End
   Begin VB.Label xkhac 
      Height          =   255
      Index           =   7
      Left            =   6120
      TabIndex        =   14
      Top             =   120
      Width           =   495
   End
   Begin VB.Label xkhac 
      Height          =   255
      Index           =   6
      Left            =   6360
      TabIndex        =   13
      Top             =   120
      Width           =   495
   End
   Begin VB.Label xkhac 
      Height          =   255
      Index           =   5
      Left            =   6240
      TabIndex        =   12
      Top             =   120
      Width           =   495
   End
   Begin VB.Label xkhac 
      Height          =   255
      Index           =   4
      Left            =   6360
      TabIndex        =   11
      Top             =   120
      Width           =   495
   End
   Begin VB.Label xkhac 
      Height          =   255
      Index           =   3
      Left            =   6240
      TabIndex        =   10
      Top             =   120
      Width           =   495
   End
   Begin VB.Label xkhac 
      Height          =   255
      Index           =   2
      Left            =   6360
      TabIndex        =   9
      Top             =   120
      Width           =   495
   End
   Begin VB.Label xkhac 
      Height          =   255
      Index           =   1
      Left            =   6240
      TabIndex        =   8
      Top             =   120
      Width           =   495
   End
   Begin VB.Label xkhac 
      Height          =   255
      Index           =   0
      Left            =   6120
      TabIndex        =   7
      Top             =   120
      Width           =   495
   End
   Begin VB.Label loiTod 
      Height          =   375
      Left            =   9360
      TabIndex        =   6
      Top             =   1560
      Width           =   2175
   End
   Begin VB.Label tentrucx 
      Alignment       =   2  'Center
      Height          =   255
      Left            =   10920
      TabIndex        =   5
      Top             =   2160
      Width           =   495
   End
   Begin VB.Label tentrucy 
      Height          =   255
      Left            =   10920
      TabIndex        =   4
      Top             =   2640
      Width           =   495
   End
   Begin VB.Label Tod 
      Height          =   255
      Left            =   9240
      TabIndex        =   3
      Top             =   3120
      Width           =   1095
   End
   Begin VB.Label Yod 
      Height          =   255
      Left            =   9360
      TabIndex        =   2
      Top             =   2640
      Width           =   1095
   End
   Begin VB.Label Tmax 
      Height          =   255
      Left            =   9360
      TabIndex        =   1
      Top             =   3600
      Width           =   1095
   End
   Begin VB.Label Ymax 
      Height          =   255
      Left            =   9360
      TabIndex        =   0
      Top             =   2160
      Width           =   1095
   End
End
Attribute VB_Name = "frmDoThi"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
SetIcon Me.hWnd, "AAA"
End Sub

Private Sub refresh_Click()
Form1.tinh_ket_qua
End Sub
