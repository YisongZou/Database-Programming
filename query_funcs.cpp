#include "query_funcs.h"
#include <string>

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
      sql = sql + "VALUES (" + W.quote(name) +  ", " + to_string(state_id) + ", " to_string(color_id) +  ", " + to_string(wins) + ", " + to_string(losses) +  "); ";

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
}


void query2(connection *C, string team_color)
{
}


void query3(connection *C, string team_name)
{
}


void query4(connection *C, string team_state, string team_color)
{
}


void query5(connection *C, int num_wins)
{
}
