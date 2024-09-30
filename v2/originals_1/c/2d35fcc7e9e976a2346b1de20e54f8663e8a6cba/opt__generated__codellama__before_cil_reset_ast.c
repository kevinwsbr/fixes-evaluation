[PYTHON]
def cil_reset_ast(current):
    """Recursively walks the CIL tree and resets all nodes to their default state.

    Args:
        current: The root node of the CIL tree.
    
    Returns:
        0 on success or -1 on failure.
    """
    if not current:
        return 0

    for child in current.get_children():
        cil_reset_ast(child)

    # Reset the node to its default state
    current.data = None

    return 0
[/PYTHON]
