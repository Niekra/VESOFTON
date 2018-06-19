package com.placeholder.isnoezel;

import android.bluetooth.*;
import android.os.Handler;
import android.os.Message;
import android.os.ParcelUuid;
import android.os.SystemClock;
import android.util.Log;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.UUID;

import static android.content.ContentValues.TAG;
import static java.lang.Boolean.FALSE;
import static java.lang.Boolean.TRUE;

public class ConnectedThread extends Thread {
    BluetoothSocket mmSocket = null;

    private final InputStream mmInStream;
    private final OutputStream mmOutStream;
    private final BluetoothDevice mmDevice;
    private final BluetoothAdapter mmAdapter;
    private final Handler mHandler;
    public static final int MESSAGE_READ = 2;

    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"/*"00001101-0000-1000-8000-00805F9B34FB"/*"B8E06067-62AD-41BA-9231-206AE80AB550"*/);

    volatile boolean running = true;

    public ConnectedThread(BluetoothDevice mmBtDevice, Handler iHandler) throws IOException, NoSuchMethodException, InvocationTargetException, IllegalAccessException {
        mmDevice = mmBtDevice;
        mmAdapter = BluetoothAdapter.getDefaultAdapter();
        mHandler = iHandler;
        //ParcelUuid[] uuids = mmDevice.getUuids();
        //UUID MY_UUID = mmDevice.getUuids()[0].getUuid();
        mmSocket = mmDevice.createInsecureRfcommSocketToServiceRecord(MY_UUID);
        final Method m = mmDevice.getClass().getMethod("createInsecureRfcommSocketToServiceRecord", new Class[] { UUID.class });
        mmSocket = (BluetoothSocket) m.invoke(mmDevice, MY_UUID);

        //try {
        mmSocket.connect();
        //} catch (IOException e) {
            //final Method l = mmDevice.getClass().getMethod("createRfcommSocket", new Class[]{int.class});
            //mmSocket = (BluetoothSocket) l.invoke(mmDevice, 1);
        //}

        /*
        try {
            mmSocket = mmDevice.createInsecureRfcommSocketToServiceRecord(MY_UUID);
        } catch (IOException e) {
            //mHandler.obtainMessage(2, 1, -1, 1).sendToTarget();
            e.printStackTrace();
        }

        try {
            final Method m = mmDevice.getClass().getMethod("createInsecureRfcommSocketToServiceRecord", new Class[] { UUID.class });
            mmSocket = (BluetoothSocket) m.invoke(mmDevice, MY_UUID);
        } catch (Exception e) {
            Log.e(TAG, "Could not create Insecure RFComm Connection",e);
            //mHandler.obtainMessage(2, 1, -1, 1).sendToTarget();
        }

        try {
            mmSocket.connect();
        } catch (IOException e) {
            try {
                final Method l = mmDevice.getClass().getMethod("createRfcommSocket", new Class[] {int.class});
                mmSocket = (BluetoothSocket) l.invoke(mmDevice, 1);
            } catch (Exception e1) {
                e1.printStackTrace();
               // mHandler.obtainMessage(2, 1, -1, 1).sendToTarget();
            }
            try {
                mmSocket.connect();
            } catch (IOException c) {
                c.printStackTrace();
                //mHandler.obtainMessage(2, 1, -1, 1).sendToTarget();
                try {
                    mmSocket.close();
                } catch (IOException c1) {
                    c1.printStackTrace();
                }

            }
        }*/

        InputStream tmpIn = null;
        OutputStream tmpOut = null;

        tmpIn = mmSocket.getInputStream();
        tmpOut = mmSocket.getOutputStream();

        // Get the input and output streams, using temp objects because
        // member streams are final
        /*
        try {
            tmpIn = mmSocket.getInputStream();
            tmpOut = mmSocket.getOutputStream();
        } catch (IOException e) {
            mHandler.obtainMessage(2, 1, -1, 1).sendToTarget();

        }*/

        mmInStream = tmpIn;
        mmOutStream = tmpOut;
    }

    @Override
    public void run() {
        int availableBytes = 0;

        int begin = 0;
        int bytes = 0;
                while (true){
                    if (!running) return;
                    try{
                        availableBytes=mmInStream.available();
                        byte[] buffer=new byte[availableBytes];
                        if (availableBytes>0){
                            bytes=mmInStream.read(buffer);
                            //mHandler.obtainMessage(1, bytes, -1, buffer).sendToTarget();

                            if (buffer[availableBytes-1] == '!'){
                                mHandler.obtainMessage(1, bytes, -1, buffer).sendToTarget();
                            }
                            else {
                                SystemClock.sleep(100);
                            }
                        }
                    }catch (IOException e){
                        e.printStackTrace();
                    }
                }
    }

    /* Call this from the main activity to send data to the remote device */
    public boolean write(String s) {
        try {
            mmOutStream.write(s.getBytes());
            return TRUE;
        } catch (IOException e) {
            return FALSE;
        }
    }

    /* Call this from the main activity to shutdown the connection */
    public void cancel() {
        running = false;
        try {
            mmSocket.close();
        } catch (IOException e) {
            return;
        }
    }
}