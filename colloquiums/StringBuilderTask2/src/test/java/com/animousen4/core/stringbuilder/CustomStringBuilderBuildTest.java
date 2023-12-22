package com.animousen4.core.stringbuilder;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class CustomStringBuilderBuildTest {

    CustomStringBuilder customStringBuilder;

    @Test
    void testOnEmptyAppenderBuild(){
        customStringBuilder = new CustomStringBuilder(
                new StringBuilder()
        );

        customStringBuilder.append("Text1");

        String result = customStringBuilder.build();

        assertEquals("Text1", result);

    }

    @Test
    void testOnNotEmptyAppenderBuild() {
        customStringBuilder = new CustomStringBuilder(
                new StringBuilder().append("StartText")
        );

        customStringBuilder.append("Text1");

        String result = customStringBuilder.build();

        assertEquals("StartTextText1", result);

    }


    @Test
    void testAppendDeleteBuild() {
        customStringBuilder = new CustomStringBuilder(
                new StringBuilder()
        );

        customStringBuilder
                .append("Text")
                .delete(0, 1);

        String result = customStringBuilder.build();

        assertEquals("ext", result);

    }

    @Test
    void testUndoDeleteOperationBuild()  {
        customStringBuilder = new CustomStringBuilder(
                new StringBuilder().append("StartText")
        );

        customStringBuilder
                .delete(0, 1)

                .undo();

        String res = customStringBuilder.build();

        assertEquals("StartText", res);

    }

    @Test
    void testUndoAllMixOperationBuild() {
        customStringBuilder = new CustomStringBuilder(
                new StringBuilder().append("StartText")
        );

        customStringBuilder
                .append("1")
                .delete(0, 1)
                .append("2")

                .undo()
                .undo()
                .undo();

        String res = customStringBuilder.build();

        assertEquals("StartText", res);

    }

    @Test
    void testUndoOnlyOnceMixOperationBuild() {
        customStringBuilder = new CustomStringBuilder(
                new StringBuilder().append("StartText")
        );

        customStringBuilder
                .append("1")
                .delete(0, 1)
                .append("2")

                .undo();


        String res = customStringBuilder.build();

        assertEquals("tartText1", res);

    }


}
