package com.animousen4.core;

import org.junit.jupiter.api.Test;

import java.util.HashSet;
import java.util.Set;

import static org.assertj.core.api.Assertions.assertThat;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.mockito.Mockito.mock;

public class StringBuilderNotifierTest {
    StringBuilderNotifier stringBuilderNotifier;

    @Test
    void testEmptySubscribers() {
        stringBuilderNotifier = new StringBuilderNotifier(new StringBuilder());

        assertEquals(0, stringBuilderNotifier.getListeners().size());
    }

    @Test
    void testAddSubscriber() {
        stringBuilderNotifier = new StringBuilderNotifier(new StringBuilder());

        StringListener listener = mock(StringListener.class);

        stringBuilderNotifier.addListener(listener);

        assertEquals(1, stringBuilderNotifier.getListeners().size());
        assertThat(stringBuilderNotifier.getListeners())
                .usingRecursiveComparison()
                .isEqualTo(
                        Set.of(listener)
                );
    }

    @Test
    void testAddSameSubscribers() {
        stringBuilderNotifier = new StringBuilderNotifier(new StringBuilder());

        StringListener listener = mock(StringListener.class);

        stringBuilderNotifier.addListener(listener);
        stringBuilderNotifier.addListener(listener);

        assertEquals(1, stringBuilderNotifier.getListeners().size());

        assertThat(stringBuilderNotifier.getListeners())
                .usingRecursiveComparison()
                .isEqualTo(
                        Set.of(listener)
                );
    }

    @Test
    void testAddDifferentSubscribers() {
        stringBuilderNotifier = new StringBuilderNotifier(new StringBuilder());

        StringListener listener1 = mock(StringListener.class);
        StringListener listener2 = mock(StringListener.class);

        stringBuilderNotifier.addListener(listener1);
        stringBuilderNotifier.addListener(listener2);

        assertEquals(2, stringBuilderNotifier.getListeners().size());

        assertThat(stringBuilderNotifier.getListeners())
                .usingRecursiveComparison()
                .isEqualTo(
                        Set.of(listener1, listener2)
                );
    }

    @Test
    void testRemoveSubscriber() {
        StringListener listener = mock(StringListener.class);

        stringBuilderNotifier = new StringBuilderNotifier(
                new StringBuilder(),
                new HashSet<>(
                        Set.of(
                                listener
                        )
                )
        );

        stringBuilderNotifier.removeListener(listener);

        assertTrue(stringBuilderNotifier.getListeners().isEmpty());

    }

}
