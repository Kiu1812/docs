# Operating System Identification

---

The *Time to Live* (TTL) references the amount of jumps that a packet can do inside a network before being discarded by the router. The *TTL* is also used in another contexts, like cache storage for CDN and DNS.

Each packet has a place where it stores a numeric value that determines the time that it has to be moving through the network. Each time a router receives a packet, substracts one from the *TTL* count y sends it to the next place in the network. If at any moment the count reaches zero after the substraction, the packet will be discarded and it will send an *ICMP* packet to the origin host.

But, what has this to do with the identification of a remote operating system? Well, different operating systems have different default values for the *TTL*. By example, **Windows** has a value of **128** and in **Linux** it is **64**. That means that if we send a packet to a machine and we get a response with a value around 128 is probable that the remote machine is running a Windows, if it returns a value around 64 instead it means we are against a Linux machine.

This method is not foolproof and can be fooled by network administrators, but can be useful to identify the operating system of a machine.

In the [following web](https://subinsb.com/default-device-ttl-values/) we have a list of multiple operating systems and their respective TTL Values.





