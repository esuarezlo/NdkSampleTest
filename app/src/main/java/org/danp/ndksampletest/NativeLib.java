package org.danp.ndksampletest;

public class NativeLib {
    static {
        System.loadLibrary("ndksampletest");
    }

    private JNICallBackInterface jniCallBackInterface;

    public NativeLib(JNICallBackInterface jniCallBackInterface){
        this.jniCallBackInterface = jniCallBackInterface;
    }
    public native String stringFromJNI();

    public native double multiply(double a, double b);

    public native double add(double a, double b);

    public native double passObjToJNI(Person person);

    public native Object findPerson(int id);

    public native void callTheCallBackMethod();

    private void callBack(int data, String stringValue) {
        jniCallBackInterface.callBackEvent(stringValue + " "+String.valueOf(data));
    }
}
