#!/bin/bash

: <<'END'
How to: Delete everyfiles except some

find . -maxdepth 1 ! -name "file1" ! -name "file2" -type f -delete
! negates the next expression
-name specifies a filename
-maxdepth 1 will make find process the specified directory only (find by default traverses directories)
-type f will process only files (and not for example directories)
-delete will delete the files

Update

Keep in mind that the order of the elements of the expressions is significant (see the documentation)
Test your command first by using -print instead of -delete

find . -maxdepth 1 ! -name "file1" ! -name "file2" -type f -print
END

gnuplot test.gpl
latex test.tex
dvips -o test.ps test.dvi
ps2pdf test.ps test.pdf
find . -maxdepth 1 ! -name "test.gp" ! -name "test.pdf" ! -name "convert.sh" -type f -delete
evince test.pdf
