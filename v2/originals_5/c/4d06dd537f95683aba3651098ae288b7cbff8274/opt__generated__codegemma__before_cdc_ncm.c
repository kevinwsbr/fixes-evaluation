**USB CDC NCM Driver**

This driver supports USB CDC (Communication Device Class) NCM (Non-Conforming Mode) devices. NCM devices are USB devices that do not conform to the standard USB CDC class specifications.

**Supported Devices:**

- Dell branded MBM devices
- Toshiba branded MBM devices
- Huawei devices
- Infineon (now Intel) HSPA Modem platform
- Generic CDC-NCM devices

**Device Matching:**

The driver uses a device table to match supported devices based on the following criteria:

- Vendor ID
- Product ID
- Interface class, subclass, and protocol

**Driver Functionality:**

- Probes USB devices that match the device table.
- Creates a virtual network interface (VCI) for each supported device.
- Provides network connectivity for NCM devices.

**Key Features:**

- Supports NCM devices that require the FLAG_NOARP flag.
- Supports autosuspend and resume operations.
- Disables hub-initiated LPM (Low-Power Mode).

**Module Information:**

- Author: Hans Petter Selasky
- Description: USB CDC NCM host driver
- License: Dual BSD/GPL

**Usage:**

- The driver is automatically loaded when the kernel is booted.
- Supported devices will be automatically recognized and connected.

**Additional Notes:**

- The driver requires the `usbcore` and `cdc-ncm` modules to be loaded.
- The `wwan_info` and `wwan_noarp_info` variables are assumed to be defined elsewhere in the code.
- The `usbnet_probe` and `usbnet_disconnect` functions are part of the USB networking framework.