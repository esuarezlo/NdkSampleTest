#include <jni.h>
#include <string>
#include "Calculator.h"

using namespace std;

extern "C" JNIEXPORT jstring JNICALL
Java_org_danp_ndksampletest_NativeLib_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_org_danp_ndksampletest_NativeLib_add(
        JNIEnv *env,
        jobject,
        jdouble a,
        jdouble b
) {
    Calculator cal;
    double c = cal.add(a, b);
    return c;
}
extern "C"
JNIEXPORT jdouble JNICALL
Java_org_danp_ndksampletest_NativeLib_multiply(JNIEnv *env, jobject thiz, jdouble a,
                                                  jdouble b) {
    return a * b;
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_org_danp_ndksampletest_NativeLib_passObjToJNI(JNIEnv *env, jobject thiz, jobject jperson) {

    // Get jclass of the object
    jclass sampleDataOBJClass = env->GetObjectClass(jperson);

    // Get data field IDs of the object
    jfieldID personIdField = env->GetFieldID(sampleDataOBJClass, "id", "I");
    jfieldID personSalaryField = env->GetFieldID(sampleDataOBJClass, "salary", "D");
    jfieldID personNameField = env->GetFieldID(sampleDataOBJClass, "name", "Ljava/lang/String;");

    jdouble salary = env->GetDoubleField(jperson, personSalaryField);
    salary = salary + salary * 0.20;

    return salary;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_danp_ndksampletest_NativeLib_findPerson(JNIEnv *env, jobject thiz, jint id) {

    // Create a jclass from actual Java object class path
    jclass sampleObjClass = env->FindClass("org/danp/ndksampletest/Person");
    jmethodID methodId = env->GetMethodID(sampleObjClass, "<init>", "()V");
    jobject sampleObj = env->NewObject(sampleObjClass, methodId);

    //Update fields of object
    const char *successString = "Jenny";
//    jfieldID sampStringField = env->GetFieldID(sampleObjClass, "name",
//                                               "Ljava/lang/String;");
//    jfieldID sampStringField = env->GetFieldID(sampleObjClass, "name",
//                                               "Ljava/lang/String;");
//    jfieldID sampStringField = env->GetFieldID(sampleObjClass, "name",
//                                               "Ljava/lang/String;");

    jfieldID personIdField = env->GetFieldID(sampleObjClass, "id", "I");
    jfieldID personSalaryField = env->GetFieldID(sampleObjClass, "salary", "D");
    jfieldID personNameField = env->GetFieldID(sampleObjClass, "name", "Ljava/lang/String;");

    env->SetObjectField(sampleObj, personNameField, env->NewStringUTF(successString));
    env->SetIntField(sampleObj, personIdField, 20);
    env->SetDoubleField(sampleObj, personSalaryField, 200.0);

    return sampleObj;

}

extern "C"
JNIEXPORT void JNICALL
Java_org_danp_ndksampletest_NativeLib_callTheCallBackMethod(JNIEnv *env,
                                                               jobject instance) {

    // Get jclass of the instance
    jclass jClassInstance = env->GetObjectClass(instance);

    // Get java callback method
    jmethodID callBackJava = env->GetMethodID(jClassInstance, "callBack", "(ILjava/lang/String;)V");

    // If method not found
    if (NULL == callBackJava) return;

    // create string data to pass
    const char *successString = "SUCCESS";

    // integer value to pass
    int data = 10;

    // Call back Java method with parameters
    env->CallVoidMethod(instance, callBackJava, data, env->NewStringUTF(successString));
}

