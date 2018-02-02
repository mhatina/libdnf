#include "Column.hpp"

std::unique_ptr<Cell> Column::getHeader() const
{
    return std::unique_ptr<Cell>(new Cell(scols_column_get_header(column)));
}

void Column::setCompareFunction(int (*function)(struct libscols_cell *, struct libscols_cell *, void *), void *data)
{
    scols_column_set_cmpfunc(column, function, data);
}

void Column::setWrapFunction(size_t (*wrapChunksize)(const struct libscols_column *, const char *, void *),
                             char *(*wrapNextchunk)(const struct libscols_column *, char *, void *), void *userdata)
{
    scols_column_set_wrapfunc(column, wrapChunksize, wrapNextchunk, userdata);
}
