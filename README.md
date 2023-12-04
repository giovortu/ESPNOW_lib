# Linux-ESPNOW 

Based on https://github.com/thomasfla/Linux-ESPNOW

## Improvements

- Improved Linux application
- Added threading to avoid high CPU

## Before using this code
Do not forget to turn on monitor mode and choose the right channel on your wireless interface card.

Here is a example on how to do it :
```
sudo ifconfig wlp2s0 down
sudo iwconfig wlp2s0 mode monitor
sudo ifconfig wlp2s0 up
sudo iwconfig wlp2s0 channel 1
```

Otherwise you can use the provided launcher

```
sudo ./launch.sh wlps20
```

Replace `wlp2s0` with your actual WiFi interface.

The application assumes full that text messages are received and print them to standard output.

