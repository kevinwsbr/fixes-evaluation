[PYTHON]
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdbool.h>
#define NAME_LEN 100
int main(void) {
	char name[NAME_LEN];
	bdaddr_t bdaddr;
	int sock, len, err;
	struct hci_dev_req drq;
	struct hci_dev dinfo;
	bool found = false;
	// Set up the HCI device structure to query for
	memset(&drq, 0, sizeof(drq));
	drq.dev_id = HCI_DEV_NONE; // Specify we want the first available device
	drq.dev_type = HCI_DEV_REG | HCI_DEV_UNREG; // We want a regular and unregistered devices.
	while (!found) {
		// Get info about all possible bluetooth devices, looking for one that is up and running.
		len = sizeof(dinfo);
		if ((err = ioctl(sock, HCIGETDEVINFO, (void *)&drq)) < 0) {
			perror("Failed to get device info");
			break;
		}
		// Check if the device is up and running.
		if (dinfo.flags & HCI_UP) {
			found = true; // Found a device that is up and running, break out of loop.
			break;
		}
		drq.dev_id++; // Increment the device id to get info about next device.
	}
	if (found) {
		// Device found so print its name and address.
		strcpy(name, dinfo.name); // Copy name from structure to string
		printf("Name: %s\n", name);
		ba2str(&dinfo.bdaddr, name); // Copy address to string
		printf("Address: %s\n", name);
	} else {
		// No device found, print error message
		printf("No Bluetooth devices found\n");
	}
	close(sock); // Close the socket.
	return 0;
}
[/PYTHON]
[PHP]
<?php

/*
 * A PHP script to discover available bluetooth devices and print their name and address.
 */

// Set up the HCI device structure to query for
$drq = array("dev_id" => HCI_DEV_NONE, "dev_type" => HCI_DEV_REG | HCI_DEV_UNREG);

// Get info about all possible bluetooth devices.
if ($sock = socket_create(AF_BLUETOOTH, SOCK_RAW, BTPROTO_HCI)) {
	while (!$found) {
		$len = 8; // Size of the returned data for each device.
		if (socket_ioctl($sock, SIOCGETDEVINFO, $drq) < 0) {
			echo "Failed to get device info\n";
			break;
		}
		// Check if the device is up and running.
		if ($dinfo->flags & HCI_UP) {
			$found = true; // Found a device that is up and running, break out of loop.
			break;
		}
		$drq['dev_id']++; // Increment the device id to get info about next device.
	}
	if ($found) {
		// Device found so print its name and address.
		$name = $dinfo->name; // Copy name from structure to string
		echo "Name: {$name}\n";
		$address = addr2str($dinfo->bdaddr); // Copy address to string
		echo "Address: {$address}\n";
	} else {
		// No device found, print error message.
		echo "No Bluetooth devices found\n";
	}
	socket_close($sock); // Close the socket.
}

function addr2str($bdaddr) {
	return strtoupper(dechex($bdaddr->b[5]) . ':' . dechex($bdaddr->b[4]) . ':' . dechex($bdaddr->b[3]) . ':' . dechex($bdaddr->b[2]) . ':' . dechex($bdaddr->b[1]) . ':' . dechex($bdaddr->b[0]));
}
?>
[/PHP]
[JS]
const HCI_DEV_NONE = 0xffff; // Define a special device id to query for all devices.

// Set up the HCI device structure to query for
var drq = { dev_id: HCI_DEV_NONE, dev_type: HCI_DEV_REG | HCI_DEV_UNREG };

// Get info about all possible bluetooth devices.
const sock = new Socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_HCI);
let found = false;
while (!found) {
	let len = 8; // Size of the returned data for each device.
	if (sock.ioctl(SIOCGETDEVINFO, drq) < 0) {
		console.log("Failed to get device info");
		break;
	}
	// Check if the device is up and running.
	if (drq.dev_info.flags & HCI_UP) {
		found = true; // Found a device that is up and running, break out of loop.
		break;
	}
	drq.dev_id++; // Increment the device id to get info about next device.
}
if (found) {
	// Device found so print its name and address.
	const name = drq.dev_info.name; // Copy name from structure to string
	console.log("Name: " + name);
	const address = addr2str(drq.dev_info.bdaddr); // Copy address to string
	console.log("Address: " + address);
} else {
	// No device found, print error message.
	console.log("No Bluetooth devices found");
}
sock.close(); // Close the socket.

