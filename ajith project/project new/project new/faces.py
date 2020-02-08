import urllib,cv2,copy
import numpy as np 
import urllib.request as ur
import pickle
face_cascade = cv2.CascadeClassifier('fdface.xml')
recognizer = cv2.face.LBPHFaceRecognizer_create()
recognizer.read("trainner.yml")
labels={}
with open("labels.pickle","rb") as f:
	og_labels = pickle.load(f)
	labels = {v:k for k,v in og_labels.items()}
url='http://192.168.43.1:8080/shot.jpg'
global i
i=1
while True:
    imgResp=ur.urlopen(url)
    imgNp=np.array(bytearray(imgResp.read()),dtype=np.uint8)
    frame=cv2.imdecode(imgNp,-1)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY) 
    faces = face_cascade.detectMultiScale(
        gray,
        scaleFactor=1.3,
        minNeighbors=5,
        minSize=(30, 30),
	flags=cv2.CASCADE_SCALE_IMAGE
    )
    
    for (x, y, w, h) in faces:
        roi_gray=gray[y:y+h,x:x+w]
        roi_color=frame[y:y+h,x:x+w]

        id_, conf = recognizer.predict(roi_gray)
        if conf>=40 and conf <= 85:
            font = cv2.FONT_HERSHEY_SIMPLEX
            name = labels[id_]
            color = (255, 255, 255)
            stroke = 2
            cv2.putText(frame, name, (x,y), font, 2, color, stroke, cv2.LINE_AA)

        
        color=(0,255,0) # BGR
        stroke=2
        end_cord_x=x+w
        end_cord_y=y+h
        cv2.rectangle(frame,(x, y),(end_cord_x,end_cord_y),color,stroke)

    cv2.namedWindow("frame", cv2.WINDOW_NORMAL)
    cv2.resizeWindow("frame", 500, 500)   
    cv2.imshow('frame',frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()












