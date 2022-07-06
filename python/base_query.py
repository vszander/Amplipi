import json
import secrets
import requests
import time

host = "amplipi.local"


def main():
    url = "http://" + secrets.host + "/api/zones/"
    query = requests.get(url, verify=False, headers=secrets.headers)
    if query.status_code != 200:
        print("failed call")
    else:
        searchreturn = query.json()
        zones = searchreturn['zones']
        for zone in zones:
            print(zone['name'] + "  vol:"+ str(zone['vol']) + "  disabled:" + str(zone['disabled']))
        print(zones)

def change_volume(zone,volume):
    url = "http://" + secrets.host + "/api/zones/" + str(zone)
    data_set = {
                'vol': volume
               }
    thechange = requests.patch(url, verify=False, headers=secrets.headers, data=json.dumps(data_set))


    if thechange.status_code != 200:
        print("failed call")
        print(thechange.content)
    else:
        print("volume changed")

def change_source(zone,source_id):
    url = "http://" + secrets.host + "/api/zones"
    data_set = {
                 "zones": [
                    zone
                  ],
                  "update": {
                    "source_id": source_id
                  }
                }
    thechange = requests.patch(url, verify=False, headers=secrets.headers, data=json.dumps(data_set))


    if thechange.status_code != 200:
        print("failed call")
        print(thechange.content)
    else:
        print("source changed")

def change_stream(source_id,stream_id):
    url = "http://" + secrets.host + "/api/sources/" + str(source_id)
    data_set = {
                 "input": "stream=" + str(stream_id)
                }
    thechange = requests.patch(url, verify=False, headers=secrets.headers, data=json.dumps(data_set))


    if thechange.status_code != 200:
        print("failed call")
        print(thechange.content)
    else:
        print("stream changed")


def announce():
    url = "http://" + secrets.host + "/api/announce"
    data_set = {
                   "media": "file:///home/pi/Music/beds/BackInTimeRingtone.mp3",
                     "source_id": 0
                }
    print("announcing ...")
    print(json.dumps(data_set))
    thechange = requests.post(url, verify=False, headers=secrets.headers, data=json.dumps(data_set))


    if thechange.status_code != 200:
        print("failed call")
        print(thechange.content)
    else:
        print("announced")
        print(thechange.content)


change_volume(0,-30)
change_stream(0,1000)
change_source(0,0)
time.sleep(5)
announce()
change_source(0,3)




