#!/usr/bin/python3
import string
import numpy as np
import matplotlib.pyplot as plt
import random
from sklearn.linear_model import LinearRegression
import re

def readList(filename):
	file = open(filename, 'r')
	text = file.read()
	text = re.sub(r'[^\w\s]','',text)
	file.close()

	words = text.split('\n')
	table = str.maketrans('', '', string.punctuation)
	textArray = [w.translate(table) for w in words]
	return textArray[:len(textArray)-1]

def readClean(filename):
	file = open(filename, 'r')
	text = file.read().lower()
	text = re.sub(r'[^\w\s]','',text)
	file.close()

	words = text.split()
	table = str.maketrans('', '', string.punctuation)
	textArray = [w.translate(table) for w in words]
	return textArray
	
def readCleanSort(filename):
	file = open(filename, 'r')
	text = file.read().lower()
	text = re.sub(r'[^\w\s]','',text)
	file.close()

	words = text.split()
	table = str.maketrans('', '', string.punctuation)
	textArray = [w.translate(table) for w in words]
	textArray.sort()
	return textArray

def mergeBooks(bookList):
	
	text = ''
	for filename in bookList:
		file = open(filename, 'r')
		text += file.read().lower()
		text = re.sub(r'[^\w\s]','',text)
		file.close()
 
	words = text.split()
	table = str.maketrans('', '', string.punctuation)
	textArray = [w.translate(table) for w in words]
	return textArray

def plotHeaps(textArray, title, output, color):
	newWords = []
	newWords.append(textArray[0])
	countNewWords = 1
	countSupport = np.array([])
	axisSupport = np.array([])
	numbers = [1,2,5,7, 10, 20, 50, 100, 200, 500, 700, 1000, 2000, 5000, 7000, 10000, 20000, 50000, 70000, 100000, 200000, 500000 ]
	
	for i in range(1,len(textArray)):
		counter = 0
		for j in range(len(newWords)):
			if textArray[i] != newWords[j]:
				counter = counter + 1
		if counter == len(newWords):
			newWords.append(textArray[i])
			countNewWords = countNewWords + 1			
		for k in range(len(numbers)):
			if numbers[k] == i:
				countSupport = np.append(countSupport,countNewWords)
				axisSupport = np.append(axisSupport,i)
		if i == len(textArray) -1:
			countSupport = np.append(countSupport,countNewWords)
			axisSupport = np.append(axisSupport,i)
		
	model = LinearRegression(fit_intercept=True)
	axisSupport = np.array(axisSupport).reshape((-1, 1))
	model.fit(np.log(axisSupport), np.log(countSupport))

	xfit = axisSupport
	yfit = model.predict(xfit)
	print(title, " Heap's coeff = ", f'{np.exp(model.intercept_):.5}', ";" , f'{model.coef_[0]:.3}')
	plt.style.use('dark_background')
	fig, ax = plt.subplots()
	plt.scatter(axisSupport, countSupport, marker='o', c = color)
	#plt.plot(xfit,yfit, c = color, linewidth = 0.5)
	plt.grid(color = 'white', linestyle = '--', linewidth = 0.5)
	ax.set_xlabel('Words')
	ax.set_ylabel('New Words')
	ax.set_title(title, weight='bold')
	ax.set_yscale('log')
	ax.set_xscale('log')
	plt.savefig(output)

def plotZipfs(textArraySorted, title, output, color):
	newWords = []
	newWords.append(textArraySorted[0])
	countSupport = np.array([1])
	pos = 0
	for i in range(1,len(textArraySorted)):
		if textArraySorted[i] == textArraySorted[i-1]:
			countSupport[pos] = countSupport[pos] + 1
		else:
			pos = pos +1
			countSupport = np.append(countSupport,1)
			newWords.append(textArraySorted[i])
	
	sortedDistr = np.sort(countSupport)
	#I could write a sort function and print words
	
	rec = []
	rec.append(sortedDistr[0])
	countRec = np.array([1])
	newpos = 0
	for i in range(1,len(sortedDistr)):
		if(sortedDistr[i] == sortedDistr[i-1]):
			countRec[newpos] = countRec[newpos] + 1
		else:
			newpos = newpos +1
			countRec = np.append(countRec,1)
			rec.append(sortedDistr[i])
	####################
	model = LinearRegression(fit_intercept=True)
	rec = np.array(rec).reshape((-1, 1))
	model.fit(np.log(rec), np.log(countRec))

	xfit = rec
	yfit = model.predict(xfit)
	print(title, " Zipf's coeff = ", f'{model.coef_[0]:.3}')
	
	plt.style.use('dark_background')
	fig, ax = plt.subplots()
	plt.scatter(rec, countRec, marker='*', c = color)
	#plt.plot(xfit, yfit, c = color, linewidth = 0.5)
	plt.grid(color = 'white', linestyle = '--', linewidth = 0.5)
	ax.set_xlabel('Word rank')
	ax.set_ylabel('Frequency')
	ax.set_title(title,  weight='bold')
	ax.set_yscale('log')
	ax.set_xscale('log')
	plt.savefig(output)
	####################

def plotSpellsRec(spells, books, title,output):
	ypos = []
	countRec = []
	for j in range(len(spells)):
		counter = 0
		for i in range(len(books)-2):
			##all cases are needed in order to be sure get spells composed of 1 or 2 words
			if books[i] == spells[j].lower():
				counter = counter + 1
			elif books[i] + ' ' == spells[j].lower():
				counter = counter + 1
			elif str(books[i])+ ' ' + str(books[i+1]) == spells[j].lower():
				counter = counter + 1
			elif str(books[i])+ ' ' + str(books[i+1])  + ' ' == spells[j].lower():
				counter = counter + 1
			elif str(books[i])+ str(books[i+1]) == spells[j].lower():
				counter = counter + 1
		countRec.append(counter)
		ypos.append(j)

	y_pos = range(len(spells))
	fig, ax = plt.subplots()
	plt.style.use('dark_background')
	plt.bar(y_pos, countRec)
	plt.xticks(ypos, spells, rotation=90)
	ax.set_ylabel('Frequency')
	ax.set_title(title,  weight='bold')
	plt.savefig(output)
