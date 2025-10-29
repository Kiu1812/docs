# Fuzzing

---

Fuzzing is a technique used to discover paths and resources hidden in a web server through brute force attacks. The objective is to find hidden resources that could be used to obtain unauthorized access to the server.

## Gobuster

### Description

[Gobuster](https://github.com/OJ/gobuster) is a tool used to brute-force:

- URIs (directories and files) in web sites.
- DNS subdomains (with wildcard support).
- Virtual Host names on target web servers.
- Open Amazon S3 buckets
- Open Google Cloud buckets
- TFTP servers


One of the main advantages of Gobuster is the speed that it has in discovering content.

### Parameters

| **Parameter**    | **Description**                                |
| ---------------- | ---------------------------------------------- |
| dir              | Use directory or file enumeration mode         |
| -u <url>         | Specify the URL to fuzz                        |
| -w <wordlist>    | Specify the wordlist to use                    |
| -t <INT>         | Number of parallel threads                     |
| --add-slash      | Adds a **/** at the end of the path            |
| -b <status-code> | Exclude the specified status code from results |
| -s <status-code> | Show only the specified status code            |
| -x <extension>   | Add extensions to the end of the path          |

### Examples

- Basic fuzzing:
```bash
gobuster dir -u https://domain.com -w <wordlist> -t 200
```

<br>

- Add a `/` at the end of each path and exclude certain status codes:
```bash
gobuster dir -u https://domain.com -w <wordlist> -t 200 -b 403,404
```

<br>

- Test specific extensions:
```bash
gobuster dir -u https://domain.com -w <wordlist> -t 200 -b 403,404 -x php,html,txt
```

<br>

- Show only status code 200:
```bash
gobuster dir -u https://domain.com -w <wordlist> -t 200 -s 200 -b '' -x php,html,txt
```


## Wfuzz

### Description

[Wfuzz](https://github.com/xmendez/wfuzz) has been created to facilitate the task in web applications assessments and it is based on a simple concept: it replaces any reference to the FUZZ keyword by the value of a given payload.

###  Parameters

| **Parameter**                    | **Description**                                                    |
| -------------------------------- | ------------------------------------------------------------------ |
| -c                               | Display output with colors                                         |
| -t <INT>                         | Number of parallel threads                                         |
| -w <wordlist>                    | Specifies the wordlist to use                                      |
| --hc=<status-code>               | Excludes the specified status code from being shown                |
| -L                               | Follow redirects                                                   |
| -z <payload-type>,<payload-data> | Allows specifying custom payloads, for example for file extensions |


### Examples


- Basic fuzzing:
```bash
wfuzz -c -t 200 -w <wordlist> https://domain.com/FUZZ
```

<br>

- Exclude status codes 404 and 403:
```bash
wfuzz -c --hc=404,403 -t 200 -w <wordlist> https://domain.com/FUZZ
```

<br>

- Test specific extensions:
```bash
wfuzz -c --hc=404,403 -t 200 -w <wordlist> -z list,html-txt-php https://domain.com/FUZZ.FUZ2Z
```


## Ffuf


### Description

[Ffuf](https://github.com/ffuf/ffuf) is a fast web fuzzer written in Go.

### Parameters

| Parameter       | Description                                                                                   |
| --------------- | --------------------------------------------------------------------------------------------- |
| -u              | Target URL                                                                                    |
| -w <wordlist>   | Wordlist file path and (optional) keyword separated by colon. eg. '/path/to/wordlist:KEYWORD' |
| -c              | Colorize output.                                                                              |
| -v              | Verbose output, printing full URL and redirect location (if any) with the results.            |
| -mc             | Match HTTP status codes, or "all" for everything.                                             |


### Examples

- Basic fuzzing:
```bash
ffuf -c -t 200 -w \<wordlist\> -u https://domain.com/FUZZ
```

<br>

- Show only status code 200:
```bash
ffuf -c -t 200 -w \<wordlist\> -u https://domain.com/FUZZ --mc=200
```