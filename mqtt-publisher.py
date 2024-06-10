import time
import paho.mqtt.client as mqtt
import ssl
import sys

# Parameters:
CLOUD_MQTT_URL = "ashp2etl1rpx2-ats.iot.eu-north-1.amazonaws.com"
CERTIFICATE_AUTH_FILE = "AmazonRootCA1.pem"
CERT_PEM_FILE = "e584295e7afb273500441f12c11a76a7e22e4db87d0af50b0a262ab1e506cad6-certificate.pem.crt"
PRIVATE_KEY_FILE = "e584295e7afb273500441f12c11a76a7e22e4db87d0af50b0a262ab1e506cad6-private.pem.key"
MQTT_TOPIC = "\\DEEC\\pub"

#Override MQTT_TOPIC from the cmd line:
if len(sys.argv) > 1:
  MQTT_TOPIC = str(sys.argv[1])


client=mqtt.Client() 

print("Connecting to Cloud MQTT Broker")
client.tls_set(ca_certs=CERTIFICATE_AUTH_FILE, certfile=CERT_PEM_FILE, keyfile=PRIVATE_KEY_FILE, tls_version=ssl.PROTOCOL_TLSv1_2)
client.tls_insecure_set(False)
client.connect(CLOUD_MQTT_URL, 8883, 60)

##start loop to process received messages
#client.loop_start()
pub_count = 0
print("Setup a publisher in topic: \""+MQTT_TOPIC+"\"")

while True:
   try: 
        msg="{\n\"message\": \"Hello from our Python script " + str(pub_count) + "\"\n}"
        print("publishing: " + msg)
  	client.publish(MQTT_TOPIC,msg)
	pub_count+=1
	#wait to allow publishing continuously
	time.sleep(2)
   except (KeyboardInterrupt):
        sys.exit()


