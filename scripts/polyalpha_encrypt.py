#!/usr/bin/env python
"""
    Polyalpha_encrypt.py

    This program generates a stream of random length out of a wordlist:

    1) select the type of wordlist (dictionary 1 or 2) by using the -two switche, defaults
        to dictionary 1.
    2) Send the keylength by using the -k switch: "-k 20"
    3) The length of the ciphertext is randomized by default but it can be defined with "-L N"
    4) The output ciphertext will be printed to the screen, along with the key, suppres 
        printing the key with -q

    Usage
        ./polyalpha_encrypt.py [-two] [-k N] [-L N] [-q]

"""

import argparse
import random 
import linecache
from string import ascii_lowercase

DICT_1_LOCATION='include/Dictionary1.txt'
DICT_1_LENGTH=150

DICT_2_LOCATION='include/Dictionary2.txt'
DICT_2_LENGTH=200

def build_plaintext_from_dict1(length=None):
    
   line = random.randint(0,DICT_1_LENGTH)
   if length is None:
       length = random.randint(100, 150)

   plaintext = linecache.getline(DICT_1_LOCATION, line)

   return plaintext[:length]



def build_plaintext_from_dict2(length=None):

    plaintext=""
    
    if length is None:
        length = random.randint(100,200)

    while (len(plaintext) < length):
        line = random.randint(0,DICT_2_LENGTH)
        word = linecache.getline(DICT_2_LOCATION, line)
        plaintext += word.strip("\n")
    
    return plaintext[:length]


def generate_polyalphabetic_key(length= None):
    
    key = []

    if length is None:
        length = random.randint(1,40)

    while (len(key) < length):
        character = random.randint(0, len(ascii_lowercase))
        key.append(character)

    return key


def encrypt_polyalphabetically(plaintext, key):
    
    plaintext_length = len(plaintext)
    key_length = len(key)
    ciphertext = ""
    i = 0

    cipher_table = ascii_lowercase*3

    for character in plaintext:
        encrypted_index = cipher_table.index(character)+ len(ascii_lowercase)
        encrypted_index += key[i % key_length]
        i += 1
        ciphertext += (cipher_table[encrypted_index])

    return ciphertext

def print_info(key, ciphertext, quiet=False):
    
    if not quiet:
        print("Key is {}".format(key))
    print("Ciphertext: {}".format(ciphertext))


if __name__=='__main__':
    
    parser = argparse.ArgumentParser(description='Create a ciphertext.')

    parser.add_argument('-k', metavar='k', type=int, nargs='?',
            help='The length of the key', const=10, default=None)
    parser.add_argument('-L', type=int, nargs='?',
            help='The length of the ciphertext', const=150, default=None)
    parser.add_argument('-two', action='store_true', default=False)
    parser.add_argument('-q', action='store_true', default=False)

    args = parser.parse_args()
    cipherlength = args.L
    keylength = args.k
    quiet = args.q

    if args.two:
        plaintext = build_plaintext_from_dict2(cipherlength)
    else:
        plaintext = build_plaintext_from_dict1(cipherlength)

    key = generate_polyalphabetic_key(keylength)

    ciphertext = encrypt_polyalphabetically(plaintext, key)
    print_info(key, ciphertext, quiet)

