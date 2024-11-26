import cv2
url = "http://192.168.1.10/640x480.jpg"
cap = cv2.VideoCapture(url)

while(1):
	cap.open(url)#Abrimos la url
	ret,frame = cap.read()#Captura los frames
	cv2.imshow("ventana esp",frame)
	if cv2.waitKey(1) == ord('a'):
		break

cap.release()
cv2.destroyAllWindows()
