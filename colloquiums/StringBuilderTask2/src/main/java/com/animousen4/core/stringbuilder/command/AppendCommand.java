package com.animousen4.core.stringbuilder.command;

import lombok.AllArgsConstructor;

@AllArgsConstructor
public class AppendCommand implements Command {
    private final String appendedString;

    @Override
    public void undo(StringBuilder stringBuilder) {
        stringBuilder.delete(stringBuilder.length() - appendedString.length(), stringBuilder.length());
    }
}