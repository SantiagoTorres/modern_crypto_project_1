#!/usr/bin/env python
"""
    build_offset_table.py

    given a wordlist, sorts and builds a C formated constant that
    points to the first element in the wordlist that contains that alphabetic character.

    For example:
        Wordlist contains:
            Abc
            abba
            abde
            batman
            carrie
            lemon
    The generated constants would be:
        DICTIONARY_OFFSETS = {
            0, // A
            3, // B
            4, // C
            -1,// D
            ...
            4, // L
            ...
            -1, // Z
            };

    Usage:
        ./build_offset_table.py [wordlist]

    table will be printed to stdout
"""
import sys
import string

def build_offset_table(dictionary_file):

    wordlist = []
    offsets = {}

    with open(dictionary_file) as fp:
        for line in fp:
            if len(line) > 1:
                wordlist.append(line)

    wordlist.sort()
    
    i = 0
    print("const int xxxxxx[] = {")

    for character in string.ascii_lowercase:

        if wordlist[i].startswith(character):
            print("\t{}, //{}".format(i, character))
        else:
            print("\t{}, //{}".format(-1, character))
            continue

        current_word = wordlist[i]
        while (current_word.startswith(character) is True):
            i += 1
            try:
                current_word = wordlist[i]
            except IndexError:
                i -= 1; # we are probably done, let's end gracefully
                break

    print("};")

if __name__=='__main__':
    build_offset_table(sys.argv[1])



