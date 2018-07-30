# PCL
PCL code generation using C++.

Create a PCL code and print text, image and barcode 39. See example: [barcode_test.cpp](barcode_test.cpp). It prints an image, text "TITLE", and two barcodes. The second barcode includes human redable text under the barcode.

See: https://en.wikipedia.org/wiki/Code_39 for more info.

Notes:
* You may have to modify library path /usr/lib/ in the Makefile
* The printer should be set as 'raw' type

```
lpadmin -p printer_name -E -v socket://printer_host:port -m raw
```

* If you turn on debug mode, it replaces Escape character (27) with character '^' to make it human readable. Remember to disable debug.
* Some scanners don't scan single character barcodes. If you are printing a single character barcode, you may have to re-program your scanner. [39 Any Length](39_any_length.png)

* Use ImageMagick to convert files to pcl.

```
-->convert logo.jpg logo.pcl
```

```
-->make
g++ -fPIC -c pcl.cpp -o pcl.o 
g++ -shared  -Wl,-soname,libpcl.so -o libpcl.so pcl.o 
cp libpcl.so /usr/lib/
g++    -c -o barcode_test.o barcode_test.cpp
g++ -o barcode_test  barcode_test.o -L. -lpcl 
```

```
-->./barcode_test
```

* Use hexdump to see output contents

```
-->hexdump -C test
hexdump -C test
00000000  1b 45 1b 2a 70 31 30 30  58 1b 2a 70 31 30 30 59  |.E.*p100X.*p100Y|
00000010  1b 2a 72 33 46 1b 2a 72  32 30 30 73 31 35 30 54  |.*r3F.*r200s150T|
00000020  1b 2a 74 37 35 52 1b 26  6c 30 45 1b 2a 76 36 57  |.*t75R.&l0E.*v6W|
00000030  00 03 00 08 08 08 1b 2a  72 31 41 1b 2a 62 30 59  |.......*r1A.*b0Y|
00000040  1b 2a 62 33 4d 1b 2a 62  36 37 35 57 e0 ff ff ff  |.*b3M.*b675W....|
00000050  ff ff ff ff ff e0 ff ff  ff ff ff ff ff ff e0 ff  |................|
...
00004d50  2b 35 2e 35 48 1b 2a 63  35 2e 35 68 33 30 30 76  |+5.5H.*c5.5h300v|
00004d60  30 50 1b 26 61 2b 35 2e  35 48 1b 2a 63 35 2e 35  |0P.&a+5.5H.*c5.5|
00004d70  68 33 30 30 76 31 50 1b  26 61 2b 35 2e 35 48 1b  |h300v1P.&a+5.5H.|
00004d80  26 66 31 53 1b 26 61 2b  33 37 35 56 2a 1b 26 66  |&f1S.&a+375V*.&f|
00004d90  31 53 1b 26 61 2b 39 39  48 1b 26 61 2b 31 38 37  |1S.&a+99H.&a+187|
00004da0  2e 35 56 1b 45                                    |.5V.E|
00004da5
```
* Finaly you can print

```
-->lpr -P PRINTER_NAME test
```

