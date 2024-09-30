**button_set_mask() Function:**

The `button_set_mask()` function sets the event masks for a given button device. It performs the following steps:

- Creates bitsets for keys, switches, and a mask.
- Sets the event mask for EV_SYN events.
- Sets the event mask for EV_KEY events, including keys like POWER, POWER2, SLEEP, and SUSPEND.
- Sets the event mask for EV_SW events, including switches like LID and DOCK.

**button_open() Function:**

The `button_open()` function opens a system button device and sets up the necessary event handling. It performs the following steps:

- Opens the device at `/dev/input/<button_name>`.
- Checks if the device is suitable for button monitoring.
- Sets the event mask for the device.
- Adds an event source to the event loop for handling button events.
- Logs the device name and status.

**button_check_switches() Function:**

The `button_check_switches()` function checks the current state of the LID and DOCK switches on a button device. It performs the following steps:

- Reads the switch states using EVIOCGSW ioctl.
- Updates the `lid_closed` and `docked` flags based on the switch states.
- Installs an event source if the LID switch is closed.

**Purpose:**

These functions are part of a system button monitoring system. They are responsible for setting up event handling for button devices, checking switch states, and triggering events based on button presses and lid closures.

**Key Features:**

- Event handling for key and switch events.
- Mask setting for event filtering.
- LID and DOCK switch monitoring.
- Event source creation for handling button events.