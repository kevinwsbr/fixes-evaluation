// Example usage:
struct cil_tree_node *ast;

// Reset the AST
int rc = cil_reset_ast(ast);

if (rc == SEPOL_OK) {
    // AST successfully reset
} else {
    // Error resetting AST
}
