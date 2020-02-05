import os
import cv2
from PIL import Image
import numpy as np
import pickle
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
image_dir = os.path.join(BASE_DIR, "images")
#face_cascade = cv2.CascadeClassifier('fdface.xml')
recognizer = cv2.face.LBPHFaceRecognizer_create()


current_id=0
label_ids={}
y_labels=[]
x_train=[]

for root, dirs, files in os.walk(image_dir):
	for file in files:
		if file.endswith("png") or file.endswith("jpg"):
			path = os.path.join(root, file)
			label=os.path.basename(os.path.dirname(path)).replace(" ","-").lower()
			if not label in label_ids:
				label_ids[label]=current_id
				current_id+=1
			id_=label_ids[label]
			#print(label_ids)
			#print(label,path)
			pil_image=Image.open(path).convert("L") # convert into gray
			'''size = (500, 500)
			final_image = pil_image.resize(size, Image.ANTIALIAS)'''
			image_array = np.array(pil_image, "uint8")
			height_1,width_1=pil_image.size

			#print(image_array)
##			faces = face_cascade.detectMultiScale(
##			image_array,
##			scaleFactor=1.3,
##			minNeighbors=5,
##			minSize=(30, 30),
##			flags=cv2.CASCADE_SCALE_IMAGE
##			)
			#for (x, y, w, h) in faces:
			roi=image_array[0:width_1,0:height_1]
			#roi=image_array[y-40:y+h+40,x-40:x+w+40]
			x_train.append(roi)
			y_labels.append(id_)
with open("labels.pickle","wb") as f:
	pickle.dump(label_ids,f)
recognizer.train(x_train, np.array(y_labels))
recognizer.save("trainner.yml")


