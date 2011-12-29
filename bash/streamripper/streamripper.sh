#!/bin/bash
# Skript zum Speichern eines Radio mp3-Streams
# Wichtig! Ausfuehrbarmachen nicht vergessen! (chmod u+x)

# Script stammt von u.a. Adresse
# http://wiki.ubuntuusers.de/Internetradio_aufzeichnen

DATUM=`date +%Y-%m-%d_%RUhr`
streamripper http://mp3stream1.apasf.apa.at:8000/listen.pls -D ~/radiorips -l 60  &&
mv ~/radiorips/incomplete/*mp3 ~/radiorips/$DATUM.mp3 &&
rmdir ~/radiorips/incomplete/
