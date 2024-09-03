package co.ab180.airbridge.ue;

import co.ab180.airbridge.AirbridgeCallback;

import android.net.Uri;

public class AirbridgeUECallback implements AirbridgeCallback<Uri> {

    @Override
    public native void onSuccess(Uri uri);
   
    @Override
    public native void onFailure(Throwable throwable);

    @Override
    public native void onComplete();
}
