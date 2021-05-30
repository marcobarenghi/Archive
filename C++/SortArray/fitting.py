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
sigmastdsort = np.array([])
meanmergesort = np.array([])
sigmamergesort = np.array([])

N = 0
f = open("data.txt", "r")
for inputdata in f:
	x = np.append(x, float(inputdata.split(' ')[0]))
	meanstdsort = np.append(meanstdsort, float(inputdata.split(' ')[1]))
	sigmastdsort = np.append(sigmastdsort, float(inputdata.split(' ')[2]))
	meanmergesort = np.append(meanmergesort, float(inputdata.split(' ')[3]))
	sigmamergesort = np.append(sigmamergesort, float(inputdata.split(' ')[4]))
	N = N + 1

#fitting & plotting
popt, pcov = curve_fit(func1, x, meanstdsort, sigma = sigmastdsort)
plt.scatter(x, meanstdsort, marker='o', color = "blue", label='Standard sorting - data')
plt.plot(x, func1(x, *popt), color = 'lightskyblue',label='Standard sorting - fit O(n^2)')
popt2, pcov2 = curve_fit(func2, x, meanmergesort, sigma = sigmamergesort)
plt.scatter(x, meanmergesort, marker='o', color = "red", label='Merge sorting - data')
plt.plot(x, func2(x, *popt2), color = 'orange',label='Merge sorting - fit O(nlog(n))')

#chi^2 calculation
meanExp = func1(x, *popt)
r = meanstdsort - meanExp
chisq = np.sum((r/sigmastdsort)**2)
df = N - 2
print("Reduced chi^2 standard sorting = ", round((chisq / df),2))
meanExp2 = func2(x, *popt2)
r2 = meanmergesort - meanExp2
chisq2 = np.sum((r2/sigmamergesort)**2)
print("Reduced chi^2 merge sorting = ", round((chisq2 / df),2))

#end plotting
plt.title("Standard vs merge sorting - ./example results", weight ="bold")
plt.xlabel('Number of elements')
plt.ylabel(' \u03BC s to sort')
plt.legend()
plt.yscale('log')
plt.show()
