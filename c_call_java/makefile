all: class TestJavaLib

class: TestJavaLib.java
	javac TestJavaLib.java

TestJavaLib: TestJavaLib.cc
	g++ -I$(JAVA_PATH)/include -I$(JAVA_PATH)/include/linux -L$(JAVA_PATH)/jre/lib/amd64/server -ljvm TestJavaLib.cc
