//
// Created by jiazhenkai on 17/1/11.
//
#include <jni.h>
#include <string.h>

static void byteToHexStr(const unsigned char *source, char *dest, int sourceLen) {//字母大写

    unsigned char highByte, lowByte;

    for (short i = 0; i < sourceLen; i++) {
        highByte = source[i] >> 4;
        lowByte = source[i] & 0x0f;

        highByte += 0x30;

        if (highByte > 0x39)
            dest[i * 2] = highByte + 0x07;
        else
            dest[i * 2] = highByte;

        lowByte += 0x30;
        if (lowByte > 0x39)
            dest[i * 2 + 1] = lowByte + 0x07;
        else
            dest[i * 2 + 1] = lowByte;
    }
    return;
}

static jbyteArray string2ByteArray(JNIEnv *env, jstring str) {

    jmethodID mid;

    jclass clazz = env->FindClass("java/lang/String");

    //拼接key
    mid = env->GetMethodID(clazz, "concat", "(Ljava/lang/String;)Ljava/lang/String;");
    jstring key = env->NewStringUTF("&key=r2e0nd9r9fe79nf8e8484ec808264538");
    jstring target = (jstring) env->CallObjectMethod(str, mid, key);

    mid = env->GetMethodID(clazz, "getBytes", "(Ljava/lang/String;)[B");

    jstring jencode = env->NewStringUTF("utf-8");

    jbyteArray array = (jbyteArray) env->CallObjectMethod(target, mid, jencode);

    return array;
}

static jstring digest(JNIEnv *env, jobject obj, jstring content) {


    jmethodID tem_method;

    jclass class_MessageDigest = env->FindClass("java/security/MessageDigest");

    tem_method = env->GetStaticMethodID(class_MessageDigest, "getInstance",
                                        "(Ljava/lang/String;)Ljava/security/MessageDigest;");

    jobject obj_md5 = env->CallStaticObjectMethod(class_MessageDigest, tem_method,
                                                  env->NewStringUTF("md5"));

    jbyteArray contentByteArray = string2ByteArray(env, content);
    tem_method = env->GetMethodID(class_MessageDigest, "digest", "([B)[B");
    jbyteArray obj_array_sign = static_cast<jbyteArray>(env->CallObjectMethod(obj_md5,
                                                                              tem_method,
                                                                              contentByteArray));

    jsize int_array_length = env->GetArrayLength(obj_array_sign);
    jbyte *byte_array_elements = env->GetByteArrayElements(obj_array_sign, JNI_FALSE);

    char *char_result = (char *) malloc(int_array_length * 2 + 1);
    // 开始没有+1，在有的情况下会越界产生问题，还是在后面补上\0比较好
    // 将byte数组转换成16进制字符串，发现这里不用强转，jbyte和unsigned char应该字节数是一样的

    byteToHexStr((const unsigned char *) byte_array_elements, char_result, int_array_length);

    *(char_result + int_array_length * 2) = '\0';// 在末尾补\0
    jstring string_result = env->NewStringUTF(char_result);
    // release
    env->ReleaseByteArrayElements(obj_array_sign, byte_array_elements, JNI_ABORT);
    // 释放指针使用free
    free(char_result);
    return string_result;
}

