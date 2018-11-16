from tkinter import *
from math import *
from constant import *
from time import *

def calcPtsOld():
   xGap = xMax - edgeLen
   theta = pi / 3
   dx = cos(theta) * edgeLen 
   dy = sin(theta) * edgeLen
   yGap = yMax - edgeLen   
   A = (xGap, yMax - yGap)
   B = (xMax / 2, yGap)
   C = (xMax - xGap, yMax - yGap)
   return [A, B, C]

def calcPts():
   xMid = xMax / 2
   yMid = yMax / 2
   theta = 1.047
   xOff = cos(theta) * edgeLen + edgeLen / 2
   yOff = sin(theta) * edgeLen
   A = (xMid - edgeLen / 2, yMid - yOff)
   B = (xMid + edgeLen / 2, yMid - yOff)
   C = (xMid + xOff, yMid)
   D = (xMid + edgeLen / 2, yMid + yOff)
   E = (xMid - edgeLen / 2, yMid + yOff)
   F = (xMid - xOff, yMid)
   return [A, B, C, D, E, F]

def dist(ptA, ptB):
   return sqrt((ptA[X] - ptB[X]) ** 2 + (ptA[Y] - ptB[Y]) ** 2) 

def calcArea(ptA, ptB, ptC):
   A = dist(ptA, ptB)
   B = dist(ptB, ptC)
   C = dist(ptC, ptA)
   P = (A + B + C) / 2
   try:
      return sqrt(P * (P - A) * (P - B) * (P - C)) 
   except:
      return 0

def calcDist(pt):
   x = pt[X]
   y = pt[Y]
   xMid = xMax / 2
   yMid = yMax / 2
   A = (0, 0)
   B = (xMax, 0)
   C = (xMax, yMax)
   D = (0, yMax)
   corner = (0, 0)
   
   if (x < xMid):
      if (y < yMid):
         corner = A
      else:
         corner = D
   else:
      if (y < yMid):
         corner = B
      else:
         corner = C

   return dist(pt, corner) - dist(pt, (xMid, yMid))

def calcMin(ptA, ptB, ptC, dx, dy):
   best = (ptC[X], ptC[Y])
   sign = [(-1, -1), (-1, +1), (+1, -1), (+1, +1)]  
   for elem in sign:
      x = ptC[X] + (elem[X] * dx)
      y = ptC[Y] + (elem[Y] * dy)
      bestVal = calcArea(ptA, ptB, best) - dist(best, (xMax / 2, yMax / 2))
      cur = (x, y)
      curVal = calcArea(ptA, ptB, cur) - dist(cur, (xMax / 2, yMax / 2))
      if (curVal >= bestVal):
         if (abs(dist(ptC, cur)) >= 0.1):
            best = cur
   return best

def calcMax(ptA, ptB, ptC, dx, dy):
   best = (ptC[X], ptC[Y])
   sign = [(-1, -1), (-1, +1), (+1, -1), (+1, +1)]  
   for elem in sign:
      x = ptC[X] + (elem[X] * dx)
      y = ptC[Y] + (elem[Y] * dy)
      bestVal = calcArea(ptA, ptB, best) - calcDist(best)
      cur = (x, y)
      curVal = calcArea(ptA, ptB, cur) - calcDist(cur)
      if (curVal >= bestVal):
         if (abs(dist(ptC, cur)) >= 0.1):
            best = cur
   return best

def draw(ptA, ptB, win, deg, theta):
   if (deg == 0):
      win.create_line(ptA[X], ptA[Y], ptB[X], ptB[Y])
   else:
      if (deg == 1):
         win.create_line(ptA[X], ptA[Y], ptB[X], ptB[Y], fill="green")
      if (deg == 2):
         win.create_line(ptA[X], ptA[Y], ptB[X], ptB[Y], fill="purple")
      if (deg == 3):
         win.create_line(ptA[X], ptA[Y], ptB[X], ptB[Y], fill="red")

      midX = abs(ptA[X] - ptB[X]) / 2 + min(ptA[X], ptB[X])
      midY = abs(ptA[Y] - ptB[Y]) / 2 + min(ptA[Y], ptB[Y])
      midLen = sqrt((midX - ptA[X]) ** 2 + (midY - ptA[Y]) ** 2)
      hyp = tan(theta) * midLen
      midDy = abs(midY - ptA[Y]) 
      phi = pi / 2 - asin(midDy / midLen)
      dx = cos(phi) * hyp
      dy = sin(phi) * hyp
      finalX, finalY = calcMax(ptA, ptB, (midX, midY), dx, dy)
      ptC = (finalX, finalY)
      draw(ptA, ptC, win, deg - 1, theta - inc)
      draw(ptC, ptB, win, deg - 1, theta - inc)
   