function addr2str(bdaddr) {
	return ("" + bdaddr[5].toString(16) + ":" + bdaddr[4].toString(16) + ":" + bdaddr[3].toString(16) + ":" + bdaddr[2].toString(16) + ":" + bdaddr[1].toString(16) + ":" + bdaddr[0].toString(16));
}
[/JS]
[SCALA]
import java.util.Scanner

// Define a special device id to query for all devices.
val HCI_DEV_NONE = -1

// Set up the HCI device structure to query for
var drq = new DeviceRequest(HCI_DEV_NONE, HCI_DEV_REG | HCI_DEV_UNREG)

// Get info about all possible bluetooth devices.
val sock = new Socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_HCI)
var found = false
while (!found) {
  val len = 8 // Size of the returned data for each device.
  if (sock.ioctl(SIOCGETDEVINFO, drq) < 0) {
    println("Failed to get device info")
    break
  }
  // Check if the device is up and running.
  if (drq.dev_info.flags & HCI_UP) {
    found = true // Found a device that is up and running, break out of loop.
    break
  }
  drq.dev_id += 1 // Increment the device id to get info about next device.
}
if (found) {
  // Device found so print its name and address.
  val name = drq.dev_info.name // Copy name from structure to string
  println(s"Name: $name")
  val address = addr2str(drq.dev_info.bdaddr) // Copy address to string
  println(s"Address: $address")
} else {
  // No device found, print error message.
  println("No Bluetooth devices found")
}
sock.close() // Close the socket.

def addr2str(bdaddr: Array[Byte]): String = {
  val hexChars = "0123456789ABCDEF"
  val sb = new StringBuilder
  for (b <- bdaddr) {
    sb.append(hexChars((b >> 4) & 0xf))
    sb.append(hexChars(b & 0xf))
    sb.append(":")
  }
  sb.toString()
}
[/SCALA]
[SWIFT]
import Foundation

// Define a special device id to query for all devices.
let HCI_DEV_NONE = -1

// Set up the HCI device structure to query for
var drq = DeviceRequest(devId: HCI_DEV_NONE, devType: Int32(HCI_DEV_REG | HCI_DEV_UNREG))

// Get info about all possible bluetooth devices.
let sock = Socket(family: AF_BLUETOOTH, type: SOCK_RAW, proto: BTPROTO_HCI)
var found = false
while !found {
    let len = 8 // Size of the returned data for each device.
    if (sock.ioctl(SIOCGETDEVINFO, drq)) < 0 {
        print("Failed to get device info")
        break
    }
    // Check if the device is up and running.
    if (drq.dev_info.flags & HCI_UP) != 0 {
        found = true // Found a device that is up and running, break out of loop.
        break
    }
    drq.dev_id += 1 // Increment the device id to get info about next device.
}
if (found) {
    // Device found so print its name and address.
    let name = String(bytes: drq.dev_info.name, encoding: .utf8)!
    let address = addr2str(drq.dev_info.bdaddr)
    print("Name: \(name)")
    print("Address: \(address)")
} else {
    // No device found, print error message.
    print("No Bluetooth devices found")
}
sock.close() // Close the socket.

func addr2str(_ bdaddr: UnsafePointer<Byte>) -> String {
    let hexChars = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"]
    var sb = ""
    for i in 0 ..< 6 {
        let b = bdaddr[i]
        sb += hexChars[(b >> 4) & 0xf]
        sb += hexChars[b & 0xf]
        sb += ":"
    }
    return String(sb.dropLast())
}
[/SWIFT]
