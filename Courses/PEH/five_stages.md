
# The Five Stages of Ethical Hacking

---

These are the five stages you go through on every assessment.

## Reconnaissance

This stage is also known as *Information Gathering*.

There are two different types, *active* and *passive*.

Passive is like going to google and search for public information without going to the company website.
Active is when you interact directly with the company resources. This can be seen as the second stage.

## Scanning & Enumeration

This is where we use tools like Nmap, Nessus, Nikto to search for open ports, vulnerabilities.

With whatever items we get from these results we actually do the enumeration, enumeration is looking at items and digging into them to see if they have something of value, per example, let's say there's port 80 open and we see it's an Apache 1.2, we can search online for vulnerabilities for that specific version.

## Gaining Access

This stage is also known as *Exploitation*.

You'll run an exploit against the client, the vulnerable server or whatever it is to train and gain access into the system, the network, environment, etc....

Once we have that access we repeat the process of scanning and enumeration to gain access to more systems, and we want to also maintain the access to the system.

## Maintaining access

For example if the user shut downs the computer, we need to maintain access to that computer when it turns back on so we still have access to it.

## Covering Tracks

We want to delete any logs, any kind of malware uploaded, accounts created, etc....
