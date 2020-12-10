
package com.example.graphicsproject.navar.network.model;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

public class Distance_ {

    @SerializedName("text")
    @Expose
    private String text;
    @SerializedName("value")
    @Expose
    private int value;

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

}
