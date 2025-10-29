
# Homelab


## Hardware

1x [ZimaBoard 432](https://shop.zimaspace.com/products/zimaboard-single-board-server?variant=39283928432838)
2x HDD (2 TB)
1x Switch (5 ports)
## Software

### OS

OS Installed: Debian 12.10.
Disks are in a [RAID-1](raid.md) status, investigation about how to implement RAID-1 was made in [2025-04-29](../../04%20-%20Daily/2025-04-29.md), although it wasn't useful at the whole because the old disk got corrupted before being able to have any RAID-1 active.

### Services

- Nginx Reverse Proxy.
- AdGuard Home (DNS) / DHCPD (DHCP).
- Cloudflared -> Cloudflare reverse proxy.
- MariaDB -> Database.
- Vaultwarden -> Password manager.
- Nginx -> Just for hosting the documentation.
- Nextcloud -> Cloud storage.
- Twingate -> VPN Connection.
- OpenWebUI -> AI local web interface.
- [Grafana](grafana.md) -> Monitoring server status.
- MDADM Monitoring -> Monitors RAID status and sends mail if it fails.
- Certbot -> Automatized renewal of LetsEncrypt certificates to use locally.
- NAT -> Use the server as a router.


Analyze how to do everything with docker compose, creating groups of containers for each application.

The objective is to be able to run a `docker compose up` and have everything running again (check feasability of that).

#### DHCPD

Install with package manager:

```bash
apt install isc-dhcp-server
```

Append the following lines to the end of the configuration at `/etc/dhcp/dhcpd.conf`.

```
subnet 10.0.0.0 netmask 255.255.0.0 {
  range 10.0.0.100 10.0.255.255;
  option routers 10.0.0.1;
  option domain-name-servers 10.0.0.1;
  option domain-name "domain.com";
  interface enp3s0;

  host reserva {
    hardware ethernet FF:FF:FF:FF:FF:FF;
    fixed-address 10.0.0.2;
  }
}
```

To apply the new configuration restart service with:

```bash
service isc-dhcp-server restart
```

#### NAT

Configuration at `/etc/nftables.conf`.

```
table ip personalnat {

        chain postrouting {
                type nat hook postrouting priority 100;
                iif "enp3s0" oif "enp2s0" masquerade
        }
}
```


Restart service with.

```bash
service nftables restart
```

We also need to enable packet forwarding for sysctl, in order to do that we just have to un-comment the line `net.ipv4.ip_forward=1` from the file `/etc/sysctl.conf`, then apply it with the command `sysctl -p`.