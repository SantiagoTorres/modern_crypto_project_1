#!/usr/bin/env python
"""
    minimum_word_prefix.py

    This script takes a wordlist and finds what's the minimum length in it from
    which we can differentiate from each other. In other words, we are trying to find
    the shortest prefix that differentiates a word from each other

    Usage:
        ./minimum_word_prefix.py

    It returns the minimum word prefix length and the dictionary of prefixes to verify such claims.
    It's printed to stdout.
"""
import sys

def minimum_word_prefix(wordlist):

    prefixes = {}
   
    # FIXME: what's with the magic numbers?
    for length in range(1,40):
        for word in wordlist:
            if len(word) >= length:
                
                prefix = word[:length]
                if prefix in prefixes:
                    print("Length {} is not enough...".format(length))
                    prefixes = None
                    break

                prefixes[prefix] = word
            else:
                print("Length exceeded, prefix couldn't be found")
                
                return None

        if prefixes is not None:
            break
        else:
            prefixes = {}

    for prefix in prefixes:
        print("{}->{}".format(prefix, prefixes[prefix]))
        

    print("Prefix length found: {}".format(len(prefix)))

if __name__ == '__main__':
    wordlist = []
    with open(sys.argv[1]) as fp:
        for line in fp:
            wordlist.append(line.strip("\n"))

    minimum_word_prefix(wordlist)
