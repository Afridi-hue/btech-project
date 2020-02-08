import urllib,cv2,copy
import numpy as np 
import urllib.request as ur
faceCascade = cv2.CascadeClassifier('fdface.xml')
url='http://192.168.43.1:8080/shot.jpg'
global i
i=1
while True:
    imgResp=ur.urlopen(url)
    imgNp=np.array(bytearray(imgResp.read()),dtype=np.uint8)
    img=cv2.imdecode(imgNp,-1)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY) 

    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.3,
        minNeighbors=5,
        minSize=(30, 30),
	flags=cv2.CASCADE_SCALE_IMAGE
    )
    img2=copy.copy(img)
    
    for (x, y, w, h) in faces:
        rect=cv2.rectangle(img, (x-40, y-40), (x+w+40, y+h+40), (255,255, 0), 2)
        croppedimg=img2[y-40:y+h+40,x-40:x+w+40]
        #cv2.imwrite('captured_images/image'+str(i)+'.jpg',croppedimg)
        cv2.imwrite('captured_images/image'+str(i)+'.jpg',img2)
        i+=1

    cv2.namedWindow("output", cv2.WINDOW_NORMAL)
    cv2.resizeWindow("output", 700, 600)   
    cv2.imshow('output', img)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()












