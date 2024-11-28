import cv2
url = "http://192.168.1.10/640x480.jpg"
cap = cv2.VideoCapture("circles.avi")
azul_bajo = (100,0,0)
azul_alto = (255,0,0)
while(1):
	#cap.open(url)#Abrimos la url
	ret,frame = cap.read()#Captura los frames
	mask = cv2.inRange(frame,azul_bajo,azul_alto)
	AND = cv2.bitwise_and(frame,frame,mask = mask)
	cv2.imshow("ventana esp",frame)
	cv2.imshow("mask",mask)
	cv2.imshow("AND",AND)
	if cv2.waitKey(60) == ord('a'):
		break

cap.release()
cv2.destroyAllWindows()
