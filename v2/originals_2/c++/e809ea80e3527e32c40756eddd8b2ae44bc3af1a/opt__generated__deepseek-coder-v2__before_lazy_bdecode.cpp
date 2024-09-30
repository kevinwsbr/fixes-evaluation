#include <iostream>
#include "your_bdecode_library.h" // Adjust the include path accordingly

int main() {
    std::string bencodedData = "d4:namei123e5:value42e"; // Example bencoded string
    try {
        lazy_entry e;
        parse(bencodedData, e); // Assuming there's a parse function to convert the string into a lazy_entry object
        std::string result = print_entry(e);
        std::cout << "Parsed Bencoded Data: " << result << std::endl;
    } catch (const bdecode_error& err) {
        std::cerr << "Bdecode error: " << err.what() << std::endl;
    }
    return 0;
}
