import cv2
import numpy as np 

img = cv2.imread("mario.jpg",1)
#print(img.shape)
z = np.zeros((256,256,3),dtype = np.uint8)
cv2.circle(z,(128,128),80,(255,255,255),-1)
AND = cv2.bitwise_and(img,z)
cv2.imshow("ventana",img)
cv2.imshow("zeros",z)
cv2.imshow("AND",AND)
cv2.waitKey()
