#include "Line.hpp"

std::unique_ptr<Line> Line::nextChild(struct libscols_iter *iter)
{
    struct libscols_line *scolsLine;
    scols_line_next_child(line, iter, &scolsLine);

    return std::unique_ptr<Line>(new Line(scolsLine));
}

void Line::referColumnData(Column *column, char *data)
{
    scols_line_refer_column_data(line, column->getSmartColsColumn(), data);
}

std::unique_ptr<Cell> Line::getColumnCell(Column *column)
{
    return std::unique_ptr<Cell>(new Cell(scols_line_get_column_cell(line, column->getSmartColsColumn())));
}

void Line::setColumnData(const std::shared_ptr<Column> &column, const std::string &data)
{
    setColumnData(column.get(), data);
}

void Line::setColumnData(Column *column, const std::string &data)
{
    scols_line_set_column_data(line, column->getSmartColsColumn(), data.c_str());
}
