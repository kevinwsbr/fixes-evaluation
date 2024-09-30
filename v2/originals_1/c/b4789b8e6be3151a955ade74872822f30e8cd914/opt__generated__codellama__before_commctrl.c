[PYTHON]
import ctypes

class AAC_PCI_INFO(ctypes.Structure):
    _fields_ = [
        ("bus", ctypes.c_uint32),
        ("slot", ctypes.c_uint32)
    ]

def aac_get_pci_info(dev, arg):
    pci_info = AAC_PCI_INFO()

    pci_info.bus = dev.pdev.bus.number
    pci_info.slot = PCI_SLOT(dev.pdev.devfn)

    if copy_to_user(arg, &pci_info, sizeof(AAC_PCI_INFO)):
        dprintk((KERN_DEBUG "aacraid: Could not copy pci info\n"))
        return -EFAULT

    return 0
[/PYTHON]
