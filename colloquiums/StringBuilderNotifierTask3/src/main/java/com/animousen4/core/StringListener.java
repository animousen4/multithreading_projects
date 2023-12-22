package com.animousen4.core;

import com.animousen4.core.observer.Listener;
import lombok.Getter;

@Getter
public class StringListener implements Listener<String> {

    private String curString;
    @Override
    public void update(String updatedObject) {
        curString = updatedObject;
    }
}
