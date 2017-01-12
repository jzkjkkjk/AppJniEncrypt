package com.business.rrc.appjniencrypt;

import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import com.business.rrc.jniencrypt.Encrypt;
import java.util.HashMap;
import java.util.Map;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void testJni(View view) {
        String sign1 = Encrypt.signature();
        String sign2 = getSingInfo();
        Log.e("test1", sign1.equals(sign2) + "");

        String md51 = Md5Algorithm.getInstance().sign(sign1, "r2e0nd9r9fe79nf8e8484ec808264538").toUpperCase();
        String md52 = Encrypt.digest(sign2);
        Log.e("test1", md51);
        Log.e("test1", md52);
        Log.e("test1", md51.equals(md52) + "");

        Map<String, String> map = new HashMap<>();
        map.put("sdf", "2345");
        map.put("ahn", "234");
        map.put("sg", "567");
        map.put("iuyh", "7867");
        map.put("awefwrev", "3254");
        map.put("vefvaeve", "787");
        map.put("VEVE", "2345353");
        Log.e("test1", Encrypt.digest(map));
    }


    public String getSingInfo() {
        try {
            PackageInfo packageInfo = getPackageManager().getPackageInfo(
                    getPackageName(), PackageManager.GET_SIGNATURES);
            Signature[] signs = packageInfo.signatures;
            Signature sign = signs[0];
            return sign.toCharsString();
        } catch (Exception e) {
            e.printStackTrace();
            return "empty";
        }
    }
}
