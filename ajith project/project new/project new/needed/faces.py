import numpy as np
import cv2
import pickle

# for face detection
# face_cascade = cv2.CascadeClassifier('fdface.xml')


recognizer = cv2.face.LBPHFaceRecognizer_create()
recognizer.read("../trainner.yml")

labels = {"person_name": 1}
with open("../labels.pickle", 'rb') as f:
	og_labels = pickle.load(f)
	labels = {v:k for k,v in og_labels.items()}


frame=cv2.imread("sample.jpg")
gray  = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
height_1, width_1, channels = frame.shape
roi_gray = gray[0:height_1, 0:width_1] #(ycord_start, ycord_end)
roi_color = frame[0:height_1, 0:width_1]


# recognize? deep learned model predict keras tensorflow pytorch scikit learn
id_, conf = recognizer.predict(roi_gray)
print(conf,labels[id_])
if conf>=4 and conf <= 85:
    
    #print(5: #id_)
    #print(labels[id_])
    font = cv2.FONT_HERSHEY_SIMPLEX
    name = labels[id_]
    print(name)
    color = (255, 255, 255)
    stroke = 2
    #cv2.putText(frame, name, (x,y), font, 1, color, stroke, cv2.LINE_AA)

    img_item = "7.png"
    cv2.imwrite(img_item, roi_color)

##    color = (255,255, 0)
##    stroke = 2
##    end_cord_x = x+w+40
##    end_cord_y = y+h+40
##    cv2.rectangle(frame, (x-40, y-40), (end_cord_x, end_cord_y), color, stroke)
    #subitems = smile_cascade.detectMultiScale(roi_gray)
    #for (ex,ey,ew,eh) in subitems:
    #	cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2)
# Display the resulting frame
cv2.imshow('frame',frame)
if cv2.waitKey(0):
    cv2.destroyAllWindows()

