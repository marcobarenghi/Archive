#!/usr/bin/python3
import string
import numpy as np
import matplotlib.pyplot as plt
import myClasses as s
import random as r
r.seed(10)

print("Loading network info: name, coord, lat")
nodeList = s.Nodes()
f=open("mi2_info.txt","r")
lines=f.readlines()
for x in lines:
	nodeList.loadNode(x.split(' ')[0], x.split(' ')[1],x.split(' ')[2].rstrip("\n"))
f.close()
print("Number of nodes: ", nodeList.getSize())
print(" ")

print("Loading network links")
net = s.Network()
net2 = s.Network()

node1 = r.randrange(nodeList.getSize())
node2 = r.randrange(nodeList.getSize())
node3 = r.randrange(nodeList.getSize())
net.loadNetwork("mi2_edges.txt", nodeList,True)
net2.loadNetwork("mi2_edges.txt", nodeList,False)
print("Number of edges: ", net.getNumberOfEdges())

print("Distances [km] between random nodes")
net.dijkstra(node1,node2)
net.dijkstra(node2,node3)
net.dijkstra(node3,node1)
print("Distances [artitrary unit] between random nodes")
net2.dijkstra(node1,node2)
net2.dijkstra(node2,node3)
net2.dijkstra(node3,node1)
