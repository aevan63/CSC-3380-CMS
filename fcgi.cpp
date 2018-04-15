// Written by Jackie Bowers
//queries an sql database with requests from a webserver with fastcgi
//probably doesnt work yet

#include <iostream>
#include <fstream>
#include <fastcgi++/request.hpp> // from https://github.com/eddic/fastcgipp
#include <fastcgi++/manager.hpp>
#include <fastcgi++/http.hpp>
#include <mysql.h> // from MariaDB's website
#include "MariaDBInitializer.h"
#include "MariaDB.h"


class Queries: public Fastcgipp::Request<char> {
	using Fastcgipp::Encoding;
	//with the fastcgi++ library the response method of any request class
	//seems to be called automatically when it is needed by the manager
	bool response() {
		string website = "FMS.com"; //placeholder, ofc.
		MariaDB sqlObj = MariaDB();
		sqlObj.queryResult = sqlObj.query(buildQuery(environment()));
		MYSQL_ROW* stringRes = sqlObj.stringRES();

	        buildHTML page = buildHTML(stringRes, environment(), website);

	        // out sends page to server w/ fastcgi++
	        out << page.fixHTML(page.buildFromSQL());

	        sqlObj.close();
		return true;
	}
};

int main( int argc, char *argv[]) {
         Fastcgipp::Manager<Queries> manager;
         manager.setupSignals();
         manager.listen();
         manager.start();
         manager.join();
         return 0;
}
