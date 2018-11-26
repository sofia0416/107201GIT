package com.abc;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;

import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class MainActivity extends AppCompatActivity {

    private TextView mtextView, mtextView2, mtextView3, mtextView6, mtextView7, mtextView8,
            mtextView9, mtextView10, mtextView4, mtextView11, mtextView12;
    private Button mbtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mbtn = (Button) findViewById(R.id.btn);
        mtextView = (TextView) findViewById(R.id.textView);
        mtextView2 = (TextView) findViewById(R.id.textView2);
        mtextView3 = (TextView) findViewById(R.id.textView3);
        mtextView6 = (TextView) findViewById(R.id.textView6);
        mtextView7 = (TextView) findViewById(R.id.textView7);
        mtextView8 = (TextView) findViewById(R.id.textView8);
        mtextView9 = (TextView) findViewById(R.id.textView9);
        mtextView10 = (TextView) findViewById(R.id.textView10);
        mtextView4 = (TextView) findViewById(R.id.textView4);
        mtextView11 = (TextView) findViewById(R.id.textView11);
        mtextView12 = (TextView) findViewById(R.id.textView12);

        mbtn.setOnClickListener(btnOnClick);
        Button nextPageBtn = (Button)findViewById(R.id.next);
        nextPageBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                intent.setClass(MainActivity.this , Main2Activity.class);
                startActivity(intent);
            }});
    }


    private View.OnClickListener btnOnClick = new View.OnClickListener() {

        @Override
        public void onClick(View v) {

            mtextView.setText("");

            new SimpleTask().execute("https://api.thingspeak.com/channels/506100/feeds/last.json?key=BF7HJHRF5JYA8QXF");

        }
    };

    private class SimpleTask extends AsyncTask<String, Void, String> {

        @Override
        protected void onPreExecute() {
            // Create Show ProgressBar
        }

        protected String doInBackground(String... urls) {
            String result = "";
            try {

                HttpGet httpGet = new HttpGet(urls[0]);
                HttpClient client = new DefaultHttpClient();

                HttpResponse response = client.execute(httpGet);

                int statusCode = response.getStatusLine().getStatusCode();

                if (statusCode == 200) {
                    InputStream inputStream = response.getEntity().getContent();
                    BufferedReader reader = new BufferedReader
                            (new InputStreamReader(inputStream));
                    String line;
                    while ((line = reader.readLine()) != null) {
                        result += line;
                    }
                }

            } catch (ClientProtocolException e) {

            } catch (IOException e) {

            }
            return result;
        }

        protected void onPostExecute(String result) {

            String resultext1 = "";
            String resultext2 = "";
            String resultext3 = "";
            String resultext4 = "";
            String resultext5 = "";
            String resultext6 = "";
            String resultext7 = "";
            String resultext8 = "";
            String tempsug = "";
            String pm2now = "";
            String pm2sug = "";

            try {
                JSONObject jsonObject = new JSONObject(result);
                String time = jsonObject.getString("created_at");
                String id = jsonObject.getString("entry_id");
                int temp = jsonObject.getInt("field1");
                int hum = jsonObject.getInt("field2");
                int lpg = jsonObject.getInt("field3");
                int co = jsonObject.getInt("field4");
                int smk = jsonObject.getInt("field5");
                int pm1 = jsonObject.getInt("field6");
                int pm2 = jsonObject.getInt("field7");
                int pm10 = jsonObject.getInt("field8");
                resultext1 += "溫度" + "\n" + temp + " °C" ;
                resultext2 += "濕度" + "\n" + hum + " %" ;
                resultext3 += "液化石油氣" + "\n" + lpg + " ppm" ;
                resultext4 += "一氧化碳" + "\n" + co + " ppm" ;
                resultext5 += "煙霧" + "\n" + smk + " ppm" ;
                resultext6 += "PM1" + "\n" + pm1 + " μg/m3" ;
                resultext7 += "PM2.5" + "\n" + pm2 + " μg/m3" ;
                resultext8 += "PM10" + "\n" + pm10 + " μg/m3";
                pm2now += "現在PM2.5為" + pm2 + " μg/m3" + " ：";
                if (temp >= 28){
                    tempsug += "現在溫度" + temp + " °C" + " ：" + "目前溫度過高 ，建議開冷氣" + "\n";
                } else if(temp > 18){
                    tempsug += "現在溫度" + temp + " °C" + " ：" + "目前溫度過高 ，建議開冷氣" + "\n";
                } else {
                    tempsug += "現在溫度" + temp + " °C" + " ：" + "溫度過低 ，建議開暖氣" + "\n";
                }

                if (pm2 > 71){
                    pm2sug += "PM2.5濃度過高 ，建議不要外出" + "\n";
                } else if(pm2 > 54){
                    pm2sug += "PM2.5濃度偏高 ，建議避免外出" + "\n";
                } else if(pm2 > 36){
                    pm2sug += "PM2.5濃度中 ，可正常外出 ，敏感族群建議避免外出" + "\n";
                } else {
                    pm2sug += "PM2.5濃度低 ，可正常外出" + "\n";
                }
            } catch (JSONException e) {
                e.printStackTrace();
            }
            mtextView.setText(resultext1);
            mtextView2.setText(resultext2);
            mtextView3.setText(resultext3);
            mtextView6.setText(resultext4);
            mtextView7.setText(resultext5);
            mtextView8.setText(resultext6);
            mtextView9.setText(resultext7);
            mtextView10.setText(resultext8);
            mtextView4.setText(tempsug);
            mtextView11.setText(pm2now);
            mtextView12.setText(pm2sug);
        }
    }
}

