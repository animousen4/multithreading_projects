package com.animousen4.core.stringbuilder;

import com.animousen4.core.stringbuilder.command.AppendCommand;
import com.animousen4.core.stringbuilder.command.Command;
import com.animousen4.core.stringbuilder.command.DeleteCommand;

import java.util.ArrayList;
import java.util.List;



public class CustomStringBuilder {
    private final StringBuilder stringBuilder;
    private final List<Command> commandList;

    CustomStringBuilder(StringBuilder builder) {
        this.stringBuilder = builder;
        this.commandList = new ArrayList<>();
    }

    public CustomStringBuilder append(String str) {
        stringBuilder.append(str);
        commandList.add(new AppendCommand(str));

        return this;
    }

    public CustomStringBuilder delete(int start, int end) {
        String deletedString = stringBuilder.substring(start, end);
        stringBuilder.delete(start, end);
        commandList.add(new DeleteCommand(start, deletedString));

        return this;
    }

    public CustomStringBuilder undo() {
        if (!commandList.isEmpty()) {
            Command lastCommand = commandList.remove(commandList.size() - 1);
            lastCommand.undo(stringBuilder);
        }

        return this;
    }

    public String build() {
        return stringBuilder.toString();
    }


}
