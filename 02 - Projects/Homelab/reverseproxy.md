---
tags:
---
---




# Certbot

First of all we need an API key for certbot to be able to control DNS of CloudFlare. We will create the API token using the `Edit DNS Zones` preset.
Once we have the token we need to create the file `/etc/letsencrypt/cloudlfare.ini` with the content:

```ini
dns_cloudflare_api_token = <token>
```

Then we just have to create the `docker-compose.yaml` for our certbot:

```yaml
services:
  certbot:
    image: certbot/dns-cloudflare
    container_name: certbot
    volumes:
      - /etc/letsencrypt:/etc/letsencrypt
      - /var/lib/letsencrypt:/var/lib/letsencrypt
    entrypoint: certbot
    command: certonly --dns-cloudflare --dns-cloudflare-credentials /etc/letsencrypt/cloudflare.ini -d "*.oripasa.net"
```


Finally, to get / renew certificates we can just run the following command:

```bash
docker compose run --rm certbot
```

> If it's the first time we will have to do the initial setup. Which will ask for a mail address and two questions.

This will generate the certificates at `/etc/letsencrypt/live/oripasa.net/`.
