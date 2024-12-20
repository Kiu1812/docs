This section provides detailed notes and resources for each module of the [Practical Ethical Hacking](https://academy.tcm-sec.com/p/practical-ethical-hacking-the-complete-course) course from [TCM Security](https://tcm-sec.com/).

### 📜 The Ethical Hacker Methodology
- [The Five Stages of Ethical Hacking](five_stages.md)

### 🔍 Information Gathering (Reconnaissance)
- [Passive Reconnaissance Overview](information_gathering.md#passive-reconnaissance-overview)
- [Identifying Our Target](information_gathering.md#identifying-our-target)
- [Discovering Email Addresses](information_gathering.md#discovering-email-addresses)
- [Gathering Breached Credentials with Breach-Parse](information_gathering.md#gathering-breached-credentials-with-breach-parse)
- [Hunting Breached Credentials with DeHashed](information_gathering.md#hunting-breached-credentials-with-dehashed)
- [Hunting Subdomains](information_gathering.md#hunting-subdomains)
- [Identifying Website Technologies](information_gathering.md#identifying-website-technologies)
- [Information Gathering with Burp Suite](information_gathering.md#)
- [Google Fu](information_gathering.md#)
- [Utilizing Social Media](information_gathering.md#)

### 📡 Scanning & Enumeration
- [Installing Kioptrix](ScanningAndEnumeration/Installing_Kioptrix.md)
- [Scanning with Nmap](ScanningAndEnumeration/Nmap.md)
- [Enumerating HTTP and HTTPS](ScanningAndEnumeration/Enumerating_HTTP_HTTPS.md)
- [Enumerating SMB](ScanningAndEnumeration/Enumerating_SMB.md)
- [Enumerating SSH](ScanningAndEnumeration/Enumerating_SSH.md)
- [Researching Potential Vulnerabilities](ScanningAndEnumeration/Researching_Vulnerabilities.md)
- [Our Notes So Far](ScanningAndEnumeration/Notes.md)

### 🔓 Exploitation Basics
- [Reverse Shells vs Bind Shells](ExploitationBasics/Reverse_vs_Bind_Shells.md)
- [Staged vs Non-Staged Payloads](ExploitationBasics/Staged_vs_NonStaged.md)
- [Gaining Root with Metasploit](ExploitationBasics/Metasploit_Root.md)
- [Manual Exploitation](ExploitationBasics/Manual_Exploitation.md)
- [Brute Force Attacks](ExploitationBasics/Brute_Force.md)
- [Credential Stuffing and Password Spraying](ExploitationBasics/Credential_Stuffing.md)
- [Our Notes, Revisited](ExploitationBasics/Notes_Revisited.md)

### 🖥 Active Directory
#### Overview
- [Active Directory Overview](ActiveDirectory/Overview/AD_Overview.md)
- [Physical and Logical Components](ActiveDirectory/Overview/Physical_Logical_Components.md)

#### Lab Build
- [Lab Overview and Setup](ActiveDirectory/LabBuild/Lab_Setup.md)

#### Initial Attack Vectors
- [LLMNR Poisoning & Mitigation](ActiveDirectory/InitialAttackVectors/LLMNR_Poisoning.md)
- [SMB Relay Attacks & Defenses](ActiveDirectory/InitialAttackVectors/SMB_Relay.md)
- [IPv6 DNS Takeover and Defenses](ActiveDirectory/InitialAttackVectors/IPv6_DNS_Takeover.md)

#### Post-Compromise Enumeration
- [Domain Enumeration with ldapdomaindump](ActiveDirectory/PostCompromiseEnumeration/Domain_Enumeration.md)
- [Bloodhound, Plumhound, and PingCastle](ActiveDirectory/PostCompromiseEnumeration/Bloodhound.md)

#### Post-Compromise Attacks
- [Pass the Hash and Other Attacks](ActiveDirectory/PostCompromiseAttacks/Pass_The_Hash.md)
- [Dumping and Cracking Hashes](ActiveDirectory/PostCompromiseAttacks/Dumping_Hashes.md)
- [Kerberoasting](ActiveDirectory/PostCompromiseAttacks/Kerberoasting.md)
- [Token Impersonation](ActiveDirectory/PostCompromiseAttacks/Token_Impersonation.md)
- [Mimikatz Overview and Credential Dumping](ActiveDirectory/PostCompromiseAttacks/Mimikatz.md)

### 📝 Post Exploitation
- [File Transfers Review](PostExploitation/File_Transfers.md)
- [Maintaining Access Overview](PostExploitation/Maintaining_Access.md)
- [Pivoting](PostExploitation/Pivoting.md)
- [Cleaning Up](PostExploitation/Cleaning_Up.md)

### 🌐 Web Application Testing
- [SQL Injection](WebApplicationTesting/SQL_Injection.md)
- [XSS](WebApplicationTesting/XSS.md)
- [Command Injection](WebApplicationTesting/Command_Injection.md)
- [Insecure File Upload](WebApplicationTesting/File_Upload.md)
- [Authentication Attacks](WebApplicationTesting/Authentication_Attacks.md)

### 📶 Wireless Penetration Testing
- [Wireless Penetration Testing Overview](WirelessPenetrationTesting/Wireless_Overview.md)
- [WPA PSK Exploit Walkthrough](WirelessPenetrationTesting/WPA_PSK.md)

### 📑 Legal and Reporting
- [Common Legal Documents](LegalAndReporting/Legal_Documents.md)
- [Pen Test Report Writing](LegalAndReporting/Report_Writing.md)
- [Reviewing a Real Pen Test Report](LegalAndReporting/Report_Review.md)

### 🎯 Career Advice
- [Career Guidance and Recommendations](CareerAdvice/Career_Advice.md)

