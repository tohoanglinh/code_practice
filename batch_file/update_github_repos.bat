@ECHO OFF
CLS
REM ************************************************
REM ** BATCH FILE TO AUTOMATE GITHUB REPOS UPDATE BY WINDOWS CMD
REM ** AUTHOR: TO HOANG LINH
REM ************************************************
ECHO Update GitHub Repos...
ECHO [1] mac_bash_utility...
cd D:\code\gitworks\mac_bash_utility
git fetch && git pull
git add . && git commit -m 'update' && git push
ECHO [2] hackerrank_linhto...
cd D:\code\gitworks\hackerrank_linhto
git fetch && git pull
git add . && git commit -m 'update' && git push
PAUSE
EXIT