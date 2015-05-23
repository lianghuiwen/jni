# jni
just a test use jni

java调用c++：  
1、编写java文件(TestCcLib.java)，声明native static方法  
2、编译java文件：javac TestCcLib.java
3、生成c++头文件：javah -jni TestCcLib
4、用cpp实现这个头文件：TestCcLib.cc
5、编译生成动态库：g++ -shared -fPIC -I$(JAVA_PATH)/include -I$(JAVA_PATH)/include/linux -o libTestCcLib.so TestCcLib.cc
6、执行java程序：java -Djava.library.path=. TestCcLib

c++调用java：
1、编写java文件(TestJavaLib.java)
2、编译java文件：javac TestJavaLib.java
3、查看java签名：javap -s -p TestJavaLib
4、编写c++文件：TestJavaLib.cc，调用java方法
5、编译c++程序：g++ -I$(JAVA_PATH)/include -I$(JAVA_PATH)/include/linux -L$(JAVA_PATH)/jre/lib/amd64/server -ljvm TestJavaLib.cc
6、运行时环境变量：export LD_LIBARRY_PATH=$(JAVA_PATH)/jre/lib/amd64/server
