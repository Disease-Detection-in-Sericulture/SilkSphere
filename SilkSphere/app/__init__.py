import os
from dotenv import load_dotenv
from flask import Flask

load_dotenv()

app = Flask(__name__)

app.config['API_KEY'] = os.getenv('API_KEY')

from app import routes