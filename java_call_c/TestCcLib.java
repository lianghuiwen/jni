/*
1.Java保存的文件名必须与类名一致；
2.如果文件中只有一个类，文件名必须与类名一致；
3.一个Java文件中只能有一个public类；
4.如果文件中不止一个类，文件名必须与public类名一致；
5.如果文件中不止一个类，而且没有public类，文件名可与任一类名一致
*/
public class TestCcLib {
    // 声明native static方法 
    public native static String callC(String str);

    public static void main(String[] args){
    System.out.println("java.library.path: " + System.getProperty("java.library.path"));
        System.loadLibrary("TestCcLib");
        String str = callC("java_string");
        System.out.println("java: " + str);
    }
}

