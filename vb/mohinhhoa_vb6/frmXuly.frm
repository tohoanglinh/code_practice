VERSION 5.00
Begin VB.Form frmXuly 
   Caption         =   "Errors"
   ClientHeight    =   1995
   ClientLeft      =   7575
   ClientTop       =   10740
   ClientWidth     =   6585
   Icon            =   "frmXuly.frx":0000
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   ScaleHeight     =   1995
   ScaleWidth      =   6585
   Begin VB.Frame Frame1 
      Caption         =   "These are two mistakes you could  have made"
      BeginProperty Font 
         Name            =   ".VnTime"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1455
      Left            =   120
      TabIndex        =   1
      Top             =   0
      Width           =   6375
      Begin VB.Image Image1 
         Height          =   1080
         Left            =   120
         Picture         =   "frmXuly.frx":030A
         Top             =   240
         Width           =   6075
      End
   End
   Begin VB.CommandButton DongY 
      Caption         =   "NhËp l¹i !"
      BeginProperty Font 
         Name            =   ".VnTime"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2640
      TabIndex        =   0
      ToolTipText     =   "Click here to Return to MAIN"
      Top             =   1560
      Width           =   1335
   End
End
Attribute VB_Name = "frmXuly"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub DongY_Click()
Unload frmXuly
Form1.Show
End Sub

Private Sub Form_Load()
SetIcon Me.hWnd, "AAA"
End Sub
