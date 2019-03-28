import math
def calcShapley():
    nbAgent = 5
    fName = "ResultatEval"+str(nbAgent)+".txt"
    f1Name = "ResultatEval"+str(nbAgent+1)+".txt"
    agent = ['R','B','C','H']
    comb=[]
    for r in range(nbAgent+1):
        print("r")
        for b in range(nbAgent+1-r):
            for h in range(nbAgent+1-r-b):
                c = nbAgent-r-b-h
                comb.append( [r,b,c,h])
    print("Read")
    dic = getTabFile(fName)
    dic1 = getTabFile(f1Name)
    print("End READ")
    for ag in range(len(agent)):
        print(agent[ag])
        somme = 0
        for co in comb:
            toFind6 = str(co[0])+"/"+str(co[1])+"/"+str(co[2])+"/"+str(co[3])
            #cn = findValueInFile(fName,toFind6)
            cn = int(dic[toFind6])
            toFind7 = str(co[0]+int(ag==0))+"/"+str(co[1]+int(ag==1))+"/"+str(co[2]+int(ag==2))+"/"+str(co[3]+int(ag==3))
            #cn1 = findValueInFile(f1Name,toFind7)
            cn1 = int(dic1[toFind7])
            somme+=(cn1-cn)
        somme = somme/math.factorial(len(agent))
        print("contribMarg de "+str(agent[ag])+" : " +str(somme))

def getTabFile(f):
    fp = open(f,'r')
    line = fp.readline()
    d = dict()
    while line:
        if not('R' in line):
            comb,val = line.split(" ") 
            d[comb]=val
        line = fp.readline()
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