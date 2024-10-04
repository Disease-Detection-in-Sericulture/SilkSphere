from flask import render_template, request, redirect, url_for
from app import app
import numpy as np
import cv2
from keras.models import load_model
import os
from Retriever import Retriever

model = load_model('model.h5')

@app.route('/', methods=['GET', 'POST'])
def index():
    retriever = Retriever()
    retriever.retrieve()

    result = None 

    if request.method == 'POST':
        if 'file' not in request.files:
            return redirect(request.url)
        
        file = request.files['file']

        if file.filename == '':
            return redirect(request.url)
        
        file_path = os.path.join(app.config['UPLOAD_FOLDER'], file.filename)
        file.save(file_path)

        test_img = cv2.imread(file_path)
        test_img = cv2.resize(test_img, (256, 256))
        test_input = test_img.reshape((1, 256, 256, 3)) / 255.0

        prediction = model.predict(test_input)
        predicted_class = (prediction > 0.5).astype(int)[0][0]

        result = "Healthy" if predicted_class == 1 else "Diseased"

    return render_template("index.html", retriever=retriever, result=result)
