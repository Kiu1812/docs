
# Subdomains

Subdomains are part of a bigger domain and are often configured to serve different network resources, like web servers, mail servers, database systems and others.

By identifying subdomains linked to a main domain an attacker could obtain valuable information for each one of these, what could lead to find potential attack vectors.

There are different tools and techniques used to enumerate subdomains, both passive and active. Passive tools allow us to obtain information without sending any request to the identified servers, while active tools send requests to the servers to find subdomains under the main domain.

Some of the passive tools most used to enumerate include the search through the search engines like Google or Bing, and the search in public DNS registers like PassiveTotal or Censys. Those tools allow us to identify subdomains, although not always are exhaustive. Additionally there are tools like [CTFR](https://github.com/UnaPibaGeek/ctfr/tree/master) that use SSL/TLS certificate registries to find subdomains.

There are other webpages like [Phonebook.cz](https://phonebook.cz/) and [Intelx.io](https://intelx.io/), or tools like [sublist3r](https://github.com/aboul3la/Sublist3r) to do these passive tasks.

In the other side, some of the active tools are [wfuzz](https://github.com/xmendez/wfuzz) and [gobuster](https://github.com/OJ/gobuster). Those tools send requests to the servers using bruteforce to find valid subdomains.

Example commands for wfuzz and gobuster:


- Gobuster
```bash
gobuster vhost -u http://domain.com -w <wordlist> -t 20 --append-domain true
```

<br>

- Wfuzz
```bash
wfuzz -c --hc=403 -t 20 -w <wordlist> -H "Host: FUZZ.domain.com" http://domain.com
```