perfhash
========

perfhash is a [perfect hash table] generator for C++ (And hopefully
later other languages). It's based in part on [GNU gperf]'s internals,
but with a completely different interface and API for the generated
tables. In particular, instead of a static table, it creates hash
table objects so that multiple tables with the same keys can exist in
the same program - one per thread, say.

Building
========

perfhash uses cmake. In the base perfhash directory:

    $ mkdir build
    $ cd build
    $ cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo [OTHER OPTIONS] ../src
    $ cmake --build


This creates an executable named `perfhash` that can be copied whereever.

Usage
=====

Generating tables
-----------------

perfhash takes an input file that is a JSON document whose layout is
described below, and creates source code files containing the
implementation of a perfect hash or set. Usage is simple:

    $ perfhash table_description.json

All options and settings are controlled by the input file.

Using tables
------------

perfhash can create two types of tables, corresponding roughly to
`std::unordered_set` and `std::unordered_map`. The keys are always
strings, the values if present are an arbitrary user-controlled type.

### Sets ###

### Maps ###

Table description file
======================

The JSON file that describes the table to be created. It holds a single JSON object, with the following fields:

### type ###

Can be either `"set"` or `"map"`.

### output ###

Controls the output language, files and language-specific options. The
`"language"` field controls what else is present.

#### C++ output ####

For C++ output, `"language"` can be `"c++17"` or `"c++14"`. Older
versions are not currently supported.

The keys `"source file"` and `"header file"` name the respective
files. `"class"` is used to control the name of the resulting table
type. For maps, `"value type"` is the type of the value.

### Example ###

    { "type": "map",
      "output": {
        "language": "c++14",
        "source file": "foo.cpp",
        "header file": "foo.h".
        "class": "my_map",
        "value type": "int"
        },
      "data": [
        {"key": "dog", "value":"1"},
        {"key": "cat", "value":"2"},
        {"key": "rat", "value":"3"}
        ]
    }

[perfect hash table]: https://en.wikipedia.org/wiki/Perfect_hash_function
[GNU gperf]: https://www.gnu.org/software/gperf/
