import cv2
url = "http://192.168.1.10/640x480.jpg"
cap = cv2.VideoCapture(0)
azul_bajo =(100,50,40) # H S V
azul_alto =(120,255,255) # H S V
#help(cv2.absdiff)
umbral = 10000
movimiento_umbral = 2000
mask_anterior = None
while(1):
	#cap.open(url)#Abrimos la url
	ret,frame = cap.read()#Captura los frames
	if ret != True:
		break
	frame_HSV = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
	mask = cv2.inRange(frame_HSV,azul_bajo,azul_alto) # Valor binario que analiza entre el rango 100 y 200, si esta esta en el rango es 255 , sino es 0
	AND = cv2.bitwise_and(frame,frame,mask = mask) # Se aplica AND entre la image original en 3D y el rango de azul, para sacar el azul
	cantidad_blancos = cv2.countNonZero(mask)

	#print(cantidad_blancos)
	if(cantidad_blancos>umbral):
		#print("Objeto detectado")
		if mask_anterior is not None:
			#Calculo de la diferencia
			diferencia = cv2.absdiff(mask,mask_anterior)
			#print(diferencia)
			movimiento = cv2.countNonZero(diferencia)
			if movimiento > movimiento_umbral:
				print("El objeto se movio")
			else:
				print("El objeto no se movio")
		else:
			print("No hay datos anteriores para determinar el movimiento")
		mask_anterior = mask.copy()
	else:
		print("Objeto no detectado")
	cv2.imshow("ventana esp",frame)
	cv2.imshow("mask",mask)
	cv2.imshow("AND",AND)
	if cv2.waitKey(1) == ord('a'):
		break
cap.release()
cv2.destroyAllWindows()
#cvtColor(src, code[, dst[, dstCn]]) -> dst
#countNonZero(src) -> retval
