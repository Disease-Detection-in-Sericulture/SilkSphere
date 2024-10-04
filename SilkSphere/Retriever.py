from dotenv import load_dotenv
import os
import requests

load_dotenv()

class Retriever:
    def __init__(self) -> None:
        self.temperature = None
        self.humidity = None
        self.co2 = None

    def retrieve(self):
        channel_id = os.getenv('CHANNEL_ID')
        api_key = os.getenv('API_KEY')
        url = f"https://api.thingspeak.com/channels/{channel_id}/feeds/last.json?api_key={api_key}"
        response = requests.get(url)

        data = response.json()
        
        self.temperature = data.get('field1')
        self.humidity = data.get('field2')
        self.co2 = data.get('field3')

#         print(data)

# test = Retriever()

# test.retrieve()

# print(test.temperature, test.humidity, test.co2)