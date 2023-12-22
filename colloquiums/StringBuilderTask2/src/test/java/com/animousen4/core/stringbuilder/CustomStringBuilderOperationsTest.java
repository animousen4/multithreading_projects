package com.animousen4.core.stringbuilder;

import com.animousen4.core.stringbuilder.command.AppendCommand;
import com.animousen4.core.stringbuilder.command.Command;
import com.animousen4.core.stringbuilder.command.DeleteCommand;
import org.junit.jupiter.api.Test;

import java.lang.reflect.Field;
import java.util.List;

import static org.assertj.core.api.Assertions.assertThat;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class CustomStringBuilderOperationsTest {

    CustomStringBuilder customStringBuilder;

    List<Command> getCommandListFromInstance() throws NoSuchFieldException, IllegalAccessException {
        Field field = CustomStringBuilder.class.getDeclaredField("commandList");
        field.setAccessible(true);

        return (List<Command>) field.get(customStringBuilder);
    }

    @Test
    void testOnEmptyAppenderOperation() throws NoSuchFieldException, IllegalAccessException {
        customStringBuilder = new CustomStringBuilder(
                new StringBuilder()
        );

        List<Command> list = getCommandListFromInstance();

        customStringBuilder.append("Text1");

        assertEquals(1, list.size());

        assertThat(
                List.of(
                        new AppendCommand("Text1")
                )
        )
                .usingRecursiveComparison()
                .isEqualTo(list);

    }

    @Test
    void testOnNotEmptyAppenderOperation() throws NoSuchFieldException, IllegalAccessException {
        customStringBuilder = new CustomStringBuilder(
                new StringBuilder().append("StartText")
        );

        List<Command> list = getCommandListFromInstance();

        customStringBuilder.append("Text1");

        assertEquals(1, list.size());

        assertThat(
                List.of(
                        new AppendCommand("Text1")
                )
        )
                .usingRecursiveComparison()
                .isEqualTo(list);

    }


    @Test
    void testDeleteOperation() throws NoSuchFieldException, IllegalAccessException {
        customStringBuilder = new CustomStringBuilder(
                new StringBuilder().append("Text1")
        );

        List<Command> list = getCommandListFromInstance();

        customStringBuilder.delete(0, 1);

        assertEquals(1, list.size());

        assertThat(
                List.of(
                        new DeleteCommand(0, "T")
                )
        )
                .usingRecursiveComparison()
                .isEqualTo(list);

    }

    @Test
    void testAppendDeleteOperation() throws NoSuchFieldException, IllegalAccessException {
        customStringBuilder = new CustomStringBuilder(
                new StringBuilder()
        );

        List<Command> list = getCommandListFromInstance();

        customStringBuilder.append("Text");
        customStringBuilder.delete(0, 1);

        assertEquals(2, list.size());

        assertThat(
                List.of(
                        new AppendCommand("Text"),
                        new DeleteCommand(0, "T")
                )
        )
                .usingRecursiveComparison()
                .isEqualTo(list);

    }

    @Test
    void testUndoAppendOperation() throws NoSuchFieldException, IllegalAccessException {
        customStringBuilder = new CustomStringBuilder(
                new StringBuilder().append("StartText")
        );

        List<Command> list = getCommandListFromInstance();

        customStringBuilder
                .append("Text")

                .undo();

        assertEquals(0, list.size());

        assertThat(
                List.of()
        )
                .usingRecursiveComparison()
                .isEqualTo(list);

    }


    @Test
    void testUndoDeleteOperation() throws NoSuchFieldException, IllegalAccessException {
        customStringBuilder = new CustomStringBuilder(
                new StringBuilder().append("StartText")
        );

        List<Command> list = getCommandListFromInstance();

        customStringBuilder
                .delete(0, 1)

                .undo();

        assertEquals(0, list.size());

        assertThat(
                List.of()
        )
                .usingRecursiveComparison()
                .isEqualTo(list);

    }

    @Test
    void testUndoAllMixOperation() throws NoSuchFieldException, IllegalAccessException {
        customStringBuilder = new CustomStringBuilder(
                new StringBuilder().append("StartText")
        );

        List<Command> list = getCommandListFromInstance();

        customStringBuilder
                .append("1")
                .delete(0, 1)
                .append("2")

                .undo()
                .undo()
                .undo();

        assertEquals(0, list.size());

        assertThat(
                List.of()
        )
                .usingRecursiveComparison()
                .isEqualTo(list);

    }

    @Test
    void testUndoOnlyOnceMixOperation() throws NoSuchFieldException, IllegalAccessException {
        customStringBuilder = new CustomStringBuilder(
                new StringBuilder().append("StartText")
        );

        List<Command> list = getCommandListFromInstance();

        customStringBuilder
                .append("1")
                .delete(0, 1)
                .append("2")

                .undo();


        assertEquals(2, list.size());

        assertThat(
                List.of(
                        new AppendCommand("1"),
                        new DeleteCommand(0, "S")
                )
        )
                .usingRecursiveComparison()
                .isEqualTo(list);

    }
}
