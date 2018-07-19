
CXX = g++

barcode_test: libpcl.so barcode_test.o
	$(CXX) -o barcode_test  barcode_test.o -L. -lpcl 

libpcl.so: pcl.cpp
	$(CXX) -fPIC -c pcl.cpp -o pcl.o 
	$(CXX) -shared  -Wl,-soname,libpcl.so -o libpcl.so pcl.o 
	cp libpcl.so /usr/lib/
clean:
	rm *.o *.so
