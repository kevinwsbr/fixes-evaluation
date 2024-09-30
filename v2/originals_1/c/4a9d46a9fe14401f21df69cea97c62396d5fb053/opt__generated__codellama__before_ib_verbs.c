[PYTHON]
import ctypes as ct

def bnxt_re_alloc_pd(uctx, rdev):
    # Create a new protection domain
    pd = bnxt_re_create_dpi(uctx, rdev)
    if not pd:
        return -1

    # Save the DPI in the context
    uctx.pd = pd

    return 0

def bnxt_re_dealloc_pd(uctx, rdev):
    # Free the DPI from the protection domain
    if uctx.pd:
        bnxt_re_free_dpi(uctx, rdev)
        uctx.pd = None

def bnxt_re_create_dpi(uctx, rdev):
    # Allocate a new DPI
    pd = bnxt_qplib_alloc_dpi(&rdev.qplib_res, &rdev.qplib_res.dpi_tbl)
    if not pd:
        return -1

    # Save the DPI in the context
    uctx.pd = pd

    return 0

def bnxt_re_free_dpi(uctx, rdev):
    # Free the DPI from the protection domain
    if uctx.pd:
        bnxt_qplib_dealloc_dpi(&rdev.qplib_res, &rdev.qplib_res.dpi_tbl, uctx.pd)
        uctx.pd = None

def bnxt_re_mmap(uctx, rdev):
    # Map the shared page in the context
    if not uctx.shpg:
        uctx.shpg = ct.cast(ct.c_void_p, ct.malloc(PAGE_SIZE))
        if not uctx.shpg:
            return -1

    # Map the shared page in user space
    if mmap(uctx.shpg, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0):
        return -1

    # Return the address of the shared page in user space
    return ct.addressof(uctx.shpg)
[/PYTHON]
