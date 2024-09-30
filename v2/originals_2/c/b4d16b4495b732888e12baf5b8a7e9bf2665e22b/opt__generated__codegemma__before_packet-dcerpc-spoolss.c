## DCERPC SpoolSS Protocol Dissector

This document describes the DCERPC SpoolSS protocol dissector for Wireshark.

**Protocol Overview:**

The SpoolSS protocol is used for printing services in Microsoft Windows operating systems. It provides features like:

* Sending and receiving printer jobs
* Managing printer drivers
* Handling printer status notifications

**Dissector Structure:**

The SpoolSS dissector is based on the DCERPC protocol dissector framework. It includes the following components:

* **Protocol:** The SpoolSS protocol itself
* **Data Types:** Various data structures used in the protocol
* **Fields:** Individual components within the data structures
* **Expert Info:** Warnings and notifications for unknown data or invalid values

**Dissector Initialization:**

* The dissector registers a protocol named "SPOOLSS" with the Wireshark protocol dissector framework.
* It defines fields and subtrees for different data structures.
* It registers expert information for handling unknown or invalid data.

**Protocol Handoff:**

* The dissector registers the SpoolSS protocol as a DCERPC protocol with a specific UUID and version.
* This allows it to be recognized and handled by the DCERPC framework.

**Key Dissections:**

* The dissector handles various operations related to printers, jobs, drivers, and notifications.
* It extracts information from the raw data and presents it in a meaningful way.

**Limitations:**

* The dissector is currently marked as "unimplemented" for some sections. This means that those parts of the protocol may not be fully dissected.
* The dissector may encounter unknown data or invalid values, which will be flagged as warnings in the expert panel.

**Additional Notes:**

* The Wireshark dissector guide provides more information about dissector development.
* The SpoolSS protocol specification is available from Microsoft.

**Disclaimer:**

This information is provided for educational purposes only. It is not intended to be a substitute for official documentation or support.