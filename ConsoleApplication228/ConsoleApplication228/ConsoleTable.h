#ifndef CONSOLETABLE_CONSOLETABLE_H
#define CONSOLETABLE_CONSOLETABLE_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>


class ConsoleTable {
public:

  typedef std::vector<std::string> Headers;
  typedef std::vector<std::vector<std::string>> Rows;
  typedef std::vector<std::size_t> Widths;

  ConsoleTable(std::initializer_list<std::string> headers);

  void setPadding(unsigned int n);

  /// ����� ������: 0 �� ���������
  /// n = 0 : �������
  /// n = 1 : ���������
  void setBoundaryStyle(unsigned int n);

  bool sort(bool ascending);

  bool addRow(std::vector<std::string> row);
  bool removeRow(unsigned int index);
  void updateRow(unsigned int row, unsigned int header, std::string data);
  void updateHeader(unsigned int header, std::string text);

  /// �������� ��� addRow()
  ConsoleTable &operator+=(std::initializer_list<std::string> row);

  /// �������� ��� removeRow()
  ConsoleTable &operator-=(uint32_t rowIndex);

private:

  Headers headers;
  Rows rows;
  Widths widths;

  struct RowType {
    std::string left;
    std::string intersect;
    std::string right;
  };

  struct TableStyle {
    std::string horizontal;
    std::string vertical;
    RowType top;
    RowType middle;
    RowType bottom;
  };


  TableStyle BasicStyle = { "-", "|", { "+", "+", "+" }, { "+", "+", "+" }, { "+", "+", "+" } };
  TableStyle InvisibleStyle = { " ", " ", { " ", " ", " " }, { " ", " ", " " }, { " ", " ", " " } };

  TableStyle style = BasicStyle;
  const std::string SPACE_CHARACTER = " ";
  unsigned int padding = 1;


  // ���������� ��������������� ������
  std::string getLine(RowType rowType) const;

  // ���������� ��������������� ���������
  std::string getHeaders(Headers headers) const;

  // ���������� ��� ������ �������
  std::string getRows(Rows rows) const;

  friend std::ostream &operator<<(std::ostream &out, const ConsoleTable &consoleTable);
};


// �������� ��������
std::string operator*(const std::string &other, int repeats);


#endif //CONSOLETABLE_CONSOLETABLE_H