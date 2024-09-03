package co.ab180.airbridge.ue;

import java.util.Map;

import co.ab180.airbridge.OnAttributionResultReceiveListener;

public class UEOnAttributionResultReceiveListener implements OnAttributionResultReceiveListener {

    @Override
    public native void onAttributionResultReceived(Map<String, String> result);
}
