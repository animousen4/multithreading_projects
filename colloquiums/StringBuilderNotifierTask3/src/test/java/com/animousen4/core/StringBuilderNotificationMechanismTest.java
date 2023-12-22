package com.animousen4.core;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.mockito.ArgumentMatchers.eq;
import static org.mockito.Mockito.*;

public class StringBuilderNotificationMechanismTest {
    StringBuilderNotifier stringBuilderNotifier;
    @Test
    void testSubscriberAppendMechanism() {
        StringListener listener = mock(StringListener.class);

        var ref = new Object() {
            Boolean executed = false;
        };

        doAnswer(
                invocation -> {
                    ref.executed = true;
                    return null;
                }
        ).when(listener).update(eq("Text1"));

        stringBuilderNotifier = new StringBuilderNotifier(
                new StringBuilder()
        );

        stringBuilderNotifier.addListener(listener);
        stringBuilderNotifier.append("Text1");

        assertTrue(ref.executed);


        //stringBuilderNotifier.notifyListeners();


    }

    @Test
    void testSubscriberDeleteMechanism() {
        stringBuilderNotifier = new StringBuilderNotifier(
                new StringBuilder().append("Text1")
        );

        StringListener listener = mock(StringListener.class);
        var ref = new Object() {
            Boolean executed = false;
        };
        doAnswer(
                invocation -> {
                    ref.executed = true;
                    return null;
                }
        ).when(listener).update(eq("ext1"));

        stringBuilderNotifier.addListener(listener);
        stringBuilderNotifier.delete(0, 1);

        assertTrue(ref.executed);


    }

    @Test
    void testSubscriberMixMechanism() {
        stringBuilderNotifier = new StringBuilderNotifier(
                new StringBuilder().append("Text1")
        );

        StringListener listener = mock(StringListener.class);
        var ref = new Object() {
            int executedTimes = 0;
        };
        doAnswer(
                invocation -> {
                    ref.executedTimes++;
                    return null;
                }
        ).when(listener).update(any());



        stringBuilderNotifier.addListener(listener);
        stringBuilderNotifier.delete(0, 1);
        stringBuilderNotifier.append("2");

        assertEquals(2, ref.executedTimes);


    }
}
