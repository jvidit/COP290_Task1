import cv2
import numpy
import sys
img = cv2.imread(sys.argv[1],0)
#image_address = '/home/ashish/Desktop/COP/Task1.3/1.png'
if img.shape != [28,28]:
    img2 = cv2.resize(img,(28,28))
    img = img2.reshape(28,28,-1);
else:
    img = img.reshape(28,28,-1);
#revert the image,and normalize it to 0-1 range
img2=numpy.array(img)

img2 = 1.0 - img2/255.0
#print (img2)
numpy.savetxt('image_28.txt', img2[:,:,0],fmt="%f",delimiter='\n')




