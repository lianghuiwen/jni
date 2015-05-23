all: class lib run

class: TestCcLib.java
	javac TestCcLib.java

lib: TestCcLib.cc
	g++ -shared -fPIC -I$(JAVA_PATH)/include -I$(JAVA_PATH)/include/linux -o libTestCcLib.so TestCcLib.cc

run:
	java -Djava.library.path=. TestCcLib
