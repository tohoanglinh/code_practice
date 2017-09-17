@ECHO OFF
REM ************************************************
REM ** BATCH FILE TO AUTOMATE GIT REPOS UPDATE BY WINDOWS CMD
REM ** AUTHOR: TO HOANG LINH
REM ** USAGE : update name_of_git_repo name_commit
REM ************************************************
ECHO -----------------------------------------------
ECHO Updating Git Repos: %1...
cd /D D:\gitworks\%1
SET gitfolder=0
IF "%1"=="code_practice" SET gitfolder=1

IF "%1"=="automation" SET gitfolder=2
IF "%1"=="doc-internal" SET gitfolder=2
IF "%1"=="s32_internal_tools" SET gitfolder=2
IF "%1"=="s32_sdk_vnv_testing" SET gitfolder=2
IF "%1"=="lwip" SET gitfolder=2
IF "%1"=="wolfssl" SET gitfolder=2

IF "%1"=="sdk_codebase" SET gitfolder=3
IF "%1"=="tcpip_stack" SET gitfolder=3
IF "%1"=="anfc_codebase" SET gitfolder=3

IF %gitfolder%==1 (
  git fetch && git pull
  IF "%2" == "" (
    git add . && git commit -m update && git push
  ) ELSE (
    git add . && git commit -m %2 && git push
  )
)

IF %gitfolder%==2 (
  ECHO Fetching a git repo
  git fetch && git pull
)

IF %gitfolder%==3 (
  ECHO This repo should not be update by this batch file.
  ECHO Please do it carefully by manual.
)
PAUSE
