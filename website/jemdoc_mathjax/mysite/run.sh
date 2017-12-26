#!/bin/bash
xampp_path="C:/xampp/htdocs/"

# start compiling
echo "[1].Compiling mysite... :-)"
../jemdoc -c mathjax.conf -o html/ *.jemdoc
# ../jemdoc -c googleanalytics.conf -o html/ *.jemdoc && ../jemdoc -c bibover.conf -o html/ *.jemdoc

cp -r html/. ../../../../tohoanglinh.github.io/

# remove contents of htdocs folder?
if [ "$(ls -A $xampp_path)" ]; then
    echo "$xampp_path is not empty"
    read -p "Remove existing contents(y/n)?" answer
    if [ "$answer" == "y" ] || [ "$answer" == "Y" ]; then
        echo "--Removing everything...Done!"
        rm -rf $xampp_path*
        # start uploading website
        echo "[2].Uploading to htdocs... :-)"
        cp -r html/. $xampp_path
    fi
else
    echo "$xampp_path is empty"
    # start uploading website
    echo "[2].Uploading to htdocs... :-)"
    cp -r html/. $xampp_path
fi

# finish
echo "DONE!"
