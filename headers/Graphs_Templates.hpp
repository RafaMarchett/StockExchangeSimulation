#pragma once
#include "Graphs.h"
#include "SystemFunctions.h"

template <typename T> void Graphs::columnChart(const vector<T> &mainVec) {
  SysFuncs funcsManager;
  row = funcsManager.getTerminalLines() - 3;
  columns = funcsManager.getTerminalColumns();

  mainVecSize = mainVec.size();
  struct dataValues<T> T_Values(
      *std::min_element(mainVec.begin(), mainVec.end()),
      *std::max_element(mainVec.begin(), mainVec.end()));
  if (T_Values.amplitude == 0)
    T_Values.amplitude = 1.0;

  leftPadding = std::to_string(T_Values.maxValue).size();
  const int bottomPadding = 3;
  graphRow = row - bottomPadding;
  graphColumns = columns - leftPadding;
  barWidth = graphColumns / mainVecSize;

  if (barWidth == 0)
    barWidth = 1;

  screen = vector<string>(row, string(columns, ' '));
  drawColumnBars(mainVec, T_Values);
  plotYAxisLabels(mainVec, T_Values);

  plotXAxisLabels(mainVec);
  cout << '\n';
  for (auto &it : screen) {
    static size_t counter{0};
    cout << it << (counter < row ? '\n' : ' ');
    counter++;
  }
  funcsManager.pressEnterToContinue();
}

template <typename T>
void Graphs::drawColumnBars(const vector<T> &mainVec, dataValues<T> &T_Values) {
  for (size_t i = 0; i < mainVecSize; ++i) {
    startColumn = leftPadding + i * barWidth;
    T normalizedValue = (mainVec[i] - T_Values.minValue) / T_Values.amplitude;
    plotLine =
        graphRow - 1 - static_cast<int>(normalizedValue * (graphRow - 1.0));

    if (plotLine < 0)
      plotLine = 0;
    if (plotLine >= graphRow)
      plotLine = graphRow - 1;

    fillColumns(mainVec);
  }
}
template <typename T> void Graphs::fillColumns(const vector<T> &mainVec) {
  for (int xOffset = 0; xOffset < barWidth; ++xOffset) {
    size_t currentColumn = startColumn + xOffset;
    if (currentColumn >= leftPadding && currentColumn < columns) {
      for (int k = plotLine; k < graphRow; ++k) {
        if (k >= 0) {

          screen[k][currentColumn] = '#';
        }
      }
    }
  }
}

template <typename T>
void Graphs::plotYAxisLabels(const vector<T> &mainVec,
                             dataValues<T> &T_Values) {

  std::vector<T> yLabelsValues = {T_Values.minValue, T_Values.maxValue};
  for (T value : yLabelsValues) {

    int yPos =
        graphRow - 1 -
        static_cast<int>(((value - T_Values.minValue) / T_Values.amplitude) *
                         (graphRow - 1.0));

    std::string label = std::to_string(value);
    for (size_t j = 0; j < label.length(); ++j) {
      if (j < leftPadding - 1 && yPos >= 0 && yPos < graphRow) {
        screen[yPos][leftPadding - 1 - j] = label[label.length() - 1 - j];
      }
    }
  }
}
template <typename T> void Graphs::plotXAxisLabels(const vector<T> &mainVec) {

  for (size_t i = 0; i < mainVecSize; ++i) {
    if (i % (mainVecSize / 5 + 1) == 0 || i == mainVecSize - 1) {
      int xPos = leftPadding + i * barWidth + barWidth / 2;
      std::string label = std::to_string(i);
      for (size_t j = 0; j < label.length(); ++j) {
        if (xPos + j < columns && row - 1 >= 0 && row - 1 < row) {
          screen[row - 1][xPos - label.length() / 2 + j] = label[j];
        }
      }
    }
  }
}
