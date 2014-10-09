/*
 * This file is Copyright Santiago Torres Arias <torresariass@gmail.com> 2014 
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 *
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef DICTIONARY_2_H
#define DICTIONARY_2_H

#include<stdio.h>
#include<strings.h>

#define D2_LONGEST_WORD 15
#define D2_SHORTEST_WORD 4
#define D2_DICTIONARY_LENGTH 200

const int D2_ALPHA_INDEX[] = {
    0, //a
    16, //b
    21, //c
    38, //d
    47, //e
    61, //f
    74, //g
    77, //h
    83, //i
    -1, //j
    -1, //k
    91, //l
    99, //m
    114, //n
    120, //o
    127, //p
    151, //q
    152, //r
    159, //s
    176, //t
    185, //u
    189, //v
    195, //w
    -1, //x
    -1, //y
    199, //z
};

const int D2_ALPHA_INDEX_END[] = {
    16, //a
    21, //b
    38, //c
    47, //d
    61, //e
    74, //f
    77, //g
    83, //h
    91, //i
    -1, //j
    -1, //k
    99, //l
    114, //m
    120, //n
    127, //o
    151, //p
    152, //q
    159, //r
    176, //s
    185, //t
    189, //u
    195, //v
    199, //w
    -1, //x
    -1, //y
    D2_DICTIONARY_LENGTH, //z
};

const char DICTIONARY2[D2_DICTIONARY_LENGTH][D2_LONGEST_WORD + 1] = {
    "abdomen",
    "accolade",
    "acuity",
    "advocate",
    "aesthetic",
    "allure",
    "aloof",
    "amorphous",
    "analogue",
    "anecdote",
    "anticipation",
    "antipathy",
    "apathetic",
    "appointment",
    "approval",
    "attenuate",
    "blackout",
    "bother",
    "bucket",
    "bureaucracy",
    "butter",
    "calibrate",
    "cardinal",
    "caustic",
    "cerebral",
    "chronic",
    "circumvent",
    "class",
    "cliche",
    "coding",
    "collage",
    "computer",
    "congruent",
    "conversation",
    "convolution",
    "cringe",
    "cryptography",
    "cupid",
    "decoy",
    "default",
    "devote",
    "discard",
    "dispatch",
    "disruption",
    "divert",
    "doodle",
    "dynamic",
    "elaborate",
    "eloquent",
    "emerge",
    "endorse",
    "engineering",
    "enhance",
    "enigma",
    "enormous",
    "ensure",
    "epigram",
    "evidence",
    "examination",
    "exorcism",
    "extrinsic",
    "fabricated",
    "facination",
    "farewell",
    "fender",
    "flatter",
    "follow",
    "forehead",
    "forever",
    "fragment",
    "freedom",
    "freedom",
    "furry",
    "futile",
    "goalpost",
    "grail",
    "gravity",
    "haircut",
    "hallow",
    "heterodox",
    "hinder",
    "hounds",
    "hyperbole",
    "important",
    "incredible",
    "incredulously",
    "induction",
    "information",
    "innovate",
    "intellect",
    "interpretation",
    "label",
    "language",
    "latent",
    "lavish",
    "legal",
    "legend",
    "lethal",
    "lucid",
    "machinist",
    "magical",
    "malleable",
    "master",
    "matter",
    "meaning",
    "medicine",
    "mellow",
    "microphone",
    "microscope",
    "minion",
    "modern",
    "modest",
    "moment",
    "monologue",
    "negate",
    "negligence",
    "network",
    "nonstick",
    "nostalgia",
    "novel",
    "obligate",
    "oblique",
    "obsession",
    "obsolete",
    "opaque",
    "operate",
    "opportunity",
    "palpable",
    "palpate",
    "paragon",
    "parody",
    "party",
    "pertain",
    "phenomenon",
    "picture",
    "pluck",
    "poised",
    "poker",
    "portable",
    "potent",
    "pottery",
    "precipitous",
    "preprocessing",
    "privacy",
    "profound",
    "program",
    "prohibitive",
    "protocol",
    "proximate",
    "psychosis",
    "purchase",
    "quote",
    "reconnaissance",
    "remedy",
    "reprehensible",
    "resistance",
    "resonant",
    "restore",
    "robust",
    "sanity",
    "score",
    "security",
    "seminal",
    "skeptical",
    "slake",
    "smoke",
    "software",
    "stipple",
    "stomach",
    "stream",
    "surface",
    "suspect",
    "swirl",
    "sword",
    "symphony",
    "system",
    "tangent",
    "temper",
    "tentative",
    "therapeutic",
    "thermal",
    "thought",
    "torrid",
    "trivial",
    "tuberoid",
    "ultra",
    "undercutting",
    "undermined",
    "underscore",
    "verbose",
    "vertigo",
    "visual",
    "vital",
    "volatile",
    "voltage",
    "waffle",
    "weather",
    "withdraw",
    "worship",
    "zenith",
    };
#endif /* POLYALPHA_DECRYPT_H */
