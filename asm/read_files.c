#include "asm.h"

static t_file *get_content_file(char *name, char *buf, int fd)
{
    t_file *file;
    int     ret;
    char    *temp;

    if (!(file = (t_file *)ft_memalloc(sizeof(t_file))))
        return (NULL);
    if (!(file->name = ft_strdup(name)))
        return (NULL);
    if (!(file->content = ft_strnew(0)))
        return (NULL);
    while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
    {
        buf[ret] = '\0';
        temp = file->content;
        if (!(file->content = ft_strjoin(file->content, buf)))
            return (NULL);
        ft_strdel(&temp);
    }
    if (!(file->code = split_data(file->content, '\n')))
        return (NULL);
    return (file);
}


int read_files(t_asm *store, int argc, char **argv)
{
    t_list  *new;
    t_file  *elem;
    char    *buf;
    int     index;
    int     fd;

    
    index = 0;
    if (!(buf = (char *)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1))))
        return (0);
    while (++index < argc)
    {
        if ((fd = open(argv[index], O_RDONLY)) < 0)
            return (0);
        if (!(elem = get_content_file(argv[index], buf, fd)))
            return (0);
        if (!(new = ft_lstnew((void *)elem, sizeof(t_file))))
            return (0);
        ft_lstadd(&store->files, new);
        close(fd);
    }
    ft_strdel(&buf);
    return (1);
}