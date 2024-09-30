int main() {
    int n = 10; // The number of actions in your SWF file.
    char *actions = "ABCDEFGHIJ"; // A string containing your SWF file's actions.
    
    // Decompile the actions and print them to standard output.
    decompile5Action(n, actions);
    
    return 0;
}
