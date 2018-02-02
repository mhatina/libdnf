#include "Table.hpp"

void Table::setColumnSeparator(const std::string &separator)
{
    scols_table_set_column_separator(table, separator.c_str());
}

std::unique_ptr<Column> Table::getColumn(size_t n)
{
    return std::unique_ptr<Column>(new Column(scols_table_get_column(table, n)));
}

void Table::moveColumn(Column *before, Column *toMove)
{
    scols_table_move_column(table, before->getSmartColsColumn(), toMove->getSmartColsColumn());
}

std::shared_ptr<Column> Table::newColumn(const std::string &name, double widthHint, int flags)
{
    auto smartColsColumn = scols_table_new_column(table, name.c_str(), widthHint, flags);
    auto column = std::make_shared<Column>(smartColsColumn);

    scols_unref_column(smartColsColumn);
    return column;
}

std::unique_ptr<Column> Table::nextColumn(struct libscols_iter *iter)
{
    struct libscols_column *column;
    scols_table_next_column(table, iter, &column);
    return std::unique_ptr<Column>(new Column(column));
}

std::shared_ptr<Line> Table::newLine(Line *parent)
{
    auto smartColsLine = scols_table_new_line(table, parent == nullptr ? nullptr : parent->getSmartColsLine());
    auto line = std::make_shared<Line>(smartColsLine);

    scols_unref_line(smartColsLine);
    return line;
}

std::unique_ptr<Line> Table::nextLine(struct libscols_iter *itr)
{
    struct libscols_line *line;
    scols_table_next_line(table, itr, &line);
    return std::unique_ptr<Line>(new Line(line));
}

std::string Table::toString()
{
    char *data;
    scols_print_table_to_string(table, &data);
    return std::string(data);
}

std::string Table::toString(Line *start, Line *end)
{
    char *data;
    if (start != nullptr && end != nullptr) {
        scols_table_print_range_to_string(table, start->getSmartColsLine(), end->getSmartColsLine(), &data);
        return std::string(data);
    } else {
        return std::string();
    }
}
