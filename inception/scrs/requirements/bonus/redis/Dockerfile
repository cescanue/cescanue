FROM	debian:bullseye

RUN		apt-get update
RUN		apt-get install -y redis \
		&& rm -rf /var/lib/apt/lists/*

COPY ./conf/redis.sh /usr/local/bin/redis.sh
EXPOSE 6379
CMD ["sh", "/usr/local/bin/redis.sh"]