import math
import matplotlib.pyplot as plt
def calcShapley():
	for nbAgent in range(5,8):
		calcMargFile = open("CalculContribMarginale_"+str(nbAgent)+".txt","w")
		fName = "ResultatEval"+str(nbAgent)+".txt"
		f1Name = "ResultatEval"+str(nbAgent+1)+".txt"
		agent = ['R','B','C','H']
		comb=[]
		for r in range(nbAgent+1):
			for b in range(nbAgent+1-r):
				for h in range(nbAgent+1-r-b):
					c = nbAgent-r-b-h
					comb.append( [r,b,c,h])
		dic = getTabFile(fName)
		dic1 = getTabFile(f1Name)
		val = []
		for ag in range(len(agent)):
			print(agent[ag])
			somme = 0
			for co in comb:
				toFind6 = str(co[0])+"/"+str(co[1])+"/"+str(co[2])+"/"+str(co[3])
				cn = int(dic[toFind6])
				toFind7 = str(co[0]+int(ag==0))+"/"+str(co[1]+int(ag==1))+"/"+str(co[2]+int(ag==2))+"/"+str(co[3]+int(ag==3))
				cn1 = int(dic1[toFind7])
				somme+=(cn1-cn)
			somme = somme/math.factorial(len(agent))
			print("contribMarg de "+str(agent[ag])+" : " +str(somme))
			calcMargFile.write("contribMarg de "+str(agent[ag])+" : " +str(somme))
			val.append(somme)
		calcMargFile.close()
		print(agent)
		print(val)
		
		plt.bar([1,2,3,4],val)
		plt.xticks([1,2,3,4],agent)
		plt.show()

def getTabFile(f):
	fp = open(f,'r')
	line = fp.readline()
	d = dict()
	i = 0
	while line:
		if not('R' in line):
			comb,val = line.split(" ") 
			d[comb]=val
		line = fp.readline()
	fp.close()
	return d


def findValueInFile(f,val):
	fp = open(f,'r')
	line = fp.readline()
	while line:
		if(val in line):
			comb,val = line.split(" ")
			fp.close()
			return val
		line = fp.readline()

	fp.close()
	return -1


calcShapley()
