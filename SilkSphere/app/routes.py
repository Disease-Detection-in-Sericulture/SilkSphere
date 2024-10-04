from flask import render_template
from app import app
from Retriever import Retriever

@app.route('/')
def index():
    retriever = Retriever()
    retriever.retrieve()

    return render_template("index.html", retriever=retriever)