#!/usr/bin/python

import string
from xml.dom.minidom import parseString
 
file = open('phonebook.xml','r')
data = file.read()
file.close()

foo = open('phonebook','rw+')
dom = parseString(data)

def handleEntries(entries):
	rows = 0
	xmlEntries = entries.getElementsByTagName("entry")
	for entry in xmlEntries:
		extension = handleExtensions(entry)
		name = handleName(entry)
		phonetype = handlePhonetype(entry)
		# Ausgabe in ./phonebook
		if int(phonetype) == 20:
			rows += 1
			foo.write('echo "sms 1 ' + extension + ' only one ping, Vasily"\n' + 'sleep 10\n' )
	print rows

def handlePhonetype(entry):
	xmlPhonetype = entry.getElementsByTagName("phonetype")[0].toxml()
	xmlData = xmlPhonetype.replace('<phonetype>', '').replace('</phonetype>', '')
	return xmlData

def handleName(entry):
	xmlName = entry.getElementsByTagName("name")[0].toxml()
	xmlData = xmlName.replace('<name>', '').replace('</name>', '')
	return xmlData

def handleExtensions(entry):
	xmlExtension = entry.getElementsByTagName("extension")[0].toxml()
	xmlData = xmlExtension.replace('<extension>', '').replace('</extension>','')
	return xmlData

handleEntries(dom)
foo.close()
