#include <functional>

#include "ConsoleTable.h"

// Public ConsoleTable

ConsoleTable::ConsoleTable(std::initializer_list<std::string> headers) : headers_{headers} {
  for (const auto &column : headers) {
    widths_.push_back(column.length());
  }
  setBoundaryStyle(0);
}


void ConsoleTable::setPadding(unsigned int n) {
  padding_ = n;
}


void ConsoleTable::setBoundaryStyle(unsigned int n) {

  switch (n) {
  case 0:
    style_ = BASIC_STYLE;
    break;

  case 1:
    style_ = INVISIBLE_STYLE;
    break;

  default:
    style_ = BASIC_STYLE;
    break;

  }
}

bool ConsoleTable::addRow(std::vector<std::string> row) {
  if (row.size() > widths_.size())
    throw std::invalid_argument{ "Appended row size must be same as header size" };

  auto r = std::vector<std::string>{ row };
  rows_.push_back(r);
  for (unsigned int i = 0; i < r.size(); ++i)
    widths_[i] = std::max(r[i].size(), widths_[i]);
  return true;
}

void ConsoleTable::remove(std::string id) {
  int index = 0;
  for (auto row : rows_) {
    if (row[0] == id) {
      removeRow(index);
      return;
    }
    index++;
  }
}

bool ConsoleTable::removeRow(unsigned int index) {
  if (index > rows_.size())
    return false;

  rows_.erase(rows_.begin() + index);
  return true;
}

void ConsoleTable::removeAll() {
  rows_.erase(rows_.begin(), rows_.end());
}


ConsoleTable &ConsoleTable::operator+=(std::initializer_list<std::string> row) {
  if (row.size() > widths_.size()) 
    throw std::invalid_argument{ "Appended row size must be same as header size" };

  addRow(row);
  return *this;
}


ConsoleTable &ConsoleTable::operator-=(const uint32_t rowIndex) {
  if (rows_.size() < rowIndex)
    throw std::out_of_range{ "Row index out of range." };

  removeRow(rowIndex);
}


std::string ConsoleTable::getLine(RowType rowType) const {
  std::stringstream line;
  line << rowType.left;
  for (unsigned int i = 0; i < widths_.size(); ++i) {
    for (unsigned int j = 0; j < (widths_[i] + padding_ + padding_); ++j)
      line << style_.horizontal;
    line << (i == widths_.size() - 1 ? rowType.right : rowType.intersect);
  }
  return line.str() + "\n";
}


std::string ConsoleTable::getHeaders(Headers headers) const {
  std::stringstream line;
  line << style_.vertical;
  for (unsigned int i = 0; i < headers.size(); ++i) {
    std::string text = headers[i];
    line << SPACE_CHARACTER * padding_ + text + SPACE_CHARACTER * (widths_[i] - text.length()) + SPACE_CHARACTER * padding_;
    line << style_.vertical;
  }
  line << "\n";
  return line.str();
}


std::string ConsoleTable::getRows(Rows rows) const {
  std::stringstream line;
  for (auto &row : rows) {
    line << style_.vertical;
    for (unsigned int j = 0; j < row.size(); ++j) {
      std::string text = row[j];
      line << SPACE_CHARACTER * padding_ + text + SPACE_CHARACTER * (widths_[j] - text.length()) + SPACE_CHARACTER * padding_;
      line << style_.vertical;
    }
    line << "\n";
  }

  return line.str();
}


std::ostream &operator<<(std::ostream &out, const ConsoleTable &consoleTable) {
  out << consoleTable.getLine(consoleTable.style_.top);
  out << consoleTable.getHeaders(consoleTable.headers_);
  out << consoleTable.getLine(consoleTable.style_.middle);
  out << consoleTable.getRows(consoleTable.rows_);
  out << consoleTable.getLine(consoleTable.style_.bottom);
  return out;
}

bool ConsoleTable::sort(bool ascending) {
  if (ascending)
    std::sort(rows_.begin(), rows_.end(), std::less<std::vector<std::string>>());
  else
    std::sort(rows_.begin(), rows_.end(), std::greater<std::vector<std::string>>());
  return true;
}

void ConsoleTable::updateRow(unsigned int row, unsigned int header, std::string data) {
  if (row > rows_.size() - 1)
    throw std::out_of_range{ "Row index out of range." };
  if (header > headers_.size() - 1)
    throw std::out_of_range{ "Header index out of range." };

  rows_[row][header] = data;
}

void ConsoleTable::updateHeader(unsigned int header, std::string text) {
  if (header > headers_.size())
    throw std::out_of_range{ "Header index out of range." };

  headers_[header] = text;
}


std::string operator*(const std::string &other, int repeats) {
  std::string ret;
  ret.reserve(other.size() * repeats);
  for (; repeats; --repeats)
    ret.append(other);
  return ret;
}
