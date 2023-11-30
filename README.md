# Linux-ESPNOW 

Based on https://github.com/thomasfla/Linux-ESPNOW

## Improvements

- Improved Linux application
- Added threading to avoid high CPU

## Before using this code
Do not forget to turn on monitor mode and choose the right channel on your wireless interface card.

Here is a exmaple on how to do it :
```
sudo ifconfig wlps20 down
sudo iwconfig wlps20 mode monitor
sudo ifconfig wlps20 up
sudo iwconfig wlps20 channel 1
```

Otherwise you can use the provided launcher

```
sudo ./launch.sh wlps20
```

Replace `wlps20` with your actual WiFi interface.

The application assumes full that text messages are received and print them to standard output.

