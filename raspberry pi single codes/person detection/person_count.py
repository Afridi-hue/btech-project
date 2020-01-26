############################################
# Dog Detection Project
# Author : Anil Kumar S   (Jan 19, 2020)
# Phone: 8891869515
############################################
# pip install tensorflow==1.14

import cv2,os,time
import argparse
import numpy as np


yolo_class="../yolo_v3/yolov3.txt"
yolo_weights="../yolo_v3/YOLOv3-320.weights"
yolo_config="../yolo_v3/YOLOv3-320.cfg"
img_folder="person_images"

global counter  # Counter for counting no of person in the image



# Adding the argument to get the camera number
"""
ap = argparse.ArgumentParser()
ap.add_argument('-c', '--camera', required=True,help = 'add the name of the camera')
args = ap.parse_args()
"""

def get_output_layers(net):

    layer_names = net.getLayerNames()

    output_layers = [layer_names[i[0] - 1] for i in net.getUnconnectedOutLayers()]

    return output_layers


def draw_prediction(img, class_id, confidence, x, y, x_plus_w, y_plus_h):

    label = str(classes[class_id])

    color = COLORS[class_id]

    cv2.rectangle(img, (x,y), (x_plus_w,y_plus_h), color, 2)

    cv2.putText(img, label, (x-10,y-10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color, 2)

image_data=os.listdir(img_folder)

for ab in image_data:
    counter=0
    yolo_image=img_folder+"\\"+ab
    image = cv2.imread(yolo_image)
    Width = image.shape[1]
    Height = image.shape[0]
    scale = 0.00392

    classes = None

    with open(yolo_class, 'r') as f:
        classes = [line.strip() for line in f.readlines()]

    COLORS = np.random.uniform(0, 255, size=(len(classes), 3))

    net = cv2.dnn.readNet(yolo_weights, yolo_config)

    blob = cv2.dnn.blobFromImage(image, scale, (416,416), (0,0,0), True, crop=False)

    net.setInput(blob)

    outs = net.forward(get_output_layers(net))

    class_ids = []
    confidences = []
    boxes = []
    conf_threshold = 0.5
    nms_threshold = 0.4


    for out in outs:
        for detection in out:
            scores = detection[5:]
            class_id = np.argmax(scores)
            confidence = scores[class_id]
            if confidence > 0.5:
                center_x = int(detection[0] * Width)
                center_y = int(detection[1] * Height)
                w = int(detection[2] * Width)
                h = int(detection[3] * Height)
                x = center_x - w / 2
                y = center_y - h / 2
                class_ids.append(class_id)
                confidences.append(float(confidence))
                boxes.append([x, y, w, h])


    indices = cv2.dnn.NMSBoxes(boxes, confidences, conf_threshold, nms_threshold)

    for i in indices:
        i = i[0]
        box = boxes[i]
        x = box[0]
        y = box[1]
        w = box[2]
        h = box[3]
        print(class_ids[i])
        # id of person is 0
        if class_ids[i]==0:
            # print("person found")
            counter+=1
            draw_prediction(image, class_ids[i], confidences[i], round(x), round(y), round(x+w), round(y+h))

    cv2.putText(image,str(counter),(100,100),cv2.FONT_HERSHEY_COMPLEX,3,(255,0,0),3) # Print the people's count in the image
    print("Total no of person identified: {}".format(counter))
    cv2.namedWindow('object detection',cv2.WINDOW_NORMAL)
    cv2.resizeWindow('object detection', 1200, 600)
    cv2.imshow("object detection", image)
    cv2.waitKey()
    # time.sleep(0)
    cv2.imwrite("identified_images\\{}".format(ab), image)
    cv2.destroyAllWindows()