def drawF(ptA, ptB, win, deg, theta):
   if (deg == 0):
      win.create_line(ptA[X], ptA[Y], ptB[X], ptB[Y], fill="green")
   else:
      if (deg == 0):
         win.create_line(ptA[X], ptA[Y], ptB[X], ptB[Y], fill="green")
      if (deg == 1):
         win.create_line(ptA[X], ptA[Y], ptB[X], ptB[Y], fill="purple")
      if (deg == 2):
         win.create_line(ptA[X], ptA[Y], ptB[X], ptB[Y], fill="red")

      midX = abs(ptA[X] - ptB[X]) / 2 + min(ptA[X], ptB[X])
      midY = abs(ptA[Y] - ptB[Y]) / 2 + min(ptA[Y], ptB[Y])
      midLen = sqrt((midX - ptA[X]) ** 2 + (midY - ptA[Y]) ** 2)
      hyp = tan(theta) * midLen
      midDy = abs(midY - ptA[Y]) 
      phi = pi / 2 - asin(midDy / midLen)
      dx = cos(phi) * hyp
      dy = sin(phi) * hyp
      finalX, finalY = calcMin(ptA, ptB, (midX, midY), dx, dy)
      ptC = (finalX, finalY)
      drawF(ptA, ptC, win, deg - 1, theta - inc)
      drawF(ptC, ptB, win, deg - 1, theta - inc)

def drawR(ptA, ptB, win, deg, theta):
   if (deg == 0):
      win.create_line(ptA[X], ptA[Y], ptB[X], ptB[Y], fill="green")
      drawF(ptA, ptB, win, 1, theta)
   else:
      if (deg == 0):
         win.create_line(ptA[X], ptA[Y], ptB[X], ptB[Y], fill="green")
      if (deg == 1):
         win.create_line(ptA[X], ptA[Y], ptB[X], ptB[Y], fill="purple")
      if (deg == 2):
         win.create_line(ptA[X], ptA[Y], ptB[X], ptB[Y], fill="red")

      midX = abs(ptA[X] - ptB[X]) / 2 + min(ptA[X], ptB[X])
      midY = abs(ptA[Y] - ptB[Y]) / 2 + min(ptA[Y], ptB[Y])
      midLen = sqrt((midX - ptA[X]) ** 2 + (midY - ptA[Y]) ** 2)
      hyp = tan(theta) * midLen
      midDy = abs(midY - ptA[Y]) 
      phi = pi / 2 - asin(midDy / midLen)
      dx = cos(phi) * hyp
      dy = sin(phi) * hyp
      finalX, finalY = calcMin(ptA, ptB, (midX, midY), dx, dy)
      ptC = (finalX, finalY)
      drawR(ptA, ptC, win, deg - 1, theta - inc)
      drawR(ptC, ptB, win, deg - 1, theta - inc)

count = 66

def drawNext():
   global theta
   global edgeLen
   global count
   win.delete("all")
   pts = calcPts()
   n = len(pts)
   for idx in range(n):
      ptA = pts[idx]
      ptB = pts[(idx + 1) % n]
      win.create_line(ptA[X], ptA[Y], ptB[X], ptB[Y], fill="red")
      draw(ptA, ptB, win, deg, theta) 
      drawR(ptA, ptB, win, deg - 1, theta) 
 
   theta += 0.01
   edgeLen -= 1
   count -= 1
   win.update()
   sleep(0.1)
   if (count > 0):
      drawNext()
   else:
      mainloop()

root = Tk()
win = Canvas(root, width=xMax, height=yMax, bg="white")
win.pack()

drawNext()    
