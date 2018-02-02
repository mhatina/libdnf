#ifndef LIBDNF_CELL_HPP
#define LIBDNF_CELL_HPP

#include <libsmartcols/libsmartcols.h>
#include <string>

class Cell
{
public:
    explicit Cell(struct libscols_cell *cell) : cell(cell) {}
    Cell(const Cell &cell) { scols_cell_copy_content(this->cell, cell.cell); };

    void reset() { scols_reset_cell(cell); };

    int getFlags() { return scols_cell_get_flags(cell); };
    int getAlignment() { return scols_cell_get_alignment(cell); };
    std::string getData() { return scols_cell_get_data(cell); };
    std::string getColor() { return scols_cell_get_color(cell); };
    void *getUserdata() { return scols_cell_get_userdata(cell); };

    void setData(const std::string &data) { scols_cell_set_data(cell, data.c_str()); };
    void setColor(const std::string &color) { scols_cell_set_color(cell, color.c_str()); };
    void setFlags(int flags) { scols_cell_set_flags(cell, flags); };
    void setUserdata(void *data) { scols_cell_set_userdata(cell, data); };

    bool operator==(const Cell &cell) const { return scols_cmpstr_cells(this->cell, cell.cell, nullptr) == 0; };

private:
    libscols_cell *getSmartColsCell() const { return cell; };

    struct libscols_cell *cell;
};



#endif //LIBDNF_CELL_HPP
