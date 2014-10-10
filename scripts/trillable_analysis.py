#!/usr/bin/env python
"""
    Billable analysis script

    The idea of this script is to provide the set of possible trillables that
    can be produced out of the existing dictionary 2

    A list of possible trillables is print to the screen to analyse
"""
import string

def get_beginning_letters(wordlist):
    start = []
    end = []

    for word in wordlist:
        start.append(word[0:2])
        end.append(word[-2:0])

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
    for letter in start:
        for otherletter in end:
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

