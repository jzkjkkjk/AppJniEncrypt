//
// Created by jzkcan on 2017/1/11.
//

#include <jni.h>
#include <string.h>

static jobject getApplication(JNIEnv *env) {
    jclass localClass = env->FindClass("android/app/ActivityThread");
    if (localClass != NULL) {
        jmethodID getapplication = env->GetStaticMethodID(localClass, "currentApplication",
                                                          "()Landroid/app/Application;");
        if (getapplication != NULL) {
            jobject application = env->CallStaticObjectMethod(localClass, getapplication);
            return application;
        }
        return NULL;
    }
    return NULL;
}

static jstring signature(JNIEnv *env) {
    jobject context = getApplication(env);
    jclass activity = env->GetObjectClass(context);
    // 得到 getPackageManager 方法的 ID
    jmethodID methodID_func = env->GetMethodID(activity, "getPackageManager",
                                               "()Landroid/content/pm/PackageManager;");
    // 获得PackageManager对象
    jobject packageManager = env->CallObjectMethod(context, methodID_func);
    jclass packageManagerclass = env->GetObjectClass(packageManager);
    //得到 getPackageName 方法的 ID
    jmethodID methodID_pack = env->GetMethodID(activity, "getPackageName", "()Ljava/lang/String;");
    //获取包名
    jstring name_str = static_cast<jstring>(env->CallObjectMethod(context, methodID_pack));
    // 得到 getPackageInfo 方法的 ID
    jmethodID methodID_pm = env->GetMethodID(packageManagerclass, "getPackageInfo",
                                             "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    // 获得应用包的信息
    jobject package_info = env->CallObjectMethod(packageManager, methodID_pm, name_str, 64);
    // 获得 PackageInfo 类
    jclass package_infoclass = env->GetObjectClass(package_info);
    // 获得签名数组属性的 ID
    jfieldID fieldID_signatures = env->GetFieldID(package_infoclass, "signatures",
                                                  "[Landroid/content/pm/Signature;");
    // 得到签名数组，待修改
    jobject signatur = env->GetObjectField(package_info, fieldID_signatures);
    jobjectArray signatures = reinterpret_cast<jobjectArray>(signatur);
    // 得到签名
    jobject signature = env->GetObjectArrayElement(signatures, 0);
    // 获得 Signature 类，待修改
    jclass signature_clazz = env->GetObjectClass(signature);
    //获取sign
    jmethodID toCharString = env->GetMethodID(signature_clazz, "toCharsString",
                                              "()Ljava/lang/String;");
    //获取签名字符；或者其他进行验证操作
    jstring signstr = static_cast<jstring>(env->CallObjectMethod(signature, toCharString));

    return signstr;
}
