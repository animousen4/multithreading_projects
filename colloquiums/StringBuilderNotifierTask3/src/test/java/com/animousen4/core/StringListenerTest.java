package com.animousen4.core;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;

public class StringListenerTest {

    @Test
    void testOnUpdate() {
        StringListener stringListener = new StringListener();

        stringListener.update("123");

        assertEquals("123", stringListener.getCurString());
    }

    @Test
    void testOnMultipleUpdate() {
        StringListener stringListener = new StringListener();

        stringListener.update("123");
        stringListener.update("222");
        stringListener.update("333");

        assertEquals("333", stringListener.getCurString());
    }

    @Test
    void testOnNullUpdate() {
        StringListener stringListener = new StringListener();

        stringListener.update(null);

        assertNull(stringListener.getCurString());
    }
}
