package com.abc;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.webkit.WebView;

public class Main2Activity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);
        WebView web = (WebView) findViewById(R.id.web);
        web.loadUrl("https://thingspeak.com/channels/506100/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&timescale=60&title=%E6%BA%AB%E5%BA%A6&type=line");
        web.getSettings().setBuiltInZoomControls(true);
        web.getSettings().setJavaScriptEnabled(true);
        web.getSettings().setUseWideViewPort(true);
        web.getSettings().setLoadWithOverviewMode(true);

        WebView web2 = (WebView) findViewById(R.id.web2);
        web2.loadUrl("https://thingspeak.com/channels/506100/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&timescale=30&title=%E6%BF%95%E5%BA%A6&type=line");
        web2.getSettings().setBuiltInZoomControls(true);
        web2.getSettings().setJavaScriptEnabled(true);
        web2.getSettings().setUseWideViewPort(true);
        web2.getSettings().setLoadWithOverviewMode(true);

        WebView web3 = (WebView) findViewById(R.id.web3);
        web3.loadUrl("https://thingspeak.com/channels/506100/charts/3?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&timescale=30&title=%E6%98%93%E7%87%83%E6%B0%A3%E9%AB%94&type=line");
        web3.getSettings().setBuiltInZoomControls(true);
        web3.getSettings().setJavaScriptEnabled(true);
        web3.getSettings().setUseWideViewPort(true);
        web3.getSettings().setLoadWithOverviewMode(true);

    }
}
