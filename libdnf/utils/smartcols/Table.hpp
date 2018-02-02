#ifndef LIBDNF_TABLE_HPP
#define LIBDNF_TABLE_HPP

#include "Cell.hpp"
#include "Column.hpp"
#include "Line.hpp"

#include "../tinyformat/tinyformat.hpp"

#include <memory>
#include <libsmartcols/libsmartcols.h>
#include <string>

class Table
{
public:
    Table() { table = scols_new_table(); }
    explicit Table(struct libscols_table *table) { this->table = table; };
    Table(const Table &table) { this->table = scols_copy_table(table.table); };
    ~Table() { scols_unref_table(table); };

    void setName(const std::string &name) { scols_table_set_name(table, name.c_str()); };
    void setColumnSeparator(const std::string &separator);
    void setLineSeparator(const std::string &separator) { scols_table_set_line_separator(table, separator.c_str()); };
    void setSymbols(struct libscols_symbols *symbols) { scols_table_set_symbols(table, symbols); };
    void setDefaultSymbols() { scols_table_set_default_symbols(table); };
    void setStream(FILE *stream) { scols_table_set_stream(table, stream); };
    void setTermforce(bool force) { scols_table_set_termforce(table, force); };
    void setTermwidth(size_t width) { scols_table_set_termwidth(table, width); };

    std::string getName() const { return scols_table_get_name(table); };
    std::string getColumnSeparator() { return scols_table_get_column_separator(table); };
    std::string getLineSeparator() { return scols_table_get_line_separator(table); };
    size_t getNumberOfColumns() { return scols_table_get_ncols(table); };
    size_t getNumberOfLines() { return scols_table_get_nlines(table); };
    std::unique_ptr<Cell> getTitle() { return std::unique_ptr<Cell>(new Cell(scols_table_get_title(table))); };
    std::unique_ptr<Column> getColumn(size_t n);
    std::unique_ptr<Line> getLine(size_t n) { return std::unique_ptr<Line>(new Line(scols_table_get_line(table, n))); };
    int getTermforce() { return scols_table_get_termforce(table); };

    struct libscols_symbols *getSymbols() { return scols_table_get_symbols(table); };
    size_t getTermwidth() { return scols_table_get_termwidth(table); };
    FILE *getStream() { return scols_table_get_stream(table); };

    bool isColorsEnabled() { return scols_table_colors_wanted(table) == 1; };
    bool isRaw() { return scols_table_is_raw(table) == 1; };
    bool isAscii() { return scols_table_is_ascii(table) == 1; };
    bool isJson() { return scols_table_is_json(table) == 1; };
    bool isNoheadings() { return scols_table_is_noheadings(table) == 1; };
    bool isEmpty() { return scols_table_is_empty(table) == 1; };
    bool isExport() { return scols_table_is_export(table) == 1; };
    bool isMaxout() { return scols_table_is_maxout(table) == 1; };
    bool isNowrap() { return scols_table_is_nowrap(table) == 1; };
    bool isNolinesep() { return scols_table_is_nolinesep(table) == 1; };
    bool isTree() { return scols_table_is_tree(table) == 1; };

    void enableColors(bool enable) { scols_table_enable_colors(table, enable); };
    void enableRaw(bool enable) { scols_table_enable_raw(table, enable); };
    void enableAscii(bool enable) { scols_table_enable_ascii(table, enable); };
    void enableJson(bool enable) { scols_table_enable_json(table, enable); };
    void enableNoheadings(bool enable) { scols_table_enable_noheadings(table, enable); };
    void enableExport(bool enable) { scols_table_enable_export(table, enable); };
    void enableMaxout(bool enable) { scols_table_enable_maxout(table, enable); };
    void enableNowrap(bool enable) { scols_table_enable_nowrap(table, enable); };
    void enableNolinesep(bool enable) { scols_table_enable_nolinesep(table, enable); };

    void addColumn(Column *column) { scols_table_add_column(table, column->getSmartColsColumn()); };
    void removeColumn(Column *column) { scols_table_remove_column(table, column->getSmartColsColumn()); };
    void removeColumns() { scols_table_remove_columns(table); };
    void moveColumn(Column *before, Column *toMove);
    std::shared_ptr<Column> newColumn(const std::string &name, double widthHint = 0, int flags = 0);
    std::unique_ptr<Column> nextColumn(struct libscols_iter *iter);

    void addLine(Line *line) { scols_table_add_line(table, line->getSmartColsLine()); };
    void removeLine(Line *line) { scols_table_remove_line(table, line->getSmartColsLine()); };
    void removeLines() { scols_table_remove_lines(table); };
    std::shared_ptr<Line> newLine(Line *parent = nullptr);
    std::unique_ptr<Line> nextLine(struct libscols_iter *itr);

    void reduceTermwidth(size_t reduce) { scols_table_reduce_termwidth(table, reduce); };

    void sort(Column *column) { scols_sort_table(table, column->getSmartColsColumn()); };
    void sortByTree() { scols_sort_table_by_tree(table); };

    void print() { tinyformat::printf("%s\n", toString()); };
    void print(Line *start, Line *end) { tinyformat::printf("%s\n", toString(start, end)); };

    std::string toString();
    std::string toString(Line *start, Line *end);

private:
    libscols_table *getSmartClsTable() const { return table; };

    struct libscols_table *table;
};

#endif //LIBDNF_TABLE_HPP
