# Linux

---

The most important part once we finally penetrated into a machine is to enumerate everything we can.
By enumerating everything it becomes easier, among other this, to identify the potential ways to escalate our privileges as an user.


## Users

To check which user we are right now we can use the `whoami` command.

We can enumerate other users by taking a look at */etc/passwd*. Here is where Linux systems store the main information about the users that are registered on the system.


If we want to list all users we can just read the file:
```bash
cat /etc/passwd
```

<br>

If we want to list only the users that have a shell assigned to them we can filter by the string **sh**:
```bash
grep "sh" /etc/passwd
```


This file also gives us other useful information like the user UID, GID and its home directory.


## Groups

To check which groups the current user belongs to we can use the `groups` command.

To enumerate groups we can read the */etc/group* file. This file contains information about the created groups at the system, it also lists the users who belong to that certain group:
```bash
cat /etc/group
```


## Processes

To list all processes running in a linux machine we can use either of these commands:

```bash
ps aux
ps -ef
```


## Binaries

A common way to escalate privileges is by using SUID or capabilities of the numerous binaries present in a system. We can list them with:

Binaries with SUID flag.
```bash
find / -perm -4000 -ls 2>/dev/null
```

<br>

Binaries with capabilities.
```bash
getcap -r / 2>/dev/null
```


## Programmed tasks

We can search for programmed tasks with the following commands.
```bash
crontab -l
cat /etc/crontab
systemctl list-timers
```




## Automated Tools

We have a big amount of tools to automate the local enumeration, some of the most common ones are:

- [LinPEAS](https://github.com/peass-ng/PEASS-ng/tree/master/linPEAS) is a script that search for possible paths to escalate privileges on Linux/Unix*/MacOS hosts
- [Linux Smart Enumeration](https://github.com/diego-treitos/linux-smart-enumeration) (*LSE*) will show relevant information about the security of the local Linux system, helping to escalate privileges
- [pspy](https://github.com/DominicBreuker/pspy) is a command line tool designed to snoop on processes without need for root permissions. It allows you to see commands run by other users, cron jobs, etc. as they execute.
