@ECHO OFF
CLS
REM ************************************************
REM ** BATCH FILE TO AUTOMATE START-UP BY WINDOWS CMD
REM ** AUTHOR: TO HOANG LINH
REM ************************************************
ECHO Starting all essential applications...
start "" "C:\Program Files\Microsoft Office\Office15\OUTLOOK.EXE"
start "" "C:\NXP\S32DS_Power_v1.2\eclipse\s32ds.exe"
start "" "C:\Program Files (x86)\Google\Chrome\Application\chrome.exe"
start C:\Users\LinhTH8\AppData\Local\SourceTree\Update.exe --processStart "SourceTree.exe"
EXIT