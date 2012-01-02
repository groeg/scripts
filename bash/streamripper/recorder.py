#!/usr/bin/python
import os, sys
from time import strftime as date

#stream = "http://mp3stream1.apasf.apa.at:8000/listen.pls"
#length = 600

urls = { "fm4": "http://mp3stream1.apasf.apa.at:8000/listen.pls",
						"oe3": "www.google.com" }

if len(sys.argv) != 3:
	raise SystemExit, "usage: %s station-name length" % sys.argv[0]

stream_name = sys.argv[1]
length = sys.argv[2]

if stream_name not in urls:
	raise SystemExit, "%s not a valid radio station. Stations are: %s" % (stream_name, str(urls.keys()))

file_name = stream_name + "_" + date('%Y-%m-%d_%H:%M')

os.system("streamripper " + urls[stream_name] + " -D ~/Music/streams -a -l " + length)
os.system("mv ~/Music/streams/incomplete/*mp3 ~/Music/streams/" + file_name +
          ".mp3")
