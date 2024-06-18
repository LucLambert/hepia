from network import WLAN
import machine
wlan = WLAN(mode=WLAN.STA)

nets = wlan.scan()
for net in nets:
    if net.ssid == 'Airbender': #à modifier pour l'id du wifi
        print('Network found!')
        wlan.connect(net.ssid, auth=(net.sec, 'awkt6871'), timeout=5000) # à modifier pour le mot de passe du wifi
        while not wlan.isconnected():
            machine.idle() # save power while waiting
        print('WLAN connection succeeded!')
        #print(wlan.ifconfig())
        break