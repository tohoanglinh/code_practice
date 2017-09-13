#!/bin/bash
echo "Compiling main-website... :-)"

../jemdoc -c googleanalytics.conf -o html/ *.jemdoc && ../jemdoc -c mathjax.conf -o html/ *.jemdoc  && ../jemdoc -c bibover.conf -o html/ *.jemdoc && ../jemdoc -c bibtex.conf -o html/ publications.jemdoc

#jemdoc -c googleanalytics.conf -o html/ *.jemdoc && jemdoc -c mathjax.conf -o html/ *.jemdoc && jemdoc -c bibtex.conf -o html/ publications.jemdoc

#../jemdoc.py -c googleanalytics.conf -o html/ *.jemdoc && ../jemdoc.py -c mathjax.conf -o html/ *.jemdoc && ../jemdoc.py -c bibtex.conf -o html/ publications.jemdoc

echo "DONE!"
