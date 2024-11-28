import numpy as np
import cv2

m1 = np.array([
			[255,255],
			[128,0]
		])

m2 = np.array([
			[255,128],
			[128,0]
		])


AND = cv2.bitwise_and(m1, m2)
print(AND)

#help(cv2.bitwise_and)
#bitwise_and(src1, src2[, dst[, mask]]) -> dst
