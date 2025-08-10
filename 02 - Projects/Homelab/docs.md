---
tags:
---

# Docs

The `docs` section is made with two dockers: `docs` & `devdocs`. The first one is the hosting the documentation you're currently reading. The second is for hosting documentation before publishing it, just to see how it would look.

They both use the [mkdocs docker](https://hub.docker.com/r/squidfunk/mkdocs-material) which provides the material theme.

The `docker-compose.yaml` is the following, changing `docs` by `devdocs` for the other one.

```yaml
services:
  docs:
    image: squidfunk/mkdocs-material
    container_name: docs
    volumes:
      - ./:/docs:ro
    restart: unless-stopped
    networks:
      - dockernetwork

volumes:
  certificates:
networks:
  dockernetwork:
    external: true
```

For the `docs` docker, there's also an script to update them automatically based on the GitHub content.

```bash
#!/bin/bash
ZIP_URL="https://github.com/Kiu1812/docs/archive/refs/heads/main.zip"
DEST_DIR="/mnt/external/docker-compose-repo/docs/docs/docs"
BUILD_PATH="/mnt/external/docker-compose-repo/docs/docs/"
TMP_DIR="/tmp/docs_temp"
ZIP_FILE="$TMP_DIR/main.zip"
/usr/bin/mkdir -p "$TMP_DIR"
/usr/bin/curl -L "$ZIP_URL" -o "$ZIP_FILE" || { /usr/bin/echo "❌ Failed to download ZIP file"; exit 1; }
/usr/bin/unzip -q "$ZIP_FILE" -d "$TMP_DIR" || { /usr/bin/echo "❌ Failed to unzip file"; exit 1; }
EXTRACTED_DIR="$TMP_DIR/docs-main"
if [ -d "$DEST_DIR" ]; then
    /usr/bin/rm -rf "$DEST_DIR" || { /usr/bin/echo "❌ Failed to remove existing DEST_DIR"; exit 1; }
fi
/usr/bin/mkdir -p "$DEST_DIR" || { /usr/bin/echo "❌ Failed to create DEST_DIR"; exit 1; }
/usr/bin/mv "$EXTRACTED_DIR"/* "$DEST_DIR" || { /usr/bin/echo "❌ Failed to move files to DEST_DIR"; exit 1; }
cd "$BUILD_PATH"
/usr/bin/docker compose down
/usr/bin/docker compose up -d
/usr/bin/rm -rf "$TMP_DIR"
```


A similar concept is used for the `devdocs` docker, but it uses a local **tar.gz** file instead of GitHub.

```bash
#!/bin/bash
tar -xzvf /tmp/DOCS.tar.gz -C /mnt/external/docker-compose-repo/docs/devdocs/docs
cd /mnt/external/docker-compose-repo/docs/devdocs
docker compose down && docker compose up -d
```

## MkDocs config

In the same folder as the `docs` folder exists a `mkdocs.yml`, which is used to configurate the behavior of mkdocs.

```yml
site_name: Kiu1812 Docs
repo_url: https://github.com/Kiu1812/docs
theme:
  name: material
  palette:
    # Palette toggle for light mode
    - scheme: default
      toggle:
        icon: material/brightness-7
        name: Switch to dark mode

    # Palette toggle for dark mode
    - scheme: slate
      toggle:
        icon: material/brightness-4
        name: Switch to light mode
extra_css:
  - 99 - META/MkDocs_Styling/style.css
exclude_docs: |
    07 - DRAFT
    99 - META
    !99 - META/MkDocs_Styling/style.css
```
