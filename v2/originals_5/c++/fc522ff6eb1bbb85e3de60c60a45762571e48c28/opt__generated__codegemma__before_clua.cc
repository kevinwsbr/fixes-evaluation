int main() {
    // Create a new Lua state
    lua_State* L = lua_newstate();

    // Load and execute a Lua file
    int status = luaL_dofile(L, "myfile.lua");

    // Check for errors
    if (status != 0) {
        // Handle error
        return 1;
    }

    // Create a Lua object
    lua_datum myObject(L, -1);

    // Check object type
    if (myObject.is_table()) {
        // Access object properties
        // ...
    }

    // Cleanup
    lua_close(L);

    return 0;
}
