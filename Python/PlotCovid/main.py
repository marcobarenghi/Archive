#!/usr/bin/python3
import pandas as pd
import matplotlib.pyplot as plt
from functions import covidStats, userInput

print("\n  Covid19 data visualization! \n")

#List = ["Germany","Austria", "Italy"]
List2 = []
nDays = 0
List2, nDays = userInput()
covidStats(List2,nDays)
