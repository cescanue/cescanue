FROM	debian:bullseye

RUN		apt-get update
RUN		apt-get install -y nginx 

COPY ./conf/nginx.conf /etc/nginx/conf.d
COPY ./static/index.html /var/www/html/index.html

RUN mkdir -p /run/nginx

ENTRYPOINT ["nginx", "-g", "daemon off;"]