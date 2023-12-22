package com.animousen4.core.stringbuilder.command;

import lombok.AllArgsConstructor;

@AllArgsConstructor
public class DeleteCommand implements Command {
    private int start;
    private String deletedString;


    @Override
    public void undo(StringBuilder stringBuilder) {
        stringBuilder.insert(start, deletedString);
    }
}