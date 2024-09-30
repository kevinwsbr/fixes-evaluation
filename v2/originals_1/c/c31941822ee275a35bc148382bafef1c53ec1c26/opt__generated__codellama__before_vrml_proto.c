[PYTHON]
def gf_node_proto_is_sftime_offset(node, field):
    if node.sgprivate.tag != TAG_ProtoNode:
        return 0

    inst = (GF_ProtoInstance *)node

    # check if the field is a startTime or stopTime field
    if not stricmp(field.name, "startTime") or not stricmp(field.name, "stopTime"):
        return 1

    i = 0
    r = None
    while r is None:
        r = (GF_Route*)gf_list_enum(inst.proto_interface.sub_graph.Routes, &i)
        if r is not None and r.IS_route and (r.FromNode == node or (r.FromField.fieldIndex == field.fieldIndex and r.ToNode != node)) and r.ToNode.sgprivate.tag == TAG_ProtoNode:
            return gf_node_proto_is_sftime_offset(r.ToNode, &r.ToField)
    return 0
[/PYTHON]
