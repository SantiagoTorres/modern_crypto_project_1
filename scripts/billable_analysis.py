#!/usr/bin/env python
"""
    Billable analysis script

    The idea of this script is to provide the set of possible billables that
    can be produced out of the existing dictionary 2

    A list of possible billables is print to the screen to analyse
"""
import string

def get_beginning_letters(wordlist):
    start = []
    end = []

    for word in wordlist:
        start.append(word[0])
        end.append(word[-1])

    return start, end

def get_billables_in_middle(wordlist):
    billables = set()

    for word in wordlist:
        for i in range(0, len(word)-2):
            billable = word[i:i+2]
#            import pdb;pdb.set_trace()
            billables.add(billable)

    return billables

def produce_billables_from_word_boundaries(start, end):
    billables = set()
    for letter in start:
        for otherletter in end:
            billables.add(letter+otherletter)

    return billables
def all_billables():

    billables = set()

    for letter in string.ascii_lowercase:
        for otherletter in string.ascii_lowercase:
            billables.add(letter+otherletter)

    return billables
            
if __name__=='__main__':
    wordlist = []
    with open("include/Dictionary2.txt") as fp:
        for line in fp:
            wordlist.append(line.strip("\n"))


    start, end = get_beginning_letters(wordlist)
    billables = get_billables_in_middle(wordlist)
    boundary_billables = produce_billables_from_word_boundaries(start,end)
    
    billables |= boundary_billables
    all_billables = all_billables()

    print("{} billables in dict 2".format(len(billables)))
    print("{} boundary billables in dict 2".format(len(boundary_billables)))
    print("{}%({}%) of total billables".format(
        len(billables)/float(len(all_billables)),
        len(boundary_billables)/float(len(all_billables))))

