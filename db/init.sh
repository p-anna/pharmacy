#!/bin/bash

mysql -u root < ./init/drop.sql;
mysql -u root < ./init/create.sql;
mysql -u root < ./init/insert.sql;
mysql -u root < ./init/trigger.sql;
mysql -u root < ./init/view.sql;
