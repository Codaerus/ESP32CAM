import cv2
import numpy as np 

img = cv2.imread("images.png",1)

#b,g,r = cv2.split(img)

b = img[ : , : , 0 ]
g = img[ : , : , 0 ]
r = img[ : , : , 0 ]

cv2.imshow("ventana",img)
cv2.imshow("rojo",r)
cv2.imshow("azul",b)
cv2.imshow("verde",g)
cv2.waitKey()
