---
tags:
  - cibersecurity/active_directory/fundamentals
center: index.md
next: 02_protocols.md
---

# Active Directory Fundamentals


## Active Directory Structure

[Active Directory (AD)](https://docs.microsoft.com/en-us/windows-server/identity/ad-ds/get-started/virtual-dc/active-directory-domain-services-overview) is a directory service for Windows network environments. It is a distributed, hierarchical structure that allows for centralized management of an organization's resources, including users, computers, groups, network devices and file shares, group policies, servers and workstations, and trusts.

AD is essentially a large database accessible to all users within the domain, regardless of their privilege level. A basic AD user account with no added privileges can be used to enumerate the majority of objects contained within AD, including but not limited to:


| Domain Computers         | Domain Users                |
| ------------------------ | --------------------------- |
| Domain Group Information | Organizational Units (OUs)  |
| Default Domain Policy    | Functional Domain Levels    |
| Password Policy          | Group Policy Objects (GPOs) |
| Domain Trusts            | Access Control Lists (ACLs) |

Active Directory is arranged in a hierarchical tree structure, with a forest at the top containing one or more domains, which can themselves have nested subdomains.

A domain is a structure within which contained objects (users, computers, and groups) are accessible. It has many built-in Organizational Units (OUs), such as `Domain Controllers`, `Users`, `Computers`, and new OUs can be created as required.

It is common to see multiple domains (or forests) linked together via trust relationships in organizations that perform a lot of acquisitions.

If a trust relationship is set between two top level domains, that doesn't mean the subdomains from forest A can access subdomains from forest B, if we want to have that connection we will need to set another trust relationship.

## Active Directory Terminology




## Active Directory Objects




## Active Directory Functionality


