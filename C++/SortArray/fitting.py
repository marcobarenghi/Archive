#!/bin/python3
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import numpy as np
import math

def func1( x, a, b, c):
	return a + b*x + c*x*x
	
def func2( x,  d, e,  f):
	return d + e*x*np.log(x)


x = np.array([])
meanstdsort = np.array([])
meanmergesort = np.array([])

f = open("data.txt", "r")
for inputdata in f:
	x = np.append(x, float(inputdata.split(' ')[0]))
	meanstdsort = np.append(meanstdsort, float(inputdata.split(' ')[1]))
	meanmergesort = np.append(meanmergesort, float(inputdata.split(' ')[3]))

popt, pcov = curve_fit(func1, x, meanstdsort)
plt.scatter(x, meanstdsort, marker='o', color = "blue", label='Standard sorting - data')
plt.plot(x, func1(x, *popt), color = 'lightskyblue',label='Standard sorting - fit O(n^2)')

popt2, pcov2 = curve_fit(func2, x, meanmergesort)
plt.scatter(x, meanmergesort, marker='o', color = "red", label='Merge sorting - data')
plt.plot(x, func2(x, *popt2), color = 'orange',label='Merge sorting - fit O(nlog(n))')

plt.title("Standard vs merge sorting - ./example results", weight ="bold")
plt.xlabel('Number of elements')
plt.ylabel(' \u03BC s to sort')
plt.legend()
plt.yscale('log')
plt.show()
