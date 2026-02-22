# Connect to board

```
sudo apt install picocom
sudo picocom -b 1500000 /dev/ttyUSB0

No password at first start

```

# See list of interfaces

```
ifconfig

# No wifi at first start

br-lan    Link encap:Ethernet  HWaddr 1A:3C:9D:A1:97:E6  
          inet addr:192.168.1.1  Bcast:192.168.1.255  Mask:255.255.255.0  # << Address of bridge
          inet6 addr: fd02:b94:dc8d::1/60 Scope:Global
          UP BROADCAST MULTICAST  MTU:1500  Metric:1
          RX packets:0 errors:0 dropped:0 overruns:0 frame:0
          TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)

eth0      Link encap:Ethernet  HWaddr 1A:3C:9D:A1:97:E6  
          UP BROADCAST MULTICAST  MTU:1500  Metric:1
          RX packets:0 errors:0 dropped:0 overruns:0 frame:0
          TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)
          Interrupt:42 

eth1      Link encap:Ethernet  HWaddr 1A:3C:9D:A1:97:E7  
          UP BROADCAST MULTICAST  MTU:1500  Metric:1
          RX packets:0 errors:0 dropped:0 overruns:0 frame:0
          TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)
          Interrupt:44 

lo        Link encap:Local Loopback  
          inet addr:127.0.0.1  Mask:255.0.0.0
          inet6 addr: ::1/128 Scope:Host
          UP LOOPBACK RUNNING  MTU:65536  Metric:1
          RX packets:104 errors:0 dropped:0 overruns:0 frame:0
          TX packets:104 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:8112 (7.9 KiB)  TX bytes:8112 (7.9 KiB)


```

# Connect RJ45 to board Inner ethernet port (eth0/WAN)

```
[  127.612378] rk_gmac-dwmac fe010000.ethernet eth0: Link is Up - 1Gbps/Full - flow control rx/tx
[  127.612469] br-lan: port 1(eth0) entered blocking state
[  127.613667] br-lan: port 1(eth0) entered forwarding state

```

# Connect to LuCi

```
In browser

http://192.168.1.1/

```

# `iperf3` test `eth0` - it's WAN

```
On board

# server mode
iperf3 -s

# on host
sudo apt install iperf3

iperf3 -c 192.168.1.1 -R
```