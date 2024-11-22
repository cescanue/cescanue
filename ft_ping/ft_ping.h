/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:49:16 by cescanue          #+#    #+#             */
/*   Updated: 2024/11/22 10:36:15 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <sys/time.h>
# include <time.h>
# include <errno.h>
# include <signal.h>
# include <math.h>
# include <ctype.h>
# include <getopt.h>
# include <linux/errqueue.h>

// Configuración por defecto
# define DEFAULT_TTL 64
# define DEFAULT_TIMEOUT 1
# define DEFAULT_INTERVAL 1000000  // 1 second in microseconds
# define MAX_PACKET_SIZE 65535
# define MIN_PACKET_SIZE 8
# define DEFAULT_PACKET_SIZE 56
# define PING_HEADER_SIZE 8
# define ICMP_HEADER_SIZE 8

// Códigos de retorno
# define PING_ERROR -1
# define PING_SUCCESS 0

// Estructura principal que mantiene el estado del programa
typedef struct {
    int             stop_ping;          // Flag para detener el ping
    int             sockfd;             // Socket file descriptor
    size_t          packets_sent;       // Contador de paquetes enviados
    size_t          packets_received;   // Contador de paquetes recibidos
    size_t          errors_received;    // Contador de errores ICMP
    struct timeval  start_time;         // Tiempo de inicio
    double          min_rtt;            // RTT mínimo
    double          max_rtt;            // RTT máximo
    double          total_rtt;          // RTT total (para promedio)
    double          total_rtt_sq;       // Sum of squares (para mdev)
    int             verbose;            // Modo verbose (-v)
    int             flood;              // Modo flood (-f)
    size_t          count;              // Número de paquetes a enviar (-c)
    int             numeric;            // Solo salida numérica (-n)
    int             interval;           // Intervalo entre pings (-i)
    int             timeout;            // Timeout para respuestas (-W)
    int             ttl;                // Time to live (-t)
    int             pattern;            // Patrón para datos (-p)
    int             routing;            // Bypass routing table (-r)
    size_t          packet_size;        // Tamaño del paquete (-s)
    int             deadline;           // Tiempo límite (-w)
    unsigned char   *data_pattern;      // Patrón de datos
    char            *target;            // Host objetivo
    struct sockaddr_in dest_addr;       // Dirección de destino
    int             quiet;              // Modo silencioso
    struct timeval  last_send_time;     // Último tiempo de envío
    int             waiting;            // Estado de espera
    int             is_domain;          // Flag para indicar si el target es un dominio
} t_ping;

extern t_ping g_ping;

// Funciones de utilidad
void            cleanup_and_exit(int status);
unsigned short  calculate_checksum(void *b, int len);
void            check_root_privileges(void);
int             parse_pattern(const char *arg);
void            *ft_memset(void *b, int c, size_t len);
char            *ft_strdup(const char *s1);

// Funciones de socket
int             create_socket(void);

// Funciones de display
void            print_usage(void);
void            print_error(const char *msg);
void            print_host_error(const char *hostname);
void            print_ping_header(void);
void            print_response(const char *target, size_t bytes, 
                             uint16_t seq, uint8_t ttl, double rtt);
void            print_statistics(void);
void            print_verbose(const char *msg);
void            print_icmp_error(struct icmphdr *icmp_header, struct sockaddr_in *from);
void            print_reply(struct timeval *send_time, ssize_t bytes_received,
                          struct sockaddr_in *from, struct ip *ip_header,
                          struct icmphdr *icmp_reply);

// Funciones de manejo de paquetes
void            prepare_packet(void *packet, size_t size);
int             send_packet(void *packet, size_t size);
int             receive_packet(void *packet, size_t size, struct sockaddr_in *from);
void            handle_icmp_packet(void *packet, size_t size, struct sockaddr_in *from);

// Funciones de manejo de señales
void            signal_handler(int signo);
void            setup_signals(void);

#endif