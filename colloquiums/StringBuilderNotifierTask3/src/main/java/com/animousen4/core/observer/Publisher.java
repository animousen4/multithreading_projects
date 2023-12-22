package com.animousen4.core.observer;

public interface Publisher<T> {
    void addListener(Listener<T> listener);
    void removeListener(Listener<T> listener);
}
