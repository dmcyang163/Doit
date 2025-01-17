@echo off
netsh wlan set hostednetwork mode=allow
netsh wlan start hostednetwork
echo 移动热点已开启。