############################################
# Dog Detection Project
# Author : Anil Kumar S   (Jan 19, 2020)
# Phone: 8891869515
############################################
# pip install tensorflow==1.14

import cv2,os
import argparse
import numpy as np
cascade_src = 'xml/haarcascade_frontalcatface_extended.xml'
img_folder="vehicle_images"

global counter  # Counter for counting no of vehicle in the image
car_cascade = cv2.CascadeClassifier(cascade_src)
image_data=os.listdir(img_folder)
for ab in image_data:
    counter=0
    yolo_image=img_folder+"\\"+ab
    img = cv2.imread(yolo_image)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    cars = car_cascade.detectMultiScale(gray, 1.1, 1)
    counter=len(cars)
    for (x,y,w,h) in cars:
        cv2.rectangle(img,(x,y),(x+w,y+h),(0,0,255),2)
    cv2.putText(img,str(counter),(100,100),cv2.FONT_HERSHEY_COMPLEX,3,(255,0,0),3) # Print the vehicle's count in the image
    print("Total no of vehicle identified: {}".format(counter))
    cv2.imshow("object detection", img)
    cv2.waitKey()
    cv2.imwrite("identified_images\\{}".format(ab), img)
    cv2.destroyAllWindows()
