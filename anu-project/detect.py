from keras.models import load_model

import numpy as np
model = keras.model.load_weights('model_saved.h5')
##classifier.compile(loss='your_loss', optimizer='your_optimizer', metrics=['your_metrics'])
from keras.preprocessing import image
test_image= image.load_img("normal/a.jpg", target_size = (150,150)) 
test_image = image.img_to_array(test_image)
test_image = np.expand_dims(test_image, axis = 0)
# test_image = test_image.reshape(img_width, img_height)
result = model.predict(test_image)
print(result)

### https://stackoverflow.com/questions/50151585/how-to-use-a-saved-model-in-keras-to-predict-and-classify-an-image
##from keras.models import load_model
##import cv2
##model = load_model('model_saved.h5')
##test_image=cv2.imread("normal/a.jpg")
##result = model.predict(test_image) 
##print(result)


"""
from keras.preprocessing import image

test_image= image.load_img(picturePath, target_size = (img_width, img_height)) 
test_image = image.img_to_array(test_image)
test_image = numpy.expand_dims(test_image, axis = 0)
test_image = test_image.reshape(img_width, img_height)
result = model.predict(test_image)   
"""


"""
img_width, img_height = 313, 220

# load the model we saved
model = load_model('model_saved.h5')
sgd = optimizers.SGD(lr=0.01, decay=1e-6, momentum=0.9, nesterov=True)
model.compile(loss='categorical_crossentropy', optimizer=sgd, metrics=['accuracy','mse'])

test_image= image.load_img('/Images/1.jpg',target_size = (img_width, img_height))
test_image = image.img_to_array(test_image)
test_image = np.expand_dims(test_image, axis = 0)
result = model.predict(test_image)
"""
