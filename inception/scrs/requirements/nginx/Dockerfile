FROM	debian:bullseye

RUN		apt-get update
RUN		apt-get install -y nginx \
                openssl

RUN mkdir /etc/nginx/ssl
RUN openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes \
       -out /etc/nginx/ssl/cescanue.crt \
       -keyout /etc/nginx/ssl/cescanue.key \
       -subj "/C=SP/ST=Barcelona/L=Barcelona/O=42/OU=cescanue/CN=cescanue.42.fr/"

COPY ./conf/nginx.conf /etc/nginx/conf.d

RUN mkdir -p /run/nginx

ENTRYPOINT ["nginx", "-g", "daemon off;"]