#!/usr/bin/python

import sys

# open fullmoon file (copy full moon dates from http://home.hiwaay.net/~krcool/Astro/moon/fullmoon.htm into a simple textfile called 'fullmoon')
try:
	fo = open("fullmoon", "r")
except:
	print "Couldn't open file. Copy full moon dates from http://home.hiwaay.net/~krcool/Astro/moon/fullmoon.htm into a textfile called 'fullmoon' in the same directory"
	sys.exit(0)
months = dict(Jan=1, Feb=2, Mar=3, Apr=4, May=5, Jun=6, Jul=7, Aug=8, Sep=9, Oct=10, Nov=11, Dec=12)

print "/* BEGIN OF AUTO-GENERATED CODE */"
print "/*"
print " * Dates of a full moon {day, month, year-2000}"
print " * Auto-generated using python script and"
print " * http://home.hiwaay.net/~krcool/Astro/moon/fullmoon.htm"
print " */"
print "struct date fullMoon[] = {"
for line in fo:
	stringlist = ' '.join(line.split())
	stringlist = stringlist.split(' ')
	year = int(stringlist[0]) - 2000
	month = months[stringlist[1]]
	day = int(stringlist[2])
	print "{ %i, %i, %i}," % (day, month, year)
print "};"
print "/* END OF AUTO-GENERATED CODE */"
	
