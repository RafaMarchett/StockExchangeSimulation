#pragma once
#ifndef GRAPHS
#define GRAPHS
#include "header.hpp"

template <typename T> struct dataValues {
  T minValue, maxValue, amplitude;
  dataValues(T _minValue, T _maxValue)
      : minValue(_minValue), maxValue(_maxValue),
        amplitude(_maxValue - _minValue) {}
};

class Graphs {
public:
  template <typename T> void columnChart(const vector<T> &);
  template <typename T> void columnChart(std::stack<T> mainStack);

private:
  int plotLine, barWidth, startColumn, graphRow, graphColumns;
  size_t row, columns, leftPadding, mainVecSize;
  vector<string> screen;

  void resetAllVars();
  template <typename T> void drawColumnBars(const vector<T> &, dataValues<T> &);
  template <typename T> void fillColumns(const vector<T> &);
  template <typename T>
  void plotYAxisLabels(const vector<T> &, dataValues<T> &);
  template <typename T> void plotXAxisLabels(const vector<T> &);
};
#include "Graphs_Templates.hpp"
#endif // GRAPHS
