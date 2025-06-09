#include "../headers/Graphs.h"

void Graphs::resetAllVars() {
  plotLine = barWidth = startColumn = graphRow = graphColumns = 0;
  row = columns = leftPadding = mainVecSize = 0;
  screen = {""};
  SysFuncs funcsManager;
  row = funcsManager.getTerminalLines() - 3;
  columns = funcsManager.getTerminalColumns();
}
