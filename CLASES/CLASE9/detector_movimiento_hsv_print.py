import cv2
url = "http://192.168.1.10/640x480.jpg"
cap = cv2.VideoCapture(0)
azul_bajo =(100,50,40) # H S V
azul_alto =(120,255,255) # H S V
#help(cv2.countNonZero)
umbral = 10000
while(1):
	#cap.open(url)#Abrimos la url
	ret,frame = cap.read()#Captura los frames
	frame_HSV = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)

	if ret == True:
		mask = cv2.inRange(frame_HSV,azul_bajo,azul_alto) # Valor binario que analiza entre el rango 100 y 200, si esta esta en el rango es 255 , sino es 0
		AND = cv2.bitwise_and(frame,frame,mask = mask) # Se aplica AND entre la image original en 3D y el rango de azul, para sacar el azul
		cantidad_blancos = cv2.countNonZero(mask)
		#print(cantidad_blancos)
		if(cantidad_blancos>umbral):
			print("Objeto detectado")
		else:
			print("Objeto no detectado")
		cv2.imshow("ventana esp",frame)
		cv2.imshow("mask",mask)
		cv2.imshow("AND",AND)
		if cv2.waitKey(1) == ord('a'):
			break
	else:
		break
cap.release()
cv2.destroyAllWindows()
#cvtColor(src, code[, dst[, dstCn]]) -> dst
#countNonZero(src) -> retval
