import math
#import matplotlib.pyplot as plt
import random
pourcentage = 15
iAgent = 1
iMaxAgent = 12
def calcShapley(iAgent,iMaxAgent,pourcentage = 100):
	for nbAgent in range(iAgent,iMaxAgent):
		calcMargFile = open("CalculContribMarginaleRSV"+str(pourcentage)+"_"+str(nbAgent)+".txt","w")
		fName = "ResultatEval"+str(nbAgent)+".txt"
		f1Name = "ResultatEval"+str(nbAgent+1)+".txt"
		agent = ['R','B','C','H']
		dic = getTabFile(fName)
		print(dic)
		dic1 = getTabFile(f1Name)
		comb=[]
		k=dic.keys()
		k = random.sample(k,int(len(k)*(pourcentage/100)))
		for ke in k:
			r,b,c,h = ke.split('/')
			comb.append([int(r),int(b),int(c),int(h)])
		print(comb)
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
			somme = somme/(math.factorial(len(agent))*(pourcentage/100))
			print("contribMarg de "+str(agent[ag])+" : " +str(somme)+"\n")
			calcMargFile.write(str(agent[ag])+" " +str(somme)+"\n")
			val.append(somme)
		calcMargFile.close()
		print(agent)
		print(val)
		
		#plt.bar([1,2,3,4],val)
		#plt.xticks([1,2,3,4],agent)
		#plt.show()

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


calcShapley(iAgent,iMaxAgent,pourcentage)
