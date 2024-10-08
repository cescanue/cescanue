FROM	debian:bullseye

RUN	apt-get update && apt-get upgrade && apt-get -y install vsftpd
COPY conf/vsftpd.conf /tmp/vsftpd.conf
COPY conf/server_ftp.sh /usr/bin/server_ftp.sh
ENTRYPOINT ["sh", "/usr/bin/server_ftp.sh"]