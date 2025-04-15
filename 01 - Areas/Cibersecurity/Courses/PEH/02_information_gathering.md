
# 🔍 Information Gathering (Reconnaissance)

---

## Passive Reconnaissance Overview

There are two types of passive reconnaissance:

### Physical / Social:

This means to actually go to the building and maybe doing a **physical engagement**, or the **social engineering** aspect doing a phishing assessment or merging those to to try to get into the private areas.

We have **location information**, we can use satellite images, often will go on site and do drone reconnaissance and what we are searching is things like, building layout, badge readers, break areas, security people, fencing, areas with doors open, etc....

In the other hand we can search for **information about the job**, employees, it's name, title, phone number, manager. We can also search for pictures like badge photos, desk photos, computer photos.


### Web / Host:

The first thing we should do is **target validation**, there are situations where a client will give you an IP address or a website and the client mistypes some character and you're attacking another website you shouldn't.

Another things to do is **search for subdomains**, we can use google, nmap, sublist3r, etc....

There's also **fingerprinting**, we need to know what's running on a website or a host, what kind of services are running, is a web server, which one, maybe IIS or Apache, what version of it, what ports are running. But we are still on the passive side, we are not gonna touch and scan the machines, maybe just connect to the website and look through there but without actually scanning it.

Lastly, we need to search for **data breaches**, we are talking about breached incidents from the past that could have leaked data, we can try to utilize those to get access, or at least the usernames

---

## Identifying Our Target

Before we begin doing our reconnaissance we have to establish a client to attack. This course uses a target from [bugcrowd](https://www.bugcrowd.com/).

In bug bounty websites it's important to always take a look at the scope, those are the targets and things we are allowed to search in, so we need to make sure we stay inside the scope and do not perform any kind of activity in the *Out Of Scope* items.

---

## Discovering Email Addresses

A list of useful resources to find emails:


- [hunter.io](https://hunter.io/): We type the company name and we see emails related to that company.
- [phonebook.cz](https://phonebook.cz/): With this resource we can search for domains and URLs as well as email addresses.
- [voilanorbert.com](https://www.voilanorbert.com/): We have a limited amount but it's quite the same of *hunter.io*.
- [Clearbit Connect](https://clearbit.com/resources/tools/connect): In a web extension type, we have this resource, we can filter by role and seniority.
- [EmailHippo](https://tools.emailhippo.com/): With this website we can verify if an email address exists or not.
- [Email Checker](https://email-checker.net/): Another website to test if an email address is valid or not.

---

## Gathering Breached Credentials with Breach-Parse

[breach-parse](https://github.com/hmaverickadams/breach-parse) is a tool created to search for breached passwords in a database of around 44GB, you can filter by domain to search for breached usernames and passwords from that domain specifically.

Example running of the tool are:

```bash
./breach-parse.sh @tesla.com tesla.txt
```

It will output three files:

- `*-master.txt`: Contains the list of usernames and passwords.
- `*-passwords.txt`: Contains only the list of passwords.
- `*-users.txt`: Contains only the list of usernames.

---

## Hunting Breached Credentials with DeHashed

[DeHashed](https://dehashed.com/) has the ability to search by many different type fields like Email, Username, IP, Name. Having so many fields can help us to get even more information about anything.

It searches information through a high amount of breached databases to search for the desired text.

The bad thing about this website is that it requires a subscription to see the real data.


---

## Hunting Subdomains

The most important thing when it comes to websites is to identify subdomains of it.

By searching for subdomains we may find hidden websites that shouldn't be available on internet because they contain sensitive information.

### Sublist3r

One useful tool is [sublist3r](https://github.com/aboul3la/Sublist3r). This is a passive tool, that means that it doesn't interact with the target domain but instead only uses public information.
We can install it by running the following command:
```bash
apt install sublist3r
```

<br>

Then we can run it as a normal binary indicating the domain to search for with the parameter `-d <domain.com>`:
```bash
sublist3r -d <domain.com>
```

<br>

If we see sublist3r going too slow we can increase it's threads with the following command:
```bash
sublist3r -d <domain.com> -t <thread_amount>
```

### Crt.sh

Another resource we can use is the website [crt.sh](https://crt.sh/).
Here we can insert the domain with the wildcard to search for subdomains like this `%.domain.com`.

This website can list subdomains in any level.
<br>
### Amass

The [OWASP Amass Project](https://github.com/owasp-amass/amass) performs network mapping of attack surfaces and external asset discovery using open source information gathering and active reconnaissance techniques.
<br>
### httprobe

A lot of the domains returned by those tools may be unavailable anymore, that when [httprobe](https://github.com/tomnomnom/httprobe) comes into play.

This tool takes a list of domains and probe for working http and https servers.


---

## Identifying Website Technologies

We are gonna look at what a website is built with.

So the first tool we are gonna see is [builtwith](https://builtwith.com/), we just type the domain and it give us the technology that the website is running.

We can also use the plugin Wappalyzer, which is available on both Firefox and Chrome.
To use it we need to open the extension from the icon and it gives us the information.

Another tool is Whatweb, this comes pre-installed in Kali Linux and to use it we execute it with the domain to search:
```bash
whatweb <domain.com>
```

