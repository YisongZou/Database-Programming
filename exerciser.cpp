#include "exerciser.h"

void exercise(connection *C)
{
  query1(C, 1, 35, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  query1(C, 1, 35, 40, 0, 18, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  query1(C, 1, 35, 40, 1, 18, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  query1(C, 0, 35, 40, 0, 18, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  query2(C, "DarkBlue");
  query3(C, "UNC");
  query3(C, "Duke");
  query4(C, "NC", "LightBlue");
  query4(C, "NC", "DarkBlue");
  query5(C, 13);
  add_player(C, 1, 1, "cjw", "mjt", 1, 1, 1, 1, 1, 1);
  query1(C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  query2(C, "nb");
  query3(C, "666");
  query4(C, "NC", "Red");
  query5(C, 5);
  add_player(C, 1, 60, "66666", "88888", 20, 20, 10, 10, 5.3, 5.3);
  add_team(C, "JOKER", 10, 3, 20, 0);
  add_state(C, "N/A");
  add_color(C, "wierd");
  query1(C, 1, 10, 30, 0, 0, 40, 0, 0, 6, 0, 0, 5, 0, 0.0, 10.0, 0, 0.0, 10.0);
 }
