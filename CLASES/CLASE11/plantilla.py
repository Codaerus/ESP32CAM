import cv2

image_as_BGR = cv2.imread("image.png")
image_as_GRAY = cv2.cvtColor(image_as_BGR, cv2.COLOR_BGR2GRAY)

template_as_BGR = cv2.imread("plantilla.png")
template_as_GRAY = cv2.cvtColor(template_as_BGR, cv2.COLOR_BGR2GRAY)
w,h = template_as_GRAY.shape
result = cv2.matchTemplate(image_as_GRAY,template_as_GRAY,cv2.TM_SQDIFF)
min_value, max_value, min_value_cordinate, max_value_cordinate = cv2.minMaxLoc(result)

top_left = min_value_cordinate
botton_right = (top_left[0]+w, top_left[1]+h)
cv2.rectangle(image_as_BGR,top_left,botton_right,(0,255,0),2)
help(cv2.rectangle)
#print(cv2.minMaxLoc(result))
#print(result)
cv2.imshow("imagen",image_as_BGR)
cv2.waitKey(0)
#cv2.rectangle(img, pt1, pt2, color[, thickness[, lineType[, shift]]]) -> img
