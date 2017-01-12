package com.business.rrc.jniencrypt;

/**
 * 创建时间：2017/1/12
 * 编写人： jzk
 * 功能描述
 */

public class Encrypt {
    static {
        System.loadLibrary("native-lib");
    }
    public static native String signature();
    public static native String digest(String content);
}
