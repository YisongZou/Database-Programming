#include <iostream>
#include <pqxx/pqxx>
#include <fstream>
#include <sstream>
#include <string>

#include "exerciser.h"

using namespace std;
using namespace pqxx;
void createTables(string filename, connection *C) {
  /* Create SQL statement */
  string sql;
  string temp;
  std::ifstream ifs;
  ifs.open(filename.c_str(), std::ifstream::in);
  while (std::getline(ifs, temp)) {
    sql += temp;
  }
  ifs.close();

  /* Create a transactional object. */
  work W(*C);

  /* Execute SQL query */
  W.exec(sql);
  W.commit();
}


int main (int argc, char *argv[]) 
{

  //Allocate & initialize a Postgres connection object
  connection *C;

  try{
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd  hostaddr = 127.0.0.1 port = 5432");
    if (C->is_open()) {
      cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }


  //TODO:1 create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  createTables("create.sql", C);



  //TODO:2 load each table with rows from the provided source txt files



  //Test
  exercise(C);


  //Close database connection
  C->disconnect();
  }
catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}


