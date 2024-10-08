#!/bin/sh

#check if wp-config.php exist
if [ -f ./wp-config.php ]
then
	echo "wordpress already downloaded"
else

####### MANDATORY ##########
	wget http://wordpress.org/latest.tar.gz
	tar xfz latest.tar.gz
	mv wordpress/* .
	rm -rf latest.tar.gz
	rm -rf wordpress
	sed "s/username_here/$MYSQL_USER/g" wp-config-sample.php > tmp; cat tmp > wp-config-sample.php; rm tmp
	sed "s/password_here/$MYSQL_PASSWORD/g" wp-config-sample.php > tmp; cat tmp > wp-config-sample.php; rm tmp	
	sed "s/localhost/$MYSQL_HOSTNAME/g" wp-config-sample.php > tmp; cat tmp > wp-config-sample.php; rm tmp
	sed "s/database_name_here/$MYSQL_DATABASE/g" wp-config-sample.php > tmp; cat tmp > wp-config-sample.php; rm tmp
	cp wp-config-sample.php wp-config.php

####### BONUS ################
## redis ##
if [ "$BONUS" = "BONUS" ];
then	
	wp config set WP_REDIS_HOST redis --allow-root 
  	wp config set WP_REDIS_PORT 6379 --raw --allow-root
 	wp config set WP_CACHE_KEY_SALT $DOMAIN_NAME --allow-root
 	wp config set WP_REDIS_CLIENT phpredis --allow-root
	wp config set WP_REDIS_DISABLE_DROPIN_CHECK true --allow-root
	wp plugin install redis-cache --activate --allow-root
    wp plugin update --all --allow-root
	wp redis enable --allow-root
	sleep 3
	chmod 775 /var/www/html/wp-content
	chmod 775 /var/www/html/wp-content/object-cache.php
## Adminer ##	
	curl -L -O https://github.com/vrana/adminer/releases/download/v4.8.1/adminer-4.8.1.php && mv ./adminer-4.8.1.php /var/www/html/adminer.php 
###########
fi
fi

exec "$@"