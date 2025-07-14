---
tags:
  - linux/system/monitor
---

# Grafana

## What is

Grafana is an open-source tool, my main reason to use this tool is that it provides a web interface from where I can monitor everything I need.


## How To

Docker needs to be installed, follow the [installation guide](docker.md).

Then we will use docker compose to run our Grafana docker. We can create a `docker-compose.yaml` file with the following content:

```yaml
services:
  grafana:
    image: grafana/grafana-oss
    container_name: grafana
    restart: unless-stopped
    ports:
     - '3000:3000'
    volumes:
      - grafana-storage:/var/lib/grafana
volumes:
  grafana-storage: {}
```

To run it inside the custom docker network we use the following file:

```yaml
services:
  grafana:
    image: grafana/grafana-oss
    container_name: grafana
    restart: unless-stopped
    ports:
     - '3000'
    volumes:
      - grafana-storage:/var/lib/grafana
    networks:
      - dockernetwork
volumes:
  grafana-storage: {}
networks:
  dockernetwork:
    external: true
```

To run the docker we have to run `docker compose up -d` in the same directory as the `docker-compose.yaml` file.

Now the grafana docker will be up and running, listening at port 3000, we can access the web interface and login with admin/admin, it will require to update the password at first login.

## Send data to web

To be able to properly monitor our system grafana needs to be able to retrieve data from the real system, in order to do that we will need to run [prometheus](https://prometheus.io/) and [node_exporter](https://github.com/prometheus/node_exporter), they'll run as a service and retrieve the data we want to monitor.

### Prometheus

We can download Prometheus directly from the official [Github repo](https://github.com/prometheus/prometheus), download appropriate `.tar.gz` from the releases. Then extract it, the extracted folder will contain an executable and a `.yml` config file.

We can edit the config file to have only the following lines:

```yml
global:
  scrape_interval: 15s
  evaluation_interval: 15s
scrape_configs:
  - job_name: "prometheus"
    static_configs:
      - targets: ["localhost:9090"]
        labels:
          app: "prometheus"
  - job_name: "node"
    static_configs:
    - targets: ['localhost:9100']
```

Now we can run prometheus by using the executable and specifying the config file we just created:

```bash
./prometheus --config.file=./prometheus.yml
```

As we can see, the program now will be running in the context of our TTY, so when we exit the session, program will close too. To avoid that we can install prometheus as a service, first of all I'll copy the executable into `/usr/local/bin/` and the config file into `/etc/prometheus`. As the service will run in the context of another user, dedicated for this task, we will need to create it using `useradd -rs /bin/false prometheus`, and now `prometheus` will be the user which will run the service.

Now we need to create the service file, we use the path `/etc/systemd/system/prometheus.service`, as the content of the file we will insert the following:

```ini
[Unit]
Description=Prometheus
After=network.target

[Service]
User=prometheus
Group=prometheus
Type=simple
Restart=on-failure
RestartSec=5s
ExecStart=/usr/local/bin/prometheus --config.file=/etc/prometheus/prometheus.yml --storage.tsdb.path=/var/lib/prometheus/
LimitNOFILE=65535

[Install]
WantedBy=multi-user.target
```

As it can be seen in the service file, we will use the path `/var/lib/prometheus` as the storage path, so it will need to be created beforehand, and the user `prometheus` should be the owner of that folder.

Finally we can start and enable the service by running:

```bash
systemctl daemon-reload
systemctl enable --now prometheus
```

### NodeExporter

We can download Node Exporter directly from the official [Github repo](https://github.com/prometheus/node_exporter), download appropriate `.tar.gz` from the releases. Then extract it, this time the extracted folder will only contain an executable.

We can just make that executable run as a service. So, same as before, we copy the executable to `/usr/local/bin/` and create the file `/etc/systemd/system/node_exporter.service` with the content:

```ini
[Unit]
Description=Node Exporter
After=network.target

[Service]
User=node_exporter
Group=node_exporter
Type=simple
Restart=on-failure
RestartSec=5s
ExecStart=/usr/local/bin/node_exporter
LimitNOFILE=65535

[Install]
WantedBy=multi-user.target
```

And run the service with:

```bash
systemctl daemon-reload
systemctl enable --now node_exporter
```


## Dashboard

First of all we need to configure Grafana to collect data from our Prometheus + Node Exporter installation. We can configure it from `Home -> Connections -> Data Sources`, select an identifying name and as URL type `http://172.17.0.1:9090`.

We will use the following [dashboard](https://grafana.com/grafana/dashboards/1860-node-exporter-full/). We need to download it's JSON file and create a new dashboard using that file and the previously created data source.
