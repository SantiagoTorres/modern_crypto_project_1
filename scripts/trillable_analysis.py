#!/usr/bin/env python
"""
    Billable analysis script

    The idea of this script is to provide the set of possible trillables that
    can be produced out of the existing dictionary 2

    A list of possible trillables is print to the screen to analyse
"""
import string
import sys

def get_beginning_letters(wordlist):
    start = []
    end = []

    for word in wordlist:
        start.append(word[0:2])
        end.append(word[-2:])

    return start, end

def get_trillables_in_middle(wordlist):
    trillables = set()

    for word in wordlist:
        for i in range(0, len(word)-3):
            billable = word[i:i+3]
            trillables.add(billable)

    return trillables

def produce_trillables_from_word_boundaries(start, end):
    trillables = set()
    for letter in end:
        for otherletter in start:
            trillables.add((letter+otherletter)[0:3])
            trillables.add((letter+otherletter)[1:4])

    return trillables
def all_trillables():

    trillables = set()

    for letter in string.ascii_lowercase:
        for otherletter in string.ascii_lowercase:
            for thirdletter in string.ascii_lowercase:
                trillables.add(letter+otherletter+thirdletter)

    return trillables
            
if __name__=='__main__':
    wordlist = []
    with open("include/Dictionary2.txt") as fp:
        for line in fp:
            wordlist.append(line.strip("\n"))


    start, end = get_beginning_letters(wordlist)
    trillables = get_trillables_in_middle(wordlist)
    boundary_trillables = produce_trillables_from_word_boundaries(start,end)
    
    trillables |= boundary_trillables
    all_trillables = all_trillables()

    print("{} trillables in dict 2".format(len(trillables)))
    print("{} boundary trillables in dict 2".format(len(boundary_trillables)))
    print("{}%({}%) of total trillables".format(
        len(trillables)/float(len(all_trillables)),
        len(boundary_trillables)/float(len(all_trillables))))

    trillables_sorted = [x for x in trillables]
    trillables_sorted.sort()

    current_letter = trillables_sorted[0][0]
    offsets = {}
    i = 0
    offsets['a'] = 0
    with open("include/trillables.h", "wt") as fp:
        fp.write("const char[{}][4] TRILLABLES = {{\n".format(len(trillables)))
        for trillable in trillables_sorted:
            trillable_letter = trillable[0]
            
            if trillable_letter != current_letter:
                fp.write("\n\t")
                current_letter = trillable_letter
                offsets[current_letter] = i

            fp.write('"{}", '.format(trillable))
            i += 1

        fp.write("\n\t};")

        fp.write("\n\n")
        fp.write("const int[{}] TRILLABLE_OFFSETS = {{\n".format(
            len(string.ascii_lowercase)))

        for offset in string.ascii_lowercase:
            if offset in offsets:
                fp.write("\t{}, // {}\n".format(offsets[offset], offset))
            else:
                fp.write("\t{}, // {}\n".format(-1, offset))

        fp.write("\t};")

        fp.write("\n\n")
        fp.write("const int[{}] TRILLABLE_OFFSETS_END = {{\n".format(
            len(string.ascii_lowercase)))
    
        carry = 0
        for offset in string.ascii_lowercase[1:]:
            for i in range(0,carry):
                carry -= 1
                fp.write("\t-1,\n")

            if offset in offsets:
                fp.write("\t{},\n".format(offsets[offset]-1))
            else:
                carry += 1

        fp.write("\t{},\n".format(len(trillables)-1))
        fp.write("\t};\n")

