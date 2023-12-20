package org.qtproject.qt5.android.bindings;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Color;
import android.webkit.JsResult;
import android.webkit.WebChromeClient;
import android.webkit.WebView;
import android.webkit.WebViewClient;


public class MyWebView extends WebView {

    public MyWebView(Context context) {

        super(context); 
        init();

        // TODO 自动生成的构造函数存根
    }



    @SuppressLint("SetJavaScriptEnabled")
    public void  init() {
        this.getSettings().setJavaScriptEnabled(true);
        this.getSettings().setJavaScriptCanOpenWindowsAutomatically(true);
            //否则不会执行js的Alert
        this.setWebChromeClient(new WebChromeClient()
            {   public boolean onJsAlert(WebView view, String url, String message,
                        JsResult result)
                {
                    //Auto-generated method stub
                    return super.onJsAlert(view, url, message, result);
                }

            });
        this.setWebViewClient(new WebViewClient());
        this.setBackgroundColor(Color.BLACK); 

        this.addJavascriptInterface(new Cjavascript(), "obj");
    }
}