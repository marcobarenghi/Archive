#!/usr/bin/python3
import string
import numpy as np
import matplotlib.pyplot as plt
from functions import readClean 
from functions import readCleanSort
from functions import plotHeaps
from functions import plotZipfs 
from functions import mergeBooks
from functions import readList
from functions import plotSpellsRec


#Zipf's law(s)
plotZipfs(readCleanSort('text/hp1.txt'), "Harry Potter & the Sorceres's Stone", "HP1-z.png", 'lime')
plotZipfs(readCleanSort('text/hp2.txt'), "Harry Potter & the Chamber of Secrets", "HP2-z.png", 'yellow')
plotZipfs(readCleanSort('text/hp3.txt'), "Harry Potter & the Prisoner of Azkaban", "HP3-z.png", 'magenta')
plotZipfs(readCleanSort('text/hp4.txt'), "Harry Potter & the Goblet of Fire", "HP4-z.png", 'aqua')
plotZipfs(readCleanSort('text/hp5.txt'), "Harry Potter & the Order of the Fenix", "HP5-z.png", 'orange')
plotZipfs(readCleanSort('text/hp6.txt'), "Harry Potter & the Half-Blood Prince", "HP6-z.png", 'lightskyblue')
plotZipfs(readCleanSort('text/hp7.txt'), "Harry Potter & the Deathly Hallows", "HP7-z.png", 'limegreen')
#Heap's law(s)
plotHeaps(readClean('text/hp1.txt'), "Harry Potter & the Sorceres's Stone", "HP1-h.png", 'lime')
plotHeaps(readClean('text/hp2.txt'), "Harry Potter & the Chamber of Secrets", "HP2-h.png", 'yellow')
plotHeaps(readClean('text/hp3.txt'), "Harry Potter & the Prisoner of Azkaban", "HP3-h.png", 'magenta')
plotHeaps(readClean('text/hp4.txt'), "Harry Potter & the Goblet of Fire", "HP4-h.png", 'aqua')
plotHeaps(readClean('text/hp5.txt'), "Harry Potter & the Order of the Fenix", "HP5-h.png", 'orange')
plotHeaps(readClean('text/hp6.txt'), "Harry Potter & the Half-Blood Prince", "HP6-h.png", 'lightskyblue')
plotHeaps(readClean('text/hp7.txt'), "Harry Potter & the Deathly Hallows", "HP7-h.png", 'limegreen')

#Spells recurrencies in saga
bookList = ['text/hp1.txt','text/hp2.txt','text/hp3.txt','text/hp4.txt','text/hp5.txt','text/hp6.txt','text/hp7.txt']
plotSpellsRec(readList('text/spells-fin.txt'),mergeBooks(bookList),"Spells in HP saga!","spellsHisto.png")



