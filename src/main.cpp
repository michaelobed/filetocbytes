//
//  main.cpp
//  FileToCBytes
//
//  Copyright 2025 Michael Obed

/* Includes. */
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, const char* argv[])
{
    std::string arrayName = "bytes";
    char buf[6];
    int byteCtr = 0;
    std::vector<uint8_t> bytes;
    std::string inputPath;
    bool isText = false;
    std::string outputPath = "./out.c";
    bool willExtern = false;

    /* Bail out if input file is not given. */
    if(argc < 2)
    {
        std::cout << "Usage: ./filetocbytes [-e] [-t] [-n foo] -i bar.bin [-o baz.c]";
        return -1;
    }

    /* Parse args. */
    for(int i = 1; i < argc; i++)
    {
        /* Textual mode (will append '\0' to bytestream). */
        if(std::string(argv[i]) == "-t")
            isText = true;

        /* Array name (optional, defaults to bytes[]). */
        else if(std::string(argv[i]) == "-n")
            arrayName = argv[i + 1];

        /* Specify extern C linkage. */
        else if(std::string(argv[i]) == "-e")
            willExtern = true;

        /* Input path (required). */
        else if(std::string(argv[i]) == "-i")
            inputPath = argv[i + 1];

        /* Output path (optional, defaults to "./out.c"). */
        else if(std::string(argv[i]) == "-o")
            outputPath = argv[i + 1];
    }

    /* Open input file. */
    std::fstream f(inputPath, std::ios::in | std::ios::binary);

    /* Read all bytes in. */
    while(!f.eof())
        bytes.push_back(f.get());
    bytes.pop_back();
    if(isText)
        bytes.push_back(0x00);
    f.close();

    /* Create an output file. */
    f.open(outputPath, std::ios::out);

    /* Usual C-style fluff. */
    f << "#include <stdint.h>\n\n";
    if(willExtern)
        f << "extern \"C\" ";
    f << "uint8_t " << arrayName << "[" << std::to_string(bytes.size()) << "] = \n{\n\t";

    /* Group bytes into rows of 8 for neatness. */
    for(uint8_t b : bytes)
    {
        if(byteCtr++ > 7)
        {
            byteCtr = 1;
            f << "\n\t";
        }
        snprintf(buf, 6, "0x%02x,", b);
        f << buf;
    }

    /* Terminate and close. */
    f.seekp(-1, f.cur);
    f << "\n};";
    f.close();
}