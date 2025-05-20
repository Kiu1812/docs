---
tags:
  - docker
---

# Docker


## Installation

To install [docker](https://www.docker.com/) and [docker compose](https://docs.docker.com/compose/) we need to run the following commands:

```bash
# Add Docker's official GPG key:
apt-get update
apt-get install ca-certificates curl
install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc
chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources:
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/debian \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  tee /etc/apt/sources.list.d/docker.list > /dev/null
apt-get update

# Install the docker packages:
apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```


## Configuration

### Modify the data path

I want to modify the location where docker stores all of the data to save it into the drive with RAID-1.
We can do that by modifying the service file, at path `/usr/lib/systemd/system/docker.service` and append `--data-root /mnt/external/.docker-data/` at the end of the `ExecStart=...` line.

Finally we just need to enable and restart the service.

```bash
systemctl enable --now docker.service
systemctl restart docker.service
```
