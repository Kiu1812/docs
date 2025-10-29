---
tags:
  - linux/disk/raid
---

# RAID

RAID was configured as mentioned in [2025-04-29](../../04%20-%20Daily/2025-04-29.md).

Once the RAID is configured we need a way to monitor it, to do it we will configure a `Postfix` client.

Then I added the fields `MAILADDR` and `MAILFROM` at `/etc/mdadm/mdadm.conf`, once simulated a fail we will see that a mail is received at the address specified.