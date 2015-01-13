ft_ls
=======

[![Build Status](https://travis-ci.org/Vallium/ft_ls.svg)](https://travis-ci.org/Vallium/ft_ls)

Man
--------
Synopsis : ./ft_ls [OPTION]... [FILE]...

Options : RSadgloprtu1

Description :

-1     list one file per line

`./ft_ls -a`
>do not ignore entries starting with "."

`./ft_ls -d`
>list directory entries instead of contents, and do not  dereference symbolic links

`./ft_ls -g`
>like -l, but do not list owner

-l     use a long listing format

-o     like -l, but do not list group information

-p, --indicator-style=slash
	      append / indicator to directories
	      
-r, --reverse
        reverse order while sorting

-t     sort by modification time

-u     with -lt: sort by, and show, access time with  -l:  show	access
	      time and sort by name otherwise: sort by access time
