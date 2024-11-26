import cv2
url = "http://192.168.1.10/640x480.jpg"
cap = cv2.VideoCapture(url)

help(cv2.circle)

while(1):
	cap.open(url)#Abrimos la url
	ret,frame = cap.read()#Captura los frames
	cv2.line(frame,(0,320),(640,320),(0,0,255),4)
	cv2.rectangle(frame,(0,0),(640,480),(0,255,0),8)
	cv2.circle(frame,(320,240),60,(255,0,0),4)
	if ret == True:
		#print(frame.shape, frame.ndim, frame.dtype)
		cv2.imshow("ventana esp",frame)
		if cv2.waitKey(1) == ord('a'):
			break

cap.release()
cv2.destroyAllWindows()
#circle(img, center, radius, color[, thickness[, lineType[, shift]]]) -> img
#line(img, pt1, pt2, color[, thickness[, lineType[, shift]]]) -> img
#rectangle(img, pt1, pt2, color[, thickness[, lineType[, shift]]]) -> img
