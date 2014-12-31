git filter-branch -f --env-filter '
oldname="Antoine DOUSSAUD"
oldemail="adoussau@e1r9p11.42.fr"
newname="Spectre"
newemail="antoine@doussaud.org"
[ "$GIT_AUTHOR_EMAIL"="$oldemail" ] && GIT_AUTHOR_EMAIL="$newemail"
[ "$GIT_COMMITTER_EMAIL"="$oldemail" ] && GIT_COMMITTER_EMAIL="$newemail"
[ "$GIT_AUTHOR_NAME"="$oldname" ] && GIT_AUTHOR_NAME="$newname"
[ "$GIT_COMMITTER_NAME"="$oldname" ] && GIT_COMMITTER_NAME="$newname"' HEAD
