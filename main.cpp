#include "mysql-connector/include/jdbc/cppconn/config.h"
#include "mysql-connector/include/jdbc/cppconn/driver.h"
#include "mysql-connector/include/jdbc/cppconn/connection.h"
#include "mysql-connector/include/jdbc/cppconn/statement.h"
#include "mysql-connector/include/jdbc/cppconn/prepared_statement.h"
#include "mysql-connector/include/jdbc/cppconn/resultset.h"
#include "mysql-connector/include/jdbc/cppconn/metadata.h"
#include "mysql-connector/include/jdbc/cppconn/resultset_metadata.h"
#include "mysql-connector/include/jdbc/cppconn/exception.h"
#include "mysql-connector/include/jdbc/cppconn/warning.h"
#include "mysql-connector/include/jdbc/mysql_connection.h"
#include "mysql-connector/include/jdbc/mysql_driver.h"
#include <iostream>

#define DBHOST "tcp://127.0.0.1:3306"
#define USER "umesh"
#define PASSWORD "1411"
#define DATABASE "mlearn_blog"


using namespace std;
using namespace sql;

static void retrieve_dbmetadata_and_print (Connection *dbcon) {

	if (dbcon -> isClosed()) {
		throw runtime_error("DatabaseMetaData FAILURE - database connection closed");
	}

	cout << "\nDatabase Metadata" << endl;
	cout << "-----------------" << endl;

	cout << boolalpha;

	/* The following commented statement won't work with Connector/C++ 1.0.5 and later */
	//auto_ptr < DatabaseMetaData > dbcon_meta (dbcon -> getMetaData());

	DatabaseMetaData *dbcon_meta = dbcon -> getMetaData();

	cout << "Database Product Name: " << dbcon_meta -> getDatabaseProductName() << endl;
	cout << "Database Product Version: " << dbcon_meta -> getDatabaseProductVersion() << endl;
	cout << "Database User Name: " << dbcon_meta -> getUserName() << endl << endl;

	cout << "Driver name: " << dbcon_meta -> getDriverName() << endl;
	cout << "Driver version: " << dbcon_meta -> getDriverVersion() << endl << endl;

	cout << "Database in Read-Only Mode?: " << dbcon_meta -> isReadOnly() << endl;
	cout << "Supports Transactions?: " << dbcon_meta -> supportsTransactions() << endl;
	cout << "Supports DML Transactions only?: " << dbcon_meta -> supportsDataManipulationTransactionsOnly() << endl;
	cout << "Supports Batch Updates?: " << dbcon_meta -> supportsBatchUpdates() << endl;
	cout << "Supports Outer Joins?: " << dbcon_meta -> supportsOuterJoins() << endl;
	cout << "Supports Multiple Transactions?: " << dbcon_meta -> supportsMultipleTransactions() << endl;
	cout << "Supports Named Parameters?: " << dbcon_meta -> supportsNamedParameters() << endl;
	cout << "Supports Statement Pooling?: " << dbcon_meta -> supportsStatementPooling() << endl;
	cout << "Supports Stored Procedures?: " << dbcon_meta -> supportsStoredProcedures() << endl;
	cout << "Supports Union?: " << dbcon_meta -> supportsUnion() << endl << endl;

	cout << "Maximum Connections: " << dbcon_meta -> getMaxConnections() << endl;
	cout << "Maximum Columns per Table: " << dbcon_meta -> getMaxColumnsInTable() << endl;
	cout << "Maximum Columns per Index: " << dbcon_meta -> getMaxColumnsInIndex() << endl;
	cout << "Maximum Row Size per Table: " << dbcon_meta -> getMaxRowSize() << " bytes" << endl;

	cout << "\nDatabase schemas: " << endl;

	auto_ptr < ResultSet > rs ( dbcon_meta -> getSchemas());

	cout << "\nTotal number of schemas = " << rs -> rowsCount() << endl;
	cout << endl;

	int row = 1;

	while (rs -> next()) {
		cout << "\t" << row << ". " << rs -> getString("TABLE_SCHEM") << endl;
		++row;
	} // while

	cout << endl << endl;

} // retrieve_dbmetadata_and_print()

void connect_db(){
    sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
    driver = get_driver_instance();
    con = driver -> connect(DBHOST, USER, PASSWORD);
    con -> setSchema(DATABASE);
    retrieve_dbmetadata_and_print (con);    
    cout<<"here";
}



int main() {
    cout << "Hi";
    connect_db();
}

