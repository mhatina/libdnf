#ifndef LIBDNF_COLUMN_HPP
#define LIBDNF_COLUMN_HPP

#include "Cell.hpp"

#include <memory>
#include <libsmartcols/libsmartcols.h>

class Line;
class Table;

class Column
{
    friend class Line;
    friend class Table;

public:
    explicit Column(struct libscols_column *column) : column(column) { scols_ref_column(column); }
    Column(Column &column) { this->column = scols_copy_column(column.column); };
    ~Column() { scols_unref_column(column); };

    bool isTree() const { return scols_column_is_tree(column) == 1; };
    bool isTrunc() const { return scols_column_is_trunc(column) == 1; };
    bool isRight() const { return scols_column_is_right(column) == 1; };
    bool isStrictWidth() const { return scols_column_is_strict_width(column) == 1; };
    bool isHidden() const { return scols_column_is_hidden(column) == 1; };
    bool isNoextremes() const { return scols_column_is_noextremes(column) == 1; };
    bool isWrap() const { return scols_column_is_wrap(column) == 1; };
    bool isCustomwrap() const { return scols_column_is_customwrap(column) == 1; };

    int getFlags() const { return scols_column_get_flags(column); };
    double getWidthHint() const { return scols_column_get_whint(column); };
    size_t getWidth() const { return scols_column_get_width(column); };
    std::string getSafechars() const { return scols_column_get_safechars(column); };
    std::string getColor() const { return scols_column_get_color(column); };
    std::unique_ptr<Cell> getHeader() const;

    void setColor(const std::string &color) { scols_column_set_color(column, color.c_str()); };
    void setFlags(int flags) { scols_column_set_flags(column, flags); };
    void setSafechars(const std::string &safe) { scols_column_set_safechars(column, safe.c_str()); };
    void setWidthHint(double hint) { scols_column_set_whint(column, hint); };


    void setCompareFunction(int (*function)(struct libscols_cell *a, struct libscols_cell *b, void *), void *data);
    void setWrapFunction(size_t (*wrapChunksize)(const struct libscols_column *, const char *, void *),
                         char *(*wrapNextchunk)(const struct libscols_column *, char *, void *),
                         void *userdata);

    char *wrapnlNextchunk(char *data, void *userdata) { return scols_wrapnl_nextchunk(column, data, userdata); };
    size_t wrapnlChunksize(const char *data, void *userdata) { return scols_wrapnl_chunksize(column, data, userdata); };

private:
    libscols_column *getSmartColsColumn() const { return column; };

    struct libscols_column *column;
};


#endif //LIBDNF_COLUMN_HPP
