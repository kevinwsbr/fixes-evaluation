 The code snippet you've provided is a part of an implementation in C that handles various operations related to expressions and their resolution within the context of X Keyboard Extension (XKB). Specifically, it deals with resolving masks and modifiers based on different types of expressions. Here's a breakdown of what each function does:

1. **ExprResolveMaskLookup**: This function is used to resolve an expression that involves bitwise operations such as AND (`&`), OR (`|`), or NOT (`~`). It handles cases where the operation results in a mask, which can be applied to other expressions or values. If the operation is not supported (like multiply or divide), it logs an error and returns false.

2. **ExprResolveMask**: This function is a wrapper for `ExprResolveMaskLookup`, using a simple lookup type by default. It's used when you want to resolve a mask without any specific context beyond basic operations on integers.

3. **ExprResolveModMask**: Similar to `ExprResolveMask`, this function resolves expressions involving modifier masks, but it takes additional parameters for the type of modifier (`mod_type`) and the set of modifiers available (`mods`). It uses a private lookup structure to manage these specifics.

4. **ExprResolveKeySym**: This function attempts to resolve an expression into a keysym (a symbolic representation of a key on the keyboard). If the expression is an identifier, it converts this identifier to a keysym using `xkb_keysym_from_name`. If not, it tries to interpret the value as a number between 0 and 9, which corresponds to ASCII characters '0' through '9'.

5. **ExprResolveMod**: This function is used to resolve expressions into virtual modifier indices. It checks if the expression is an identifier and then uses `XkbModNameToIndex` to find the corresponding index for that name in the provided set of modifiers, considering the type of modifier (`mod_type`).

Each of these functions handles specific cases within a broader system for handling keyboard extensions using XKB. They are crucial for interpreting and manipulating keyboard configurations at runtime or during initialization based on expression rules defined elsewhere in the codebase.