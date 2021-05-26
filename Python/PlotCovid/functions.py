#!/usr/bin/python3

import pandas as pd
import matplotlib.pyplot as plt


def userInput(userList):
	n = input("How many countries do you want to get information about? ")
	n = int(n) 
		
	if (n > 0):
		for i in range(n):
			answer = str()
			print("Select country #", i+1)
			answer = input()
			userList.append(answer)
	else:
		print("Only EU data will be displayed")
		
def covidStats(List):
	print("\n GETTING DATA! Please wait a few secs")
	List.append("European Union")
	df = pd.read_csv("https://raw.githubusercontent.com/owid/covid-19-data/master/public/data/vaccinations/vaccinations.csv")
	df2 = pd.read_csv("https://raw.githubusercontent.com/owid/covid-19-data/master/public/data/owid-covid-data.csv")

	info = df[["location", "date", "total_vaccinations_per_hundred", "people_vaccinated_per_hundred", "people_fully_vaccinated_per_hundred"]]
	data = info.values
	info2 = df2[["location", "date", "new_cases_smoothed_per_million"]]
	data2 = info2.values


	fig, (ax1, ax2) = plt.subplots(2)
	for country in List:
		mask = data[:,0] == country #filter per country
		data_with_mask =data[mask]
		dates = data_with_mask[:,1][:-1]
		nPoints = len(dates)
		startingDate = dates[0]
		cumuVax = data_with_mask[:,2][:-1]
		mask2 = data2[:,0] == country
		data_with_mask2 =data2[mask2]
		newCases = data_with_mask2[:,2][-nPoints-1:-1]
		
		#print some info
		print("\n", "-----",country, "-----")
		print(f"Total vaccinations per hundred: {float(data_with_mask[-1:,2][0])}")
		print(f"Vaccinated people per hundred: {float(data_with_mask[-1:,3][0])}")
		print(f"Fully vaccinated people per hundred: {float(data_with_mask[-1:,4][0])}")
		
		ax1.plot(range(nPoints), cumuVax, label=country)
		ax1.legend(loc='upper left');
		ax1.set_title("Vaccinated people (per hundred)", weight="bold")
		ax2.plot(range(nPoints), newCases, label=country)
		ax2.set_title("Smoothed new cases (per million)",weight="bold")
		ax2.legend(loc='upper left');
		
	fig.suptitle('Vaccinations and new cases from ' + str(startingDate), size=12, style='italic')	
	plt.show()
	
