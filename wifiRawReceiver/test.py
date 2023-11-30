import time
from pywifi import PyWiFi

def handle_message(message):
    if message == "TOGGLE":
        print("Received TOGGLE message. Responding with OK.")
        return "OK"
    else:
        print("Received unknown message:", message)
        return "UNKNOWN"

def esp_now_receiver():
    wifi = PyWiFi()
    iface = wifi.interfaces()[0]  # Assuming only one Wi-Fi interface is available

    iface.scan()
    time.sleep(2)

    print("Listening for ESP-NOW messages...")
    while True:
        scan_results = iface.scan_results()
        for result in scan_results:
            if "ESP_NOW_DEVICE" in result.ssid:
                sender_mac = result.bssid
                message = result.ssid.split(":")[1]  # Assuming message is in the SSID

                response = handle_message(message)

                print(f"Responding to {sender_mac} with: {response}")

                # TODO: Send the response back to the ESP-NOW device (implementation required)

        time.sleep(1)

if __name__ == "__main__":
    esp_now_receiver()



