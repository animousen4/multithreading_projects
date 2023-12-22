package com.animousen4.core;

import com.animousen4.core.observer.Listener;
import com.animousen4.core.observer.Publisher;
import lombok.AllArgsConstructor;
import lombok.Getter;

import java.util.HashSet;
import java.util.Set;

@AllArgsConstructor
@Getter
public class StringBuilderNotifier implements Publisher<String> {
    private final StringBuilder stringBuilder;
    private final Set<Listener<String>> listeners;

    public StringBuilderNotifier(StringBuilder stringBuilder) {
        this.stringBuilder = stringBuilder;
        listeners = new HashSet<>();
    }
    public StringBuilderNotifier append(String str) {
        stringBuilder.append(str);
        notifyListeners();
        return this;
    }

    public StringBuilderNotifier delete(int start, int end) {
        stringBuilder.delete(start, end);
        notifyListeners();
        return this;
    }

    public String build() {
        return stringBuilder.toString();
    }

    private void notifyListeners() {
        String updatedString = build();
        listeners.forEach(
                listener -> listener.update(updatedString)
        );
    }

    @Override
    public void addListener(Listener<String> listener) {
        listeners.add(listener);
    }

    @Override
    public void removeListener(Listener<String> listener) {
        listeners.remove(listener);
    }
}