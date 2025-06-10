//
//  main.cpp
//  FileToCBytes
//
//
//  Copyright 2024 Michael Obed

/* Includes. */
#include <cstdio>
#include <fstream>
#include <iostream>

int main(int argc, const char* argv[])
{
    char buf[6];
    int byteCtr = 0;
    std::vector<uint8_t> bytes;

    /* Bail out if input file is not given. */
    if(argc < 2)
        return -1;

    /* Open input file. */
    std::fstream f(argv[1], std::ios::in | std::ios::binary);

    /* Read all bytes in. */
    while(!f.eof())
        bytes.push_back(f.get());
    bytes.pop_back();
    f.close();

    /* Create an output file. */
    f.open("./out.txt", std::ios::out);

    /* Usual C-style fluff. */
    f << "uint8_t bytes[" << std::to_string(bytes.size()) << "] = \n{\n\t";

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