import cv2
import numpy as np
image_as_BGR = cv2.imread("mario.png")
image_as_GRAY = cv2.cvtColor(image_as_BGR, cv2.COLOR_BGR2GRAY)

template_as_BGR = cv2.imread("blo.png")
template_as_GRAY = cv2.cvtColor(template_as_BGR, cv2.COLOR_BGR2GRAY)
w,h = template_as_GRAY.shape
result = cv2.matchTemplate(image_as_GRAY,template_as_GRAY,cv2.TM_CCOEFF_NORMED)

valor_umbral = 0.97
#r = np.array([10,20,30,40,50], np.uint8)
location = np.where(result>=valor_umbral)
location = location[::-1]

for point in zip(*location):
	print(point)
	cv2.rectangle(image_as_BGR,point,(point[0]+w, point[1]+h),(0,255,0),2)
#help(cv2.rectangle)
#print(cv2.minMaxLoc(result))
#print(result)
cv2.imshow("imagen",image_as_BGR)
cv2.waitKey(0)
#cv2.rectangle(img, pt1, pt2, color[, thickness[, lineType[, shift]]]) -> img
