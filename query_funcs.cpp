#include "query_funcs.h"
#include <string>
#include <iomanip>
using namespace std;
void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{
  /* Create a transactional object. */
      work W(*C);
  /* Create SQL statement */
  string sql = "INSERT INTO player (team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg)";
  sql = sql + "VALUES (" + to_string(team_id) + ", " + to_string(jersey_num) +", " +  W.quote(first_name) + ", " + W.quote(last_name) +  ", " +  to_string(mpg) + ", " + to_string(ppg) +", "  + to_string(rpg) + ", " +  to_string(apg) +  ", " +  to_string(spg) + ", " + to_string(bpg) + "); ";
      
      /* Execute SQL query */
      W.exec( sql );
      W.commit();
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{
 /* Create a transactional object. */
      work W(*C);
  /* Create SQL statement */
      string sql = "INSERT INTO team (name, state_id, color_id, wins, losses)";
      sql = sql + "VALUES (" + W.quote(name) +  ", " + to_string(state_id) + ", "+ to_string(color_id) +  ", " + to_string(wins) + ", " + to_string(losses) +  "); ";

      /* Execute SQL query */
      W.exec( sql );
      W.commit();
}


void add_state(connection *C, string name)
{
/* Create a transactional object. */
      work W(*C);
  /* Create SQL statement */
      string sql = "INSERT INTO state (name) VALUES (";
      sql = sql + W.quote(name) +  "); ";
      
      /* Execute SQL query */
      W.exec( sql );
      W.commit();

}


void add_color(connection *C, string name)
{
/* Create a transactional object. */
      work W(*C);
  /* Create SQL statement */
      string sql = "INSERT INTO color (name) VALUES (";
      sql = sql	+ W.quote(name) +  "); ";

      /* Execute SQL query */
      W.exec( sql );
      W.commit();
  
}


void query1(connection *C,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{

  /* Create SQL statement */
  string sql = "SELECT * from PLAYER";
  int counter = 0;
  if (use_mpg) {
    if (counter == 0)
      sql += " WHERE ";
    else
      sql += " AND ";
    sql = sql +  "(mpg between " +  to_string(min_mpg) +  " AND " +  to_string(max_mpg) +  ") ";
    counter ++;
  }
  if (use_ppg) {
    if (counter == 0)
      sql += " WHERE ";
    else
      sql += " AND ";
    sql  = sql + "(ppg between " + to_string(min_ppg) +  " AND " + to_string(max_ppg) + ") ";
    counter ++;
  }

  if (use_rpg) {
    if (counter == 0)
      sql +=" WHERE ";
    else
      sql += " AND ";
    sql  = sql +  "(rpg between " +  to_string(min_rpg) + " AND " +  to_string(max_rpg) + ") ";
    counter++;
  }

  if (use_apg) {
    if (counter == 0)
      sql += " WHERE ";
    else
      sql += " AND ";
    sql = sql +  "(apg between " + to_string(min_apg) + " AND " +  to_string(max_apg) +  ") ";
    counter ++;
  }

  if (use_spg) {
    if (counter == 0)
      sql += " WHERE ";
    else
      sql += " AND ";
    sql  = sql +  "(spg between " + to_string(min_spg) +  " AND " + to_string(max_spg) + ") ";
    counter ++;
  }

  if (use_bpg) {
    if (counter == 0)
      sql += " WHERE ";
    else
      sql += " AND ";
    sql = sql + "(bpg between " + to_string(min_bpg) +  " AND " + to_string(max_bpg) + ") ";
    counter ++;
  }
  
  sql += ";";

  
  /* Create a non-transactional object. */
  nontransaction N(*C);
  
  /* Execute SQL query */
  result R( N.exec( sql ));

   /* List down all the records */
  cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG\n";
  for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
    cout << c[0].as<int>() << " " << c[1].as<int>() << " " << c[2].as<int>()
         << " " << c[3].as<string>() << " " << c[4].as<string>() << " "
         << c[5].as<int>() << " " << c[6].as<int>() << " " << c[7].as<int>()
         << " " << c[8].as<int>() << " " << fixed << setprecision(1)
         << c[9].as<double>() << " " << c[10].as<double>() << "\n";
  }
}


void query2(connection *C, string team_color)
{
  work W(*C);
/* Create SQL statement */
  string sql = "SELECT TEAM.NAME FROM TEAM ,COLOR  WHERE TEAM.COLOR_ID = COLOR.COLOR_ID AND COLOR.NAME = ";
  sql = sql + W.quote(team_color) + " ;";
  W.commit();
  nontransaction N(*C);
  result R(N.exec(sql));
  cout << "NAME\n";
  for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
    cout << c[0].as<string>() << "\n";
  }
}


void query3(connection *C, string team_name)
{
work W(*C);
  string sql = "SELECT PLAYER.FIRST_NAME, PLAYER.LAST_NAME FROM PLAYER, TEAM WHERE PLAYER.TEAM_ID = TEAM.TEAM_ID AND TEAM.name = " +
               W.quote(team_name) + " ORDER BY PPG DESC;";
  W.commit();
  nontransaction N(*C);
  result R(N.exec(sql));
  cout << "FIRST_NAME LAST_NAME\n";
  for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
    cout << c[0].as<string>() << " " << c[1].as<string>() << "\n";
  }
}


void query4(connection *C, string team_state, string team_color)
{
  work W(*C);
  string sql = "SELECT PLAYER.FIRST_NAME, PLAYER.LAST_NAME, PLAYER.UNIFORM_NUM FROM PLAYER, TEAM, STATE, COLOR WHERE PLAYER.TEAM_ID"
    " = TEAM.TEAM_ID AND TEAM.STATE_ID = STATE.STATE_ID AND TEAM.COLOR_ID = COLOR.COLOR_ID AND STATE.NAME = " + W.quote(team_state) +
    "AND COLOR.NAME = " +  W.quote(team_color) + ";"; 
  W.commit();
  nontransaction N(*C);
  result R(N.exec(sql));
  cout << "FIRST_NAME LAST_NAME UNIFORM_NUM\n";
  for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
    cout << c[0].as<string>() << " " << c[1].as<string>() << " " << c[2].as<int>() << "\n";
  }
}


void query5(connection *C, int num_wins)
{
  string sql = "SELECT PLAYER.FIRST_NAME, PLAYER.LAST_NAME, TEAM.NAME, TEAM.WINS FROM PLAYER, TEAM WHERE PLAYER.TEAM_ID"
    " = TEAM.TEAM_ID AND TEAM.WINS >" + to_string(num_wins) + ";";
  nontransaction N(*C);
  result R(N.exec(sql));
  cout << "FIRST_NAME LAST_NAME TEAM_NAME WINS\n";
  for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
    cout << c[0].as<string>() << " " << c[1].as<string>() << " " << c[2].as<string>() << " " << c[3].as<int>() << "\n";
  }
}
