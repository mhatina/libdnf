#ifndef LIBDNF_LINE_HPP
#define LIBDNF_LINE_HPP

#include "Cell.hpp"
#include "Column.hpp"

#include <memory>
#include <libsmartcols/libsmartcols.h>

class Table;

class Line
{
    friend class Table;

public:
    explicit Line(struct libscols_line *line) : line(line) { scols_ref_line(line); };
    Line(const Line &line) { this->line = line.line; };
    ~Line() { scols_unref_line(line); }

    void allocCells(size_t n) { scols_line_alloc_cells(line, n); };
    void freeCells() { scols_line_free_cells(line); };

    void addChild(Line *child) { scols_line_add_child(line, child->getSmartColsLine()); };
    void removeChild(Line *child) { scols_line_remove_child(line, child->getSmartColsLine()); };
    std::unique_ptr<Line> nextChild(struct libscols_iter *iter);

    void referData(size_t n, char *data) { scols_line_refer_data(line, n, data); };
    void referColumnData(Column *column, char *data);

    bool hasChildren() { return scols_line_has_children(line) == 1; };
    bool isAncestor(Line *parent) { return scols_line_is_ancestor(line, parent->getSmartColsLine()) == 1; };

    size_t getCellCount() { return scols_line_get_ncells(line); };
    std::string getColor() { return scols_line_get_color(line); };
    std::unique_ptr<Cell> getCell(size_t n) { return std::unique_ptr<Cell>(new Cell(scols_line_get_cell(line, n))); };
    std::unique_ptr<Cell> getColumnCell(const std::shared_ptr<Column> &column) { return getColumnCell(column.get()); };
    std::unique_ptr<Cell> getColumnCell(Column *column);
    std::unique_ptr<Line> getParent() { return std::unique_ptr<Line>(new Line(scols_line_get_parent(line))); };
    void *getUserdata() { return scols_line_get_userdata(line); };

    void setUserdata(void *data) { scols_line_set_userdata(line, data); };
    void setColor(const std::string &color) { scols_line_set_color(line, color.c_str()); };
    void setData(size_t n, const std::string &data) { scols_line_set_data(line, n, data.c_str()); };
    void setColumnData(const std::shared_ptr<Column> &column, const std::string &data);
    void setColumnData(Column *column, const std::string &data);


private:
    libscols_line *getSmartColsLine() const { return line; };

    struct libscols_line *line;
};


#endif //LIBDNF_LINE_HPP
