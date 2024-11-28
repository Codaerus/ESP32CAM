import cv2
import numpy as np 

m1 = np.array([
			[60,80,100,120],
			[70,20,200,150],
			[24,90,100,140],
			[120,2,120,255]
		], dtype = np.uint8)

mask = cv2.inRange(m1,100,200)
AND = cv2.bitwise_and(m1,mask)
print(m1)
print(mask)
print(AND)
#help(cv2.inRange)
#inRange(src, lowerb, upperb[, dst]) -> dst
