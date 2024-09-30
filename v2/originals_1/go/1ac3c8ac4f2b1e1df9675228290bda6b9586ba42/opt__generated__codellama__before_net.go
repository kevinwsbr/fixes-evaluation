
[PYTHON]
def handle_neighbors_packet(self, n, pkt):
    req = pkt.data
    nodes = []
    for rn in req.nodes:
        try:
            nn = self.intern_node_from_neighbours(pkt.remote_addr, rn)
            if nn is not None:
                nodes.append(nn)
        except:
            log.debug("invalid neighbour (%s) from %x@%s" % (rn.ip, n.id[:8], pkt.remote_addr))
    # TODO: don't ignore second packet
    if len(nodes) > 0:
        n.pending_neighbours.reply.put(nodes)
        n.pending_neighbours = None
    # Now that this query is done, start the next one.
    n.start_next_query(self)
[/PYTHON]
