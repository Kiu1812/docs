---
tags:
---
---

To run AdGuard Home inside a Docker we will use the following `docker-compose.yaml` (with the custom-network already cconfigured).


```yaml
services:
  adguardhome:
    image: adguard/adguardhome
    container_name: adguardhome
    restart: unless-stopped
    ports:
      - "53:53/tcp"
      - "53:53/udp"
    volumes:
      - adguardhome-work:/opt/adguardhome/work
      - adguardhome-conf:/opt/adguardhome/conf
    networks:
      - dockernetwork
volumes:
  adguardhome-work: {}
  adguardhome-conf: {}
networks:
  dockernetwork:
    external: true
```

To configure it at the beginning we can expose the port 80/TCP && 443/TCP too. Once all the config is finished I'll access the configuration through a Nginx reverse proxy.
