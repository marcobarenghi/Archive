import sys
import os
import time
import random
import datetime
import numpy as np
import matplotlib.pyplot as plt
#from sklearn.linear_model import LinearRegression
random.seed(time.time())

class VocabGame:
	def __init__(self):
		self.ita = []
		self.de = []
		self.extra = []
		self.guessed = 0
		self.N = 0
		self.loaded = False

	def Read_File(self,file_name):
		with open(file_name, 'r') as data:
			for line in data:
				p = line.split(';')
				self.ita.append(str(p[0]))
				self.de.append(str(p[1]))
				self.extra.append(str(p[2]))
	
	def setGame(self,pathDir):
		print("Welcome to your personal dictionary game!","\n")
		
		fileList = ["nouns.txt","adjs.txt","verbs.txt","extra.txt","wos.txt"]
		for i in fileList:
			myanswer = str()
			print("Do you want to load",i,"? (y/n)")
			myanswer = input()
			if (myanswer == "y"):
				self.Read_File(str(pathDir+"/"+i))
				print(i,"loaded!")
				self.loaded = True
			else: 
				print(i, "NOT loaded!")


	def playGame(self):
		if (self.loaded == False):
			print("NO FILES WERE LOADED - CAN NOT PLAY")
			sys.exit()
			
		print("\n")
		n = input("How many words do you want to guess? ")
		n = int(n) 
		if (n < 1):
			print("Number of words not valid!!!")
			sys.exit()
			 
		self.N = n 
		guess = str()
		guessed = 0
		for i in range(n):
		    r1 = random.uniform(0, 1) 
		    r2 = r = int(random.uniform(0, len(self.ita))) #randomly select one line of the dictionary
		    if(r1<0.5): #start with italian p = 0.5
		        print("The word is:", self.ita[r2])
		        guess = input ()
		        if guess  == self.de[r2]:
		            print("Good job! The word was: ", self.de[r2],";",self.extra[r2])
		            self.guessed=self.guessed+1
		        else:
		            print("Try again... ")
		            guess = input ()
		            if guess  == self.de[r2]:
		                print("Good job! The word was: ", self.de[r2],";",self.extra[r2]) 
		                self.guessed=self.guessed+1
		            else:
		                print("Unlucky! The word was: ", self.de[r2],";",self.extra[r2]) 
		    else:
		        print("The word is:",self.de[r2])
		        guess = input ()
		        if guess  == self.ita[r2]:
		            print("Good job! The word was: ", self.de[r2],";",self.extra[r2])
		            self.guessed=self.guessed+1
		        else:
		            print("Try again... ")
		            guess = input ()
		            if guess  == self.ita[r2]:
		                print("Good job! The word was: ", self.de[r2],";",self.extra[r2]) 
		                self.guessed=self.guessed+1
		            else:
		                print("Unlucky! The word was: ", self.ita[r2]) 			                
	
	def printResults(self):
		print("Game is over. You guessed ",self.guessed, "/",self.N,"words.","\n")
		print("See ya next time","\n")
	
	def updateHistory(self):
		outputFile = open('results/myfile.txt','a+')
				
		now = datetime.datetime.now()
		outputFile.write(str(now.strftime("%Y-%m-%d %H:%M")) + " " + str(self.guessed / self.N * 100) + "\n")
		outputFile.close()
		
	def displayProgress(self):
		inputFile = open('results/progressfile.txt','r')
		count = 0
		array = []
		for line in inputFile:
			if line != "\n":
				count = count + 1
			p = line.split(' ')
			array.append(float(p[2]))
			
		plt.style.use('dark_background')
		fig, ax = plt.subplots()
		plt.plot(range(1,count+1), array, marker='o', c = "lightskyblue")
		plt.grid(color = 'white', linestyle = '--', linewidth = 0.5)
		ax.set_ylabel('Score')
		ax.set_title("Progress history!",  weight='bold')
		plt.show()
