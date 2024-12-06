# Port Discovery and Enumeration

---
## Nmap

With Nmap the security professionals can identify hosts connected to a network, services that are running in them and possible vulnerabilities that could be exploited by an attacker.
The tool is capable of detecting a wide range of devices, including routers, web servers, printers, IP Cameras, operating systems and other devices.

### Parameters

The most common parameters in Nmap are:

| **Parameter**       | **Description**                                                                                     |
|----------------------|-----------------------------------------------------------------------------------------------------|
| -p <port-range>      | Only check specified ports, separated by commas or a hyphen to specify a range. Use -p - for all ports. |
| --top-ports <n>      | Scan the specified number of most common ports.                                                    |
| --open               | Show only open ports, hiding the filtered ones.                                                    |
| -n                   | Disable DNS resolution.                                                                            |
| -v                   | Verbose mode. Increase the number of v to raise the verbosity level.                               |
| -T[0-5]              | Set a timing template. Higher values indicate more aggressive scans.                               |
| -sT                  | TCP connect scan. Recommended when TCP SYN scan fails.                                            |
| -sS                  | TCP SYN scan. The most common and stealthiest scan, as it does not complete the connection.         |
| -sU                  | UDP scan, used to scan through UDP instead of TCP.                                                 |
| -sV                  | Detect the version of the services running on the open ports.                                      |
| -sC                  | Run a set of scripts during the scan to assist in reconnaissance.                                  |
| -Pn                  | Prevent Nmap from pinging the remote machine.                                                      |
| -O                   | Enable OS detection.                                                                               |

### Examples of execution

 Scan the first 1000 ports:
```bash
Nmap -p1-1000 10.0.0.1
```

<br>

Scan all ports:
```bash
Nmap -p- 10.0.0.0
```

<br>

Scan the 500 most common ports:
```bash
Nmap --top-ports 500 10.0.0.1
```

<br>

Fast scan to search for opened ports, no DNS resolution and assuming the host is online. This is a common scan if we don't care about them detecting us.
```bash
Nmap -p- -sS -T5 --open -n -Pn 10.0.0.1
```


### Firewall evasion techniques

When doing penetration testings, one of the biggest challenges is to evade the Firewalls. To overcome this challenge Nmap has a wide range of evasion techniques that allow the security professionals to do stealthy scans.

 - **MTU** (`--mtu <value>`): *Maximum Transmission Unit* adjusts the max size of the sent packages.
 - **Data Length** (`--data-length <num>`): Adds random content to the sent packages.
 - **Source Port** (`--source-port <port_number>`): Allows to specify the origin port number.
 - **Decoy** (`-D`): This allows to send fake packets to confuse the detection systems.
 - **Fragmented** (`-f`): Fragments packets.
 - **Spoof-Mac** (`--spoof-mac <fake_mac_address>`): Allows to falsify the MAC address. 
 - **Stealth Scan** (`-sS`): Allows to do a SYN scan that doesn't completes the connections to the machines.
 - **Minimum Rate** (`--min-rate <num>`): Send this minimum amount of packets per second.

It's important to say that there are more techniques than the mentioned above.
The ones mentioned are just the most common and popular.


### Scripts

One of the most powerful characteristics of Nmap is its capacity to automate tasks using custom scripts. The parameter `--script` from Nmap allows the user to select a set of scripts to run against the objectives.

There are many script categories available at Nmap, each one designed to do a certain task. Some of the most common ones are:

- **default**: This is the default category in Nmap, includes a wide variety of reconnaissance and useful scripts for most of the scans.
- **discovery**: This category focuses in finding information inside a network, like discovering hosts and active devices.
- **safe**: Includes scripts that considered safe and do not realize invasive operations that could trigger a security alert on the network.
- **intrusive**: Includes scripts more invasive that can be detected easily by the security measures, but can provide valuable information about vulnerabilities and weaknesses in a network.
- **vuln**: This category focuses mainly in vulnerability and weaknesses recognition of the hosts and services running in a network.

---
## File descriptors

Another way to enumerate ports is using **file descriptors** in the Unix systems. File descriptors are a way to access and manipulate files and devices in Unix systems. In particular, the use of */dev/tcp* gives us the capacity to create a connection to a specific host and port.

To do this job is possible to create a script that does the connection to each port that we are interested in, and the script will check if the port is opened or closed based in if it can send or receive data. One way to do this is to use commands like `echo` or `cat`, applying redirects to */dev/tcp*. The status code returned can be used to know if the port is open or closed.

A sample script is:

```bash
#!/bin/bash

function ctrl_c(){
  echo -e "\n\n[!] Aborting...\n"
  tput cnorm; exit 1 # Shows the cursor again
}

# Ctrl+C
trap ctrl_c SIGINT

declare -a ports=( $(seq 1 65535) )

function checkPort(){

  # Launches file descriptor starting a connection to IP and port
  (exec 3<> /dev/tcp/$1/$2) 2>/dev/null

  if [ $? -eq 0 ]; then
    echo "[+] Host $1 - Port $2 (OPEN)"
  fi

  # Closes file descriptor
  exec 3<&-
  exec 3>&-
}

tput civis # Hides the cursor

if [ $1 ]; then
  for port in ${ports[@]}; do
    checkPort $1 $port &
  done
else
  echo -e "\n[!] Use: $0 <ip-address>\n"
fi

wait

tput cnorm
```


