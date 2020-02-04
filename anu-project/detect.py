# https://stackoverflow.com/questions/50151585/how-to-use-a-saved-model-in-keras-to-predict-and-classify-an-image
from keras.models import load_model
model = load_model('saved_model.h5')
model.evaluate()
