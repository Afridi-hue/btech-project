# https://stackoverflow.com/questions/50151585/how-to-use-a-saved-model-in-keras-to-predict-and-classify-an-image
from keras.models import load_model
model = load_model('saved_model.h5')
model.evaluate()\


"""
from keras.preprocessing import image

test_image= image.load_img(picturePath, target_size = (img_width, img_height)) 
test_image = image.img_to_array(test_image)
test_image = numpy.expand_dims(test_image, axis = 0)
test_image = test_image.reshape(img_width, img_height)
result = model.predict(test_image)   
"""
