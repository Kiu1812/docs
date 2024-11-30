# Host Discovery

---

The host discovery in a local network is a crucial task in network management and pentesting. There are many tools and techniques used to accomplish this task, they go from port scanning to network traffic analysis.

The tools we will be using are [nmap](#nmap), [arp-scan](#arp-scan), [netdiscover](#netdiscover), [masscan](#masscan)

## Scanning through Ports

### NMap

We can use the `-sn` type of scan to do a Ping Scan and disable the Port Scan part of NMap. An example of it is:

```bash
nmap -sn 10.0.0.0/24
```


### Masscan

To use `masscan` we have to specify the port list to use with the parameter `-p<port-numbers>`, we separate the different port numbers with a comma. We can also add `-Pn` to not send a ping to the hosts and only search the ports and `--rate=5000` to increase the amount of packets per second that are sent. An example execution is:

```bash
masscan -p21,22,139,445 -Pn 10.0.0.0/24 --rate=5000
```

## Scanning through ARP

### Arp-Scan

To scan through ARP we can use the `arp-scan` command, we just have to specify the interface where it will scan with the parameter `-i <interface>`:

```bash
arp-scan -I <network-interface> --localnet
```


### NetDiscover

Another way to scan through ARP is the tool `netdiscover`, we have to specify the network interface with `-i <interface>`:

```bash
netdiscover -i <network-interface>
```


## Manual ICMP Scanning

We can also make a script that executes a ping for all the machines in a certain range with an script like the following:

```bash
#!/bin/bash

function ctrl_C(){
  echo -e "\n\n[!] Aborting...\n"
  tput cnorm; exit 1
}

# Ctrl + C
trap ctrl_c SIGINT
tput civis

for i in $(seq 1 254); do
  timeout 1 bash -c "ping -c 1 10.0.0.$i" &>/dev/null && echo "[+] Host 10.0.0.$i - ACTIVE" &
done

wait
tput cnorm
```







