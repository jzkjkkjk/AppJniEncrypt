#include "signature.cpp"
#include "digest.cpp"

static JNINativeMethod gMethods[] = {
        {"signature", "()Ljava/lang/String;",                   (jstring *) signature},
        {"digest",           "(Ljava/lang/String;)Ljava/lang/String;", (jstring *) digest}
};

static int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *gMethods,
                                 int numMethods) {
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

//注册类
static int registerNatives(JNIEnv *env) {
    const char *kClassName = "com/business/rrc/jniencrypt/Encrypt";
    return registerNativeMethods(env, kClassName, gMethods, sizeof(gMethods) / sizeof(gMethods[0]));
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = -1;

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return result;
    }
    if (!registerNatives(env)) {//注册
        return result;
    }
    //成功
    result = JNI_VERSION_1_4;
    return result;
}


