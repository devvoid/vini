# VINI (Void's INI Parsing Library)
A small, single-header library for reading/writing INI files.

## Usage

```c++
#include <string>
#include "vini.hpp"

int main() {
    //Load INI file from existing file.
    Vini file_one("test.ini");
    
    //Create a blank file; use this to create an INI from scratch
    Vini file_two;

    //Get a value from the INI file.
    //The first argument is the section to search from.
    //The second argument is the key to get content from.
    //The third argument is a default value.
    //If the section or key does not exist, that value will be created in that section or key.
    //In addition, the function will return that default value.
    std::string returned_string = file_two.get("main", "key", "default_value");

    //Sets a value in the INI file.
    //The arguments are all the same as the get function.
    //This function returns nothing.
    //It will also overwrite any existing values in that section/key if one already exists.
    file_two.set("main", "otherkey", "Hello, world!");

    //Write file to disk.
    file_two.save("output.ini");
}
```

Output:
```ini
[main]
key="default_value"
otherkey="Hello, world!"
```

## License

Licensed under either of

 * Apache License, Version 2.0 ([LICENSE-APACHE](LICENSE-APACHE) or http://www.apache.org/licenses/LICENSE-2.0)
 * MIT license ([LICENSE-MIT](LICENSE-MIT) or http://opensource.org/licenses/MIT)

at your option.

### Contribution

Unless you explicitly state otherwise, any contribution intentionally submitted
for inclusion in the work by you, as defined in the Apache-2.0 license, shall be dual licensed as above, without any
additional terms or conditions.

