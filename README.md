# libext | A EXT-File parser library
This library can be used to parse .ext files in your project and extract the necessary informations from it!<br>

## Building 🔨
### Wii U 🎮
`make WIIU && make install` this will compile the library for Wii U and install it to `\opt\devkitpro\wut\usr\`<br>
To use the library add `-lmocha` to `LIBS` and `$(WUT_ROOT)/usr` to `LIBDIRS` in your makefile.<br>
### Windows 🖥️
`make WIN && make install %PATH%` this will compile the library for Windows and install it to `%PATH%`<br>
To use the library just link it as any other library in your Makefile and add it to your Includes<br>

## The EXT-File
The EXT-File is a file type introduced by 4J Studios in Minecraft: Wii U-Edition.
It's essentially the metadata for a Minecraft Wii U World and contains data like:

- World Name
- World Image (standard PNG data)
- Seed
- Hostoptions
- Texturepacks
- Links with images attached to it (Usage ???)
- Deflate Compressed Data (needs more research)

#### World Name - Details
The World Name is stored from 0x00 to 0x32 and before each byte is a null-character, example:<br>
![Hex View](https://github.com/germanvanadium/libext/blob/master/namehex.png?raw=true)<br>
The World Name sections gets ended by two null-characters (this gets used by the library to know when the name ends)<br>

#### World Image - Details
The World Image is stored from 0x100 to a unknown position (depending on the size of the image) and is standard PNG data.<br>
The image has dimensions of 64x64 with a bitdepth of 32<br>
The World Name sections gets ended by three null-characters (this is unprecise tho because the image itself could also contain three null-characters so the library searches for \0\0\0(CHARACTER MAY VARY)(CHARACTER MAY VARY)EXt4J instead to determine the image size)<br>
![Hex View](https://github.com/germanvanadium/libext/blob/master/image_section.png?raw=true)<br>

## Documentation
`EXTFile* loadEXT(const char* filename);` returns a EXTFile pointer if successful otherwise returns a nullptr<br>
`void freeEXT(EXTFile* ext);` closes an EXTFile and cleans everything up<br>

EXTFile class functions:
```
std::string readWorldName((optional) int maxNameSize);` reads the World Name
EXTPNG readWorldImage((optional) int maxImageSize);` reads the World Image
EXTData readData(dataType data, (optional) std::string dataPrefix, (optional) int howLongToRead, (optional) int maxDataLength);` reads Extra Data
```

Typedefs:
```
typedef std::string dataType;
typedef std::vector<char> EXTPNG;
typedef std::vector<char> EXTData;
```

## Example
```
#include <iostream>
#include <libext/ext.hpp>

int main(int argc, char **argv) {
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << " <Filename>" << std::endl;
        return -1;
    }

    EXTFile* file = loadEXT(argv[1]);
    if(!file) {
        std::cout << "File " << argv[1] << " not found!" << std::endl;
        return -1;
    }

    std::cout << "World Name: " << file->readWorldName() << std::endl;
    std::cout << "World Seed: " << file->readData("SEED").data() << std::endl;
    std::cout << "Host Options: " << file->readData("HOSTOPTIONS").data() << std::endl;
    std::cout << "Texturepack: " << file->readData("TEXTUREPACK").data() << std::endl;
    std::cout << "Extradata: " << file->readData("EXTRADATA").data() << std::endl;
    EXTPNG png = file->readWorldImage();
    std::cout << "Image size: " << png.size() << std::endl;
    std::cout << "Image data: " << png.data() << std::endl;

    freeEXT(file);
    return 0;
}
```

## Credits
[germanvanadium](https://github.com/germanvanadium) - made the library itself<br>
[Maschell](https://github.com/wiiu-env) - I copied the Wii U Makefile from<br>
[Cloncurry](https://www.reddit.com/user/Cloncurry/) and [alfps](https://www.reddit.com/user/alfps/) - on Reddit for troubleshooting
