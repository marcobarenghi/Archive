#!/usr/bin/python3
import pandas as pd
import matplotlib.pyplot as plt
from functions import covidStats, userInput

print(" \nPlotting and comparing vaccinations!")

#List = ["Germany","Austria", "Italy"]
List2 = []
userInput(List2)
covidStats(List2)
