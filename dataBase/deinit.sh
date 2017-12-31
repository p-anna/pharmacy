#!/bin/bash

mysql -u root < ./init/delete.sql;
mysql -u root < ./init/drop.sql;
