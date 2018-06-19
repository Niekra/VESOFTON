package com.placeholder.isnoezel;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.os.SystemClock;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.UUID;

import static android.content.ContentValues.TAG;
import static java.lang.Boolean.FALSE;
import static java.lang.Boolean.TRUE;
import static java.lang.Boolean.valueOf;

public class BedieningsPaneel extends AppCompatActivity {
    public static final int MESSAGE_READ = 2;

    private BluetoothAdapter mBluetoothAdapter = null;
    private BluetoothSocket mBluetoothSocket = null;
    private BluetoothDevice mBluetoothDevice = null;
    private OutputStream mBluetoothStream = null;
    private ConnectedThread ct;

    private Button nDevice, previous, next, play, pause;
    private Spinner uSpinner, mSpinner, aMSpinner, lModus;
    private SeekBar mBar, vSeekBar, lSeekBar;
    private Switch mSwitch, vSwitch, lSwitch, eSwitch;
    private EditText mMinutes, mSeconds, sInput, mInput, vDuration, vInterval, eDuration, eInterval;

    private boolean userStatus = false;
    private boolean onItemInterrupt = true;
    public String MAC_Address;

    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bedienings_paneel);

        nDevice = (Button) findViewById(R.id.change_device_button);
        uSpinner = (Spinner) findViewById(R.id.user_spinner);
        mSpinner = (Spinner) findViewById(R.id.mode_spinner);
        mMinutes = (EditText) findViewById(R.id.modus_minutes);
        mSeconds = (EditText) findViewById(R.id.modus_seconds);
        mBar = (SeekBar) findViewById(R.id.volume_slider);
        mSwitch = (Switch) findViewById((R.id.music_onoff));
        aMSpinner = (Spinner) findViewById(R.id.aModus_spinner);
        sInput = (EditText) findViewById(R.id.song_input);
        mInput = (EditText) findViewById(R.id.map_input);
        previous = (Button) findViewById(R.id.previous_button);
        next = (Button) findViewById(R.id.next_button);
        play = (Button) findViewById(R.id.play_button);
        pause = (Button) findViewById(R.id.pause_button);
        vSeekBar = (SeekBar) findViewById(R.id.vibration_slider);
        vSwitch = (Switch) findViewById((R.id.vib_onoff));
        vDuration = (EditText) findViewById(R.id.vib_duration);
        vInterval = (EditText) findViewById(R.id.vib_interval);
        lSeekBar = (SeekBar) findViewById(R.id.light_slider);
        lSwitch = (Switch) findViewById((R.id.light_onoff));
        lModus = (Spinner) findViewById(R.id.light_modus_spinner);
        eSwitch = (Switch) findViewById((R.id.eyes_onoff));
        eDuration = (EditText) findViewById(R.id.eye_duration);
        eInterval = (EditText) findViewById(R.id.eye_interval);

        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        mBluetoothAdapter.cancelDiscovery();

        Intent intent = getIntent();
        MAC_Address = intent.getStringExtra("address");

        try {
            mBluetoothDevice = mBluetoothAdapter.getRemoteDevice(MAC_Address);

            ct = new ConnectedThread(mBluetoothDevice, mHandler);
        }catch(Exception e){
            this.finish();
        }

        try {
            ct.start();
        }catch(Exception e1){
            this.finish();
        }

        ct.write("ul0!");


        /*
        mMinutes.setText("2");
        mSeconds.setText("30");
        sInput.setText("1");
        mInput.setText("1");
        vDuration.setText("5");
        vInterval.setText("1");
        eDuration.setText("5");
        eInterval.setText("1");
        */
        setupInterrupts();


    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        try {
            ct.cancel();
        }catch (Exception e2){}
        finish();
    }

    Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
        byte[] writeBuf = (byte[]) msg.obj;
        //int begin = (int)msg.arg1;
        //int end = (int)msg.arg2;

        String writeMessage = new String(writeBuf);
        Toast.makeText(getBaseContext(), writeMessage, Toast.LENGTH_SHORT).show();
        //
        userStatus = false; //disable interrupts.

        writeMessage = writeMessage.substring(0, writeMessage.length() - 1);
        String[] output = writeMessage.split(",");

        int minutes = Integer.parseInt(output[2]) /1000 / 60;
        int seconds = Integer.parseInt(output[2]) / 1000 - (60*minutes);

        mSpinner.setSelection(Integer.parseInt(output[3]), false);
        mMinutes.setText(String.valueOf(minutes));
        mSeconds.setText(String.valueOf(seconds));
        mBar.setProgress(Integer.parseInt(output[15]));
        mSwitch.setChecked((Integer.parseInt(output[16]) != 0));
        aMSpinner.setSelection(Integer.parseInt(output[17]));
        sInput.setText(output[1]);
        mInput.setText(output[0]);
        vSeekBar.setProgress(Integer.parseInt(output[5]));
        vSwitch.setChecked((Integer.parseInt(output[4]) != 0));
        vDuration.setText(String.valueOf(Integer.parseInt(output[6])/1000));
        vInterval.setText(String.valueOf(Integer.parseInt(output[7])/1000));
        lSeekBar.setProgress(Integer.parseInt(output[14])/255*100);
        lSwitch.setChecked((Integer.parseInt(output[9]) != 0));
        lModus.setSelection(Integer.parseInt(output[10]));
        eSwitch.setChecked((Integer.parseInt(output[11]) != 0));
        eDuration.setText(String.valueOf(Integer.parseInt(output[12])/1000));
        eInterval.setText(String.valueOf(Integer.parseInt(output[13])/1000));

        userStatus = true;

       //writeMessage = writeMessage.substring(begin, end);

        }
    };

    private void setupInterrupts()
    {
        nDevice.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                //Todo: Close te bluetooth connection and .
                ct.cancel();

                finish();
            }
        });

        uSpinner.setSelection(0, false);
        uSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                if(onItemInterrupt) {
                    try {
                        if(userStatus) {
                            //Toast.makeText(getBaseContext(), "ul" + String.valueOf(position) + "!", Toast.LENGTH_SHORT).show();
                            ct.write("ul" + String.valueOf(position) + "!");
                        }
                    } catch (Exception e) {
                    }
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

        mSpinner.setSelection(0, false);
        mSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                if(onItemInterrupt) {
                    try {
                        if(userStatus) {
                            //Toast.makeText(getBaseContext(), "mm" + String.valueOf(position) + "!", Toast.LENGTH_SHORT).show();
                            ct.write("mm" + String.valueOf(position) + "!");
                        }
                    } catch (Exception e) {
                    }
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

        mMinutes.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                String str1 = mMinutes.getText().toString();
                String str2 = mSeconds.getText().toString();
                int totalSeconds = Integer.parseInt(str1) * 60 + Integer.parseInt(str2);

                if(userStatus) {
                    //Toast.makeText(getBaseContext(), "md" + String.valueOf(totalSeconds) + "!", Toast.LENGTH_SHORT).show();
                    ct.write("md" + String.valueOf(totalSeconds) + "!");
                }

                View view = getCurrentFocus();
                if (view != null) {
                    InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
                    imm.hideSoftInputFromWindow(view.getWindowToken(), 0);
                }

                return true;
            }
        });

        mSeconds.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                String str1 = mMinutes.getText().toString();
                String str2 = mSeconds.getText().toString();
                int totalSeconds = Integer.parseInt(str1) * 60 + Integer.parseInt(str2);

                if(userStatus) {
                    //Toast.makeText(getBaseContext(), "md" + String.valueOf(totalSeconds) + "!", Toast.LENGTH_SHORT).show();
                    ct.write("md" + String.valueOf(totalSeconds) + "!");
                }

                View view = getCurrentFocus();
                if (view != null) {
                    InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
                    imm.hideSoftInputFromWindow(view.getWindowToken(), 0);
                }

                return true;
            }
        });

        mBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            int progressChanged = 0;

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromTouch) {
                progressChanged = progress;
                //Toast.makeText(getBaseContext(), String.valueOf(progress), Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                progressChanged = mBar.getProgress();
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                if(userStatus) {
                    //Toast.makeText(getBaseContext(), String.valueOf(progressChanged), Toast.LENGTH_SHORT).show();
                    ct.write("sv" + String.valueOf(progressChanged) + "!");
                }
            }
        });

        mSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener()
        {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean bChecked) {
                if (bChecked) {
                    if(userStatus) {
                        //Toast.makeText(getBaseContext(), "on", Toast.LENGTH_SHORT).show();
                        ct.write("sW!");
                    }
                } else {
                    if(userStatus) {
                        //Toast.makeText(getBaseContext(), "off", Toast.LENGTH_SHORT).show();
                        ct.write("sS!");
                    }
                }
            }
        });

        aMSpinner.setSelection(0, false);
        aMSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                if(onItemInterrupt) {
                    if(userStatus) {
                        if (position == 0) {
                            int folder = Integer.parseInt(mInput.getText().toString());
                            ct.write("sR" + String.valueOf(folder) + "!");
                        } else if (position == 1) {
                            ct.write("sR!"); //play with folder name(cycle)
                        } else if (position == 2) {
                            ct.write("ss!"); //shuffle
                        } else if (position == 3) {
                            ct.write("sC!"); //single cycle
                        }
                    }

                    try {
                        Toast.makeText(getBaseContext(), "ss" + String.valueOf(position) + "!", Toast.LENGTH_SHORT).show();
                        //ct.write("sm"+ String.valueOf(position)+"!");
                    } catch (Exception e) {
                    }
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

        sInput.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                String str = sInput.getText().toString();
                if(userStatus) {
                    //Toast.makeText(getBaseContext(), "sk" + str + "!", Toast.LENGTH_SHORT).show();
                    ct.write("sk" + str + "!");
                }

                View view = getCurrentFocus();
                if (view != null) {
                    InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
                    imm.hideSoftInputFromWindow(view.getWindowToken(), 0);
                }

                return true;
            }
        });

        mInput.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                String str = mInput.getText().toString();
                if(userStatus) {
                    //Toast.makeText(getBaseContext(), "sF" + str + "!", Toast.LENGTH_SHORT).show();
                    ct.write("sF" + str + "!");
                }

                View view = getCurrentFocus();
                if (view != null) {
                    InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
                    imm.hideSoftInputFromWindow(view.getWindowToken(), 0);
                }

                return true;
            }
        });

        previous.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                //Todo: Close te bluetooth connection and .
                if(userStatus) {
                    //Toast.makeText(getBaseContext(), "s<!", Toast.LENGTH_SHORT).show();
                    ct.write("s<!");
                }
            }
        });

        next.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                //Todo: Close te bluetooth connection and .
                if(userStatus) {
                    //Toast.makeText(getBaseContext(), "s>!", Toast.LENGTH_SHORT).show();
                    ct.write("s>!");
                }
            }
        });

        play.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                //Todo: Close te bluetooth connection and .
                if(userStatus) {
                    //Toast.makeText(getBaseContext(), "sp!", Toast.LENGTH_SHORT).show();
                    ct.write("sp!");
                }
            }
        });

        pause.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                //Todo: Close te bluetooth connection and .
                if(userStatus) {
                    //Toast.makeText(getBaseContext(), "sP!", Toast.LENGTH_SHORT).show();
                    ct.write("sP!");
                }
            }
        });

        vSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            int progressChanged = 0;

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromTouch) {
                progressChanged = progress;
                //Toast.makeText(getBaseContext(), String.valueOf(progress), Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                progressChanged = mBar.getProgress();
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                if(userStatus) {
                    //Toast.makeText(getBaseContext(), String.valueOf(progressChanged), Toast.LENGTH_SHORT).show();
                    ct.write("vi" + String.valueOf(progressChanged) + "!");
                }
            }
        });

        vSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener()
        {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean bChecked) {
                if (bChecked) {
                    if(userStatus) {
                        //Toast.makeText(getBaseContext(), "on", Toast.LENGTH_SHORT).show();
                        ct.write("vo!");
                    }
                } else {
                    if(userStatus) {
                        //Toast.makeText(getBaseContext(), "off", Toast.LENGTH_SHORT).show();
                        ct.write("vf!");
                    }
                }
            }
        });

        vDuration.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                String str = vDuration.getText().toString();
                if(userStatus) {
                    //Toast.makeText(getBaseContext(), "vv" + str + "!", Toast.LENGTH_SHORT).show();
                    ct.write("vv" + str + "!");
                }

                View view = getCurrentFocus();
                if (view != null) {
                    InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
                    imm.hideSoftInputFromWindow(view.getWindowToken(), 0);
                }

                return true;
            }
        });

        vInterval.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                String str = vInterval.getText().toString();
                if(userStatus) {
                    //Toast.makeText(getBaseContext(), "vz" + str + "!", Toast.LENGTH_SHORT).show();
                    ct.write("vz" + str + "!");
                }

                View view = getCurrentFocus();
                if (view != null) {
                    InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
                    imm.hideSoftInputFromWindow(view.getWindowToken(), 0);
                }

                return true;
            }
        });

        lSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            int progressChanged = 0;

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromTouch) {
                progressChanged = progress;
                //Toast.makeText(getBaseContext(), String.valueOf(progress), Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                progressChanged = mBar.getProgress();
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                if(userStatus) {
                    //Toast.makeText(getBaseContext(), "lo" + String.valueOf(progressChanged) + "!", Toast.LENGTH_SHORT).show();
                    ct.write("lo" + String.valueOf(progressChanged) + "!");
                }
            }
        });

        lSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener()
        {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean bChecked) {
                if (bChecked) {
                    if(userStatus) {
                        //Toast.makeText(getBaseContext(), "on", Toast.LENGTH_SHORT).show();
                        ct.write("la1!");
                    }
                } else {
                    if(userStatus) {
                        //Toast.makeText(getBaseContext(), "off", Toast.LENGTH_SHORT).show();
                        ct.write("la0!");
                    }
                }
            }
        });

        lModus.setSelection(0, false);
        lModus.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                if(onItemInterrupt) {
                    try {
                        if(userStatus) {
                            //Toast.makeText(getBaseContext(), "lb" + String.valueOf(position) + "!", Toast.LENGTH_SHORT).show();
                            ct.write("lb" + String.valueOf(position) + "!");
                        }
                    } catch (Exception e) {
                    }
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

        eSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener()
        {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean bChecked) {
                if (bChecked) {
                    if(userStatus) {
                        //Toast.makeText(getBaseContext(), "on", Toast.LENGTH_SHORT).show();
                        ct.write("lm!");
                    }
                } else {
                    if(userStatus) {
                        //Toast.makeText(getBaseContext(), "off", Toast.LENGTH_SHORT).show();
                        ct.write("ln!");
                    }
                }
            }
        });

        eDuration.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                String str = eDuration.getText().toString();
                if(userStatus) {
                    //Toast.makeText(getBaseContext(), "lq" + str + "!", Toast.LENGTH_SHORT).show();
                    ct.write("lq" + str + "!");
                }

                View view = getCurrentFocus();
                if (view != null) {
                    InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
                    imm.hideSoftInputFromWindow(view.getWindowToken(), 0);
                }

                return true;
            }
        });

        eInterval.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                String str = eInterval.getText().toString();
                if(userStatus) {
                    //Toast.makeText(getBaseContext(), "lr" + str + "!", Toast.LENGTH_SHORT).show();
                    ct.write("lr" + str + "!");
                }

                View view = getCurrentFocus();
                if (view != null) {
                    InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
                    imm.hideSoftInputFromWindow(view.getWindowToken(), 0);
                }

                return true;
            }
        });
    }
}
