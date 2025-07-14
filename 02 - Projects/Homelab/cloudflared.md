---
tags:
---

We can run the following command to run directly as a docker:

```bash
docker run cloudflare/cloudflared:latest tunnel --no-autoupdate run --token <token>
```


Or use a `docker-compose.yaml` file like this:

```yaml
services:
  cloudflared:
    image: cloudflare/cloudflared:latest
    command: tunnel --no-autoupdate run --token <token>
    restart: unless-stopped
    networks:
      - dockernetwork
networks:
  dockernetwork:
    external: true
```