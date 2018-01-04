#!/bin/bash

mysql -u root < ./init/delete.sql;
mysql -u root < ./init/insert.sql;
mysql -u root < ./init/trigger.sql;
