package com.business.rrc.jniencrypt;

import android.text.TextUtils;

import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

/**
 * 创建时间：2017/1/12
 * 编写人： jzk
 * 功能描述
 */

public class Encrypt {

    private static final String PARAM_EQUAL = "=";
    private static final String PARAM_AND = "&";

    static {
        System.loadLibrary("native-lib");
    }

    public static native String signature();

    public static native String digest(String content);

    public static String digest(Map<String, String> contentMap) {
        String content = sortStr(contentMap);
        return digest(content);
    }

    //按照key自然排序，过滤掉value为空的item
    private static String sortStr(Map<String, String> contentMap) {
        if (contentMap == null || contentMap.size() == 0) {
            throw new IllegalArgumentException("data cannot be null or empty");
        }
        Map<String, String> temp = new TreeMap<>();
        temp.putAll(contentMap);
        StringBuffer sb = new StringBuffer();
        Set<Map.Entry<String, String>> entries = temp.entrySet();
        for (Map.Entry<String, String> entry : entries) {
            if (TextUtils.isEmpty(entry.getValue())) {
                continue;
            }
            sb.append(entry.getKey());
            sb.append(PARAM_EQUAL);
            sb.append(entry.getValue());
            sb.append(PARAM_AND);
        }
        return sb.substring(0, sb.length() - 1);
    }
}
