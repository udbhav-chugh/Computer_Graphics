package com.example.graphicsproject.Activities;

import android.os.Bundle;

import androidx.fragment.app.FragmentActivity;

import com.beyondar.android.plugin.googlemap.GoogleMapWorldPlugin;
import com.beyondar.android.world.World;
import com.example.graphicsproject.R;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;

public class GoogleMapActivity extends FragmentActivity implements OnMapReadyCallback {

    private GoogleMap mMap;
    private GoogleMapWorldPlugin mGoogleMapPlugin;
    private World mWorld;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.map_google);

        SupportMapFragment supportMapFragment = ((SupportMapFragment) getSupportFragmentManager().findFragmentById(R.id.map));
        supportMapFragment.getMapAsync(this);

    }

    @Override
    public void onMapReady(GoogleMap googleMap) {

        mMap = googleMap;
        setUpMap();
    }

    public void setUpMap() {
        // We create the world and fill the world
        try {
            mWorld = CustomWorldHelper.generateObjects(GoogleMapActivity.this);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // As we want to use GoogleMaps, we are going to create the plugin and
        // attach it to the World
        mGoogleMapPlugin = new GoogleMapWorldPlugin(GoogleMapActivity.this);
        // Then we need to set the map in to the GoogleMapPlugin
        mGoogleMapPlugin.setGoogleMap(mMap);
        // Now that we have the plugin created let's add it to our world.
        // NOTE: It is better to load the plugins before start adding object in to the world.
        mWorld.addPlugin(mGoogleMapPlugin);
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(mGoogleMapPlugin.getLatLng(), 15));
        mMap.animateCamera(CameraUpdateFactory.zoomTo(4), 2000, null);
    }
}