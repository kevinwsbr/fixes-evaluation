[PYTHON]
def sas_ex_revalidate_domain(port_dev):
    res = 0
    dev = None

    res = sas_find_bcast_dev(port_dev, &dev)
    while res == 0 and dev:
        ex = &dev.ex_dev
        i = 0

        do:
            phy_id = -1
            res = sas_find_bcast_phy(dev, &phy_id, i, True)
            if phy_id == -1:
                break
            res = sas_rediscover(dev, phy_id)
            i = phy_id + 1
        while i < ex.num_phys

        dev = None
        res = sas_find_bcast_dev(port_dev, &dev)
    return res
[/PYTHON]
