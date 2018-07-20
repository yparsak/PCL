# PCL
PCL code generation using C++.

Create a PCL code and print text, image and barcode 39. See example: barcode_test.cpp. It prints text "TITLE" and two barcodes. The second barcode includes human redable text under the barcode.

See: https://en.wikipedia.org/wiki/Code_39 for more info.

Notes:
* You may have to modify library path /usr/lib/ in the Makefile
* The printer should be set as 'raw' type

```
lpadmin -p printer_name -E -v socket://printer_host:port -m raw
```
* Some scanners don't scan single character barcodes. If you are printing a single character barcode, you may have to re-program your scanner.

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

```
-->hexdump -C test
hexdump -C test
00000000  1b 45 1b 2a 70 33 32 30  58 1b 2a 70 31 32 30 59  |.E.*p320X.*p120Y|
00000010  1b 28 73 31 70 31 32 76  73 33 62 34 31 30 31 54  |.(s1p12vs3b4101T|
00000020  54 49 54 4c 45 1b 28 73  31 70 31 32 76 73 30 62  |TITLE.(s1p12vs0b|
00000030  34 31 30 31 54 1b 2a 70  32 30 30 58 1b 2a 70 32  |4101T.*p200X.*p2|
...
000005b0  33 30 30 76 30 50 1b 26  61 2b 35 2e 35 48 1b 2a  |300v0P.&a+5.5H.*|
000005c0  63 35 2e 35 68 33 30 30  76 31 50 1b 26 61 2b 35  |c5.5h300v1P.&a+5|
000005d0  2e 35 48 1b 26 66 31 53  1b 26 61 2b 33 37 35 56  |.5H.&f1S.&a+375V|
000005e0  2a 1b 26 66 31 53 1b 26  61 2b 38 38 48 1b 26 61  |*.&f1S.&a+88H.&a|
000005f0  2b 31 38 37 2e 35 56 1b  45                       |+187.5V.E|
000005f9
```

```
-->lpr -P PRINTER_NAME test
```

