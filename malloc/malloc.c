/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:28:28 by cescanue          #+#    #+#             */
/*   Updated: 2024/11/07 12:51:03 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

t_zone	        g_zone = {NULL, NULL, NULL};
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void *allocate_block(size_t block_size, size_t user_size, void **zone)
{
    pthread_mutex_lock(&g_mutex);
    if (*zone == NULL) {
        size_t total_size = (ALIGN(block_size) + ALIGN(sizeof(t_block))) * MINBOOK;
        size_t page_size = getpagesize();
        total_size = ((total_size + page_size - 1) / page_size) * page_size;
        *zone = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
        if (*zone == MAP_FAILED)
        {
            pthread_mutex_unlock(&g_mutex);
            return NULL;
        }
        void *ptr = *zone;
        ((t_block *)ptr)->signature = BLOCK_SIGNATURE;
        ((t_block *)ptr)->size = user_size;
        ((t_block *)ptr)->free = 0;
        ((t_block *)ptr)->num = 0;
        ((t_block *)ptr)->next = NULL;
        pthread_mutex_unlock(&g_mutex);
        return (char *)ptr + ALIGN(sizeof(t_block));
    }
    
	void *ptr = *zone;
	
    while (((t_block*)ptr)->next != NULL && ((t_block*)ptr)->free == 0)
        ptr = ((t_block*)ptr)->next;
    if (((t_block *)ptr)->free == 1) {
        ((t_block *)ptr)->free = 0;
        ((t_block *)ptr)->size = user_size;
        pthread_mutex_unlock(&g_mutex);
        return (char *)ptr + ALIGN(sizeof(t_block));
    }
    if (((t_block*)ptr)->next == NULL) {
        if ((((t_block*)ptr)->num + 1) % MINBOOK != 0) {
            ((t_block*)ptr)->next = (t_block *)((char *)ptr + ALIGN(block_size) + ALIGN(sizeof(t_block)));
        } else {
            size_t total_size = (ALIGN(block_size) + ALIGN(sizeof(t_block))) * MINBOOK;
            size_t page_size = getpagesize();
            total_size = ((total_size + page_size - 1) / page_size) * page_size;
            ((t_block*)ptr)->next = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
            if (((t_block*)ptr)->next == MAP_FAILED)
            {
                pthread_mutex_unlock(&g_mutex);
                return NULL;
            }
        }
        ((t_block *)((t_block*)ptr)->next)->signature = BLOCK_SIGNATURE;
        ((t_block *)((t_block*)ptr)->next)->size = user_size;
        ((t_block *)((t_block*)ptr)->next)->free = 0;
        ((t_block *)((t_block*)ptr)->next)->num = ((t_block*)ptr)->num + 1;
        ((t_block *)((t_block*)ptr)->next)->next = NULL;
        pthread_mutex_unlock(&g_mutex);
        return (char *)((t_block*)ptr)->next + ALIGN(sizeof(t_block));
    }
    pthread_mutex_unlock(&g_mutex);
    return NULL;
}

void *allocate_block_large(size_t block_size, void **zone)
{
    pthread_mutex_lock(&g_mutex);
    size_t total_size = (ALIGN(block_size) + ALIGN(sizeof(t_block)));
    size_t page_size = getpagesize();
    total_size = ((total_size + page_size - 1) / page_size) * page_size;
    if (*zone == NULL)
    {
        *zone = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
        if (*zone == MAP_FAILED)
        {
            pthread_mutex_unlock(&g_mutex);
            return NULL;
        }
        void *ptr = *zone;
        ((t_block *)ptr)->signature = BLOCK_SIGNATURE;
        ((t_block *)ptr)->size = block_size;
        ((t_block *)ptr)->free = 0;
        ((t_block *)ptr)->num = 0;
        ((t_block *)ptr)->next = NULL;
        pthread_mutex_unlock(&g_mutex);
        return (char *)ptr + ALIGN(sizeof(t_block));
    }
    
	void *ptr = *zone;
    
	while (((t_block *)ptr)->next != NULL)
        ptr = ((t_block*)ptr)->next;
    ((t_block*)ptr)->next = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (((t_block*)ptr)->next == MAP_FAILED)
    {
        pthread_mutex_unlock(&g_mutex);
        return NULL;
    }
    ((t_block *)((t_block*)ptr)->next)->signature = BLOCK_SIGNATURE;
    ((t_block *)((t_block*)ptr)->next)->size = block_size;
    ((t_block *)((t_block*)ptr)->next)->free = 0;
    ((t_block *)((t_block*)ptr)->next)->num = ((t_block*)ptr)->num + 1;
    ((t_block *)((t_block*)ptr)->next)->next = NULL;
    pthread_mutex_unlock(&g_mutex);
    return (char *)((t_block*)ptr)->next + ALIGN(sizeof(t_block));
}

void free(void *ptr)
{
    if (ptr == NULL)
        return;

    t_block *block = (t_block *)((char *)ptr - ALIGN(sizeof(t_block)));

    if (block->signature != BLOCK_SIGNATURE)
        return;
    pthread_mutex_lock(&g_mutex);

    size_t block_size = block->size;

    if (block_size > SMALL)
    {
        t_block *current = (t_block *)g_zone.large;
        t_block *prev = NULL;
        while (current != NULL)
        {
            if (current == block)
            {
                if (prev == NULL)
                    g_zone.large = current->next;
                else
                    prev->next = current->next;
                size_t total_size = ALIGN(sizeof(t_block)) + ALIGN(block->size);
                size_t page_size = getpagesize();
                total_size = ((total_size + page_size - 1) / page_size) * page_size;
                munmap((void *)block, total_size);
                pthread_mutex_unlock(&g_mutex);
                return;
            }
            prev = current;
            current = current->next;
        }
    }
    else
        block->free = 1;
    pthread_mutex_unlock(&g_mutex);
}

void *realloc(void *ptr, size_t size)
{
    if (ptr == NULL)
        return malloc(size);
    if (size == 0)
    {
        free(ptr);
        return NULL;
    }

    t_block *block = (t_block *)((char *)ptr - ALIGN(sizeof(t_block)));

    if (block->signature != BLOCK_SIGNATURE)
        return NULL;
    pthread_mutex_lock(&g_mutex);
    if (size <= block->size)
    {
        pthread_mutex_unlock(&g_mutex);
        return ptr;
    }
    pthread_mutex_unlock(&g_mutex);
    void *new_ptr = malloc(size);
    if (new_ptr == NULL)
        return NULL;
    ft_memcpy(new_ptr, ptr, block->size);
    free(ptr);
    return new_ptr;
}

static void print_address_hex(void *addr)
{
    unsigned long addr_value = (unsigned long)addr;
    char buffer[17];
    char hex_digits[] = "0123456789ABCDEF";
    int i = 15;
	
    buffer[16] = '\0';
    while (i >= 0)
    {
        buffer[i] = hex_digits[addr_value % 16];
        addr_value /= 16;
        i--;
    }
    ft_putstr_fd("0x", 1);
    ft_putstr_fd(buffer, 1);
}

static void print_number(size_t num)
{
    char buffer[21];
    int i = 20;
    buffer[20] = '\0';

    if (num == 0)
    {
        buffer[--i] = '0';
    }
    else
    {
        while (num > 0 && i > 0)
        {
            buffer[--i] = '0' + (num % 10);
            num /= 10;
        }
    }
    ft_putstr_fd(&buffer[i], 1);
}

void show_alloc_mem(void)
{
    pthread_mutex_lock(&g_mutex);

    size_t total = 0;
    t_block *ptr;

    ft_putstr_fd("TINY : ", 1);
    if (g_zone.tiny)
        print_address_hex(g_zone.tiny);
    else
        ft_putstr_fd("No allocations", 1);
    ft_putstr_fd("\n", 1);
    ptr = (t_block *)g_zone.tiny;
    while (ptr)
    {
        if (ptr->free == 0)
        {
            print_address_hex((char *)ptr + ALIGN(sizeof(t_block)));
            ft_putstr_fd(" - ", 1);
            print_address_hex((char *)ptr + ALIGN(sizeof(t_block)) + ptr->size);
            ft_putstr_fd(" : ", 1);
            print_number(ptr->size);
            ft_putstr_fd(" bytes\n", 1);
            total += ptr->size;
        }
        ptr = ptr->next;
    }

    ft_putstr_fd("SMALL : ", 1);
    if (g_zone.small)
        print_address_hex(g_zone.small);
    else
        ft_putstr_fd("No allocations", 1);
    ft_putstr_fd("\n", 1);
    ptr = (t_block *)g_zone.small;
    while (ptr)
    {
        if (ptr->free == 0)
        {
            print_address_hex((char *)ptr + ALIGN(sizeof(t_block)));
            ft_putstr_fd(" - ", 1);
            print_address_hex((char *)ptr + ALIGN(sizeof(t_block)) + ptr->size);
            ft_putstr_fd(" : ", 1);
            print_number(ptr->size);
            ft_putstr_fd(" bytes\n", 1);
            total += ptr->size;
        }
        ptr = ptr->next;
    }

    ft_putstr_fd("LARGE : ", 1);
    if (g_zone.large)
        print_address_hex(g_zone.large);
    else
        ft_putstr_fd("No allocations", 1);
    ft_putstr_fd("\n", 1);
    ptr = (t_block *)g_zone.large;
    while (ptr)
    {
        if (ptr->free == 0)
        {
            print_address_hex((char *)ptr + ALIGN(sizeof(t_block)));
            ft_putstr_fd(" - ", 1);
            print_address_hex((char *)ptr + ALIGN(sizeof(t_block)) + ptr->size);
            ft_putstr_fd(" : ", 1);
            print_number(ptr->size);
            ft_putstr_fd(" bytes\n", 1);
            total += ptr->size;
        }
        ptr = ptr->next;
    }

    ft_putstr_fd("Total : ", 1);
    print_number(total);
    ft_putstr_fd(" bytes\n", 1);

    pthread_mutex_unlock(&g_mutex);
}

static void print_byte_hex(unsigned char byte)
{
    char hex_digits[] = "0123456789ABCDEF";
    char hex[3];

    hex[0] = hex_digits[byte / 16];
    hex[1] = hex_digits[byte % 16];
    hex[2] = '\0';

    ft_putstr_fd(hex, 1);
}

static void print_memory_hex(void *addr, size_t size)
{
    size_t i;
    unsigned char *ptr = (unsigned char *)addr;
    size_t line_offset = 0;

    while (line_offset < size)
    {
        print_address_hex(ptr + line_offset);
        ft_putstr_fd(" : ", 1);
        for (i = 0; i < 16 && (line_offset + i) < size; i++)
        {
            print_byte_hex(ptr[line_offset + i]);
            ft_putchar_fd(' ', 1);
        }
        ft_putstr_fd("\n", 1);
        line_offset += 16;
    }
}

void show_alloc_mem_hex(void)
{
    pthread_mutex_lock(&g_mutex);

    t_block *ptr;
    size_t total = 0;
	
    ft_putstr_fd("TINY : ", 1);
    if (g_zone.tiny)
        print_address_hex(g_zone.tiny);
    else
        ft_putstr_fd("No allocations", 1);
    ft_putstr_fd("\n", 1);
    ptr = (t_block *)g_zone.tiny;
    while (ptr)
    {
        if (ptr->free == 0)
        {
            print_address_hex((char *)ptr + ALIGN(sizeof(t_block)));
            ft_putstr_fd(" - ", 1);
            print_address_hex((char *)ptr + ALIGN(sizeof(t_block)) + ptr->size);
            ft_putstr_fd(" : ", 1);
            print_number(ptr->size);
            ft_putstr_fd(" bytes\n", 1);
            print_memory_hex((char *)ptr + ALIGN(sizeof(t_block)), ptr->size);
            total += ptr->size;
        }
        ptr = ptr->next;
    }
    ft_putstr_fd("SMALL : ", 1);
    if (g_zone.small)
        print_address_hex(g_zone.small);
    else
        ft_putstr_fd("No allocations", 1);
    ft_putstr_fd("\n", 1);

    ptr = (t_block *)g_zone.small;
    while (ptr)
    {
        if (ptr->free == 0)
        {
            print_address_hex((char *)ptr + ALIGN(sizeof(t_block)));
            ft_putstr_fd(" - ", 1);
            print_address_hex((char *)ptr + ALIGN(sizeof(t_block)) + ptr->size);
            ft_putstr_fd(" : ", 1);
            print_number(ptr->size);
            ft_putstr_fd(" bytes\n", 1);
            print_memory_hex((char *)ptr + ALIGN(sizeof(t_block)), ptr->size);
            total += ptr->size;
        }
        ptr = ptr->next;
    }

    ft_putstr_fd("LARGE : ", 1);
    if (g_zone.large)
        print_address_hex(g_zone.large);
    else
        ft_putstr_fd("No allocations", 1);
    ft_putstr_fd("\n", 1);

    ptr = (t_block *)g_zone.large;
    while (ptr)
    {
        if (ptr->free == 0)
        {
            print_address_hex((char *)ptr + ALIGN(sizeof(t_block)));
            ft_putstr_fd(" - ", 1);
            print_address_hex((char *)ptr + ALIGN(sizeof(t_block)) + ptr->size);
            ft_putstr_fd(" : ", 1);
            print_number(ptr->size);
            ft_putstr_fd(" bytes\n", 1);
            print_memory_hex((char *)ptr + ALIGN(sizeof(t_block)), ptr->size);
            total += ptr->size;
        }
        ptr = ptr->next;
    }
    ft_putstr_fd("Total : ", 1);
    print_number(total);
    ft_putstr_fd(" bytes\n", 1);

    pthread_mutex_unlock(&g_mutex);
}

void *malloc(size_t size)
{
    if (size <= TINY)
        return allocate_block(TINY, size, &g_zone.tiny);
    else if (size <= SMALL)
        return allocate_block(SMALL, size, &g_zone.small);
    else
        return allocate_block_large(size, &g_zone.large);    
    return NULL;
}
