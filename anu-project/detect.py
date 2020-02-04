import keras
keras.models.load_model(filepath)
model = load_model('my_model.h5')
model.evaluate(x,y)
