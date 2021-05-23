#!/usr/bin/python3
import numpy as np
from math import sin, cos, sqrt, atan2, radians, sqrt
import sys

class Nodes:
	def __init__(self):
		self.size = 0
		self.node = []
		self.coord1 = []
		self.coord2 = []
		
	def loadNode(self,name,c1,c2):
		self.node.append(name)
		self.coord1.append(c1)
		self.coord2.append(c2)
		self.size = self.size + 1
		
	def getSize(self):
		return self.size
		
	def getName(self,n):
		return self.node[n]
		
	def getNameList(self):
		return self.node
		
	def getCoord1(self, n):
		return((self.coord1[n]))
			
	def getCoord2(self, n):
		return((self.coord2[n]))
		
	def printInfo(self):
		for i in range(self.size):
			print(self.node[i],self.coord1[i], self.coord2[i])
			
class Network: 
	def __init__(self):
		self.size = 0
		self.edges = 0
		self.adjiacencyMatrix = np.array([])
		self.vertices = np.array([])
		
	def getMatrixSize(self):
		return self.size
		
	def getNumberOfEdges(self):
		return self.edges		
		
	def loadNetwork(self,inputfile, nodes, flag):
		R = 6373
		lat1 = 0
		lat2 = 0
		lon1 = 0
		lon2 = 0
		self.adjiacencyMatrix = np.zeros((nodes.getSize(),nodes.getSize()))
		self.vertices = np.zeros((nodes.getSize()))
		for i in range((nodes.getSize())):
			self.vertices[i] = i + 1
		
		self.size = nodes.getSize()*nodes.getSize()
		f=open(inputfile,"r")
		lines=f.readlines()
		for x in lines:
			left = x.split(' ')[0]
			right = x.split(' ')[1]	
			foundOne = False	
			foundTwo = False	
			for i in range(nodes.getSize()):
				if nodes.getName(i) == left:
					foundOne = True	
					if(flag == True):
						lat1 = radians(float(nodes.getCoord1(i)))
						lon1 = radians(float(nodes.getCoord2(i)))

				if nodes.getName(i) == right:
					foundTwo = True	
					if(flag == True):
						lat2 = radians(float(nodes.getCoord1(i)))
						lon2 = radians(float(nodes.getCoord2(i)))
					
			if (flag == True):
				dlon = lon2 - lon1
				dlat = lat2 - lat1
				a = sin(dlat / 2)**2 + cos(lat1) * cos(lat2) * sin(dlon / 2)**2
				c = 2 * atan2(sqrt(a), sqrt(1 - a))
				d = R * c
				self.adjiacencyMatrix[int(right)-1][int(left)-1] = d
				self.edges = self.edges + 1
			else:
				self.adjiacencyMatrix[int(right)-1][int(left)-1] = 1
				self.edges = self.edges + 1
				
		f.close()
		
	def printNetwork(self):
		for j in range(int(sqrt(self.size))):
			for k in range(int(sqrt(self.size))):
				print("{:.1f}".format(self.adjiacencyMatrix[k][j]), end = ' ')
			print("\n")

	def minDistance(self, dist, sptSet):
		minD = 1000000
		for v in range(int(sqrt(self.size))):
			if dist[v] < minD and sptSet[v] == False:
				minD = dist[v]
				min_index = v
		return min_index
		
	def dijkstra(self, src, node2):
		dist = [1000000] * self.vertices
		dist[src] = 0
		sptSet = [False] * self.vertices
  
		for count in range(int(sqrt(self.size))):
			u = self.minDistance(dist, sptSet)
			sptSet[u] = True
			for v in range(int(sqrt(self.size))):
				if self.adjiacencyMatrix[u][v] > 0 and sptSet[v] == False\
			    and dist[v] > dist[u] + self.adjiacencyMatrix[u][v]:
					dist[v] = dist[u] + self.adjiacencyMatrix[u][v]
		print ("Distance between nodes: ",src, "-", node2, "=", "{:.1f}".format(dist[node2]))
