import os
from flask import Flask

app = Flask(__name__)

app.config['UPLOAD_FOLDER'] = 'app/static/uploads'
app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024

from app import routes