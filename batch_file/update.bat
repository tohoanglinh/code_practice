@ECHO OFF
REM ************************************************
REM ** BATCH FILE TO AUTOMATE GIT REPOS UPDATE BY WINDOWS CMD
REM ** AUTHOR: TO HOANG LINH
REM ** USAGE : update name_of_git_repo name_commit
REM ************************************************
ECHO -----------------------------------------------
ECHO Updating Git Repos: %1...
cd /D D:\gitworks\%1
git fetch && git pull
git add . && git commit -m %2 && git push
PAUSE
