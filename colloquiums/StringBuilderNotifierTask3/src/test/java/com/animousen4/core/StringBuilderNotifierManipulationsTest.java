package com.animousen4.core;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class StringBuilderNotifierManipulationsTest {

    StringBuilderNotifier customStringBuilder;
    @Test
    void testOnEmptyAppenderBuild(){
        customStringBuilder = new StringBuilderNotifier(
                new StringBuilder()
        );

        customStringBuilder.append("Text1");

        String result = customStringBuilder.build();

        assertEquals("Text1", result);

    }

    @Test
    void testOnNotEmptyAppenderBuild() {
        customStringBuilder = new StringBuilderNotifier(
                new StringBuilder().append("StartText")
        );

        customStringBuilder.append("Text1");

        String result = customStringBuilder.build();

        assertEquals("StartTextText1", result);

    }


    @Test
    void testAppendDeleteBuild() {
        customStringBuilder = new StringBuilderNotifier(
                new StringBuilder()
        );

        customStringBuilder
                .append("Text")
                .delete(0, 1);

        String result = customStringBuilder.build();

        assertEquals("ext", result);

    }
}
