 /*
    * Read a WPG2 document.
    */
    case '2': {
        /*
         * Start reading the file body, which contains records of type
         * RecordStart and RecordEnd.  The end record marks the end of the
         * file.  Each record may consist of any number of objects.  The file
         * is parsed in a hierarchical way: an object may be embedded within
         * another one, but it's properties are only defined for that particular
         * object and its children.
         */
        while (1) {
            WPG2RecordType Rec2;
            if (!ReadWPG2Record(&Rec2, image)) break;

            switch(Rec2.RecordID) {
                case RECORD_START: {
                    /*
                     * We have found a new object, save the current state and push it to the stack of
                     * saved objects so we can restore it after processing this one.
                     */
                    WPG2State State2;
                    CopyWPG2State(&state, &State2);
                    stack = (WPG2StateStack *)push_stack(stack, &State2);
                    break;
                }

                case RECORD_END: {
                    /*
                     * This object is finished.  Restore the previous state and pop it from the stack.
                     */
                    WPG2StateStack *entry = (WPG2StateStack *)pop_stack(stack);
                    if (!entry) ThrowReaderException(CorruptImageError, "Unmatched record end");
                    CopyWPG2State(&entry->state, &state);
                    entry = destroy_wpg_state_stack(entry);
                    break;
                }

                default: {
                    /*
                     * Parse the object according to its type.
                     */
                    WPG2Object *object = ReadWPG2Object(&Rec2, image, image_info, exception);
                    if (object) {
                        stack = (WPG2StateStack *)push_stack(stack, &state);
                        ProcessWPG2Object(object, image, image_info, exception);
                        object = DestroyWPG2Object(object);
                        WPG2StateStack *entry = (WPG2StateStack *)pop_stack(stack);
                        if (!entry) ThrowReaderException(CorruptImageError, "Unmatched record end");
                        CopyWPG2State(&entry->state, &state);
                        entry = destroy_wpg_state_stack(entry);
                    }
                }
            }