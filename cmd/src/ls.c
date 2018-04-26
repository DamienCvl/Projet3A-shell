#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <limits.h>
#include <dirent.h>
#include "../include/ls.h"
#include "../utils/macro_main.h"

MAIN(ls)

int ls(int argc, char *argv[]) {
  DIR *dirp;
  struct dirent *dptr;
  char *dir;
  struct stat st;
  char path[PATH_MAX];
  struct passwd *userInfo;
  struct group *groupInfo;
  struct tm *timeInfo;

  if (argc == 0) dir = ".";
  else dir = argv[0];

  if (stat(dir, &st) == -1) {
    printf("ls: cannot access '%s': No such file or directory\n", dir);
    return(-1);
  }
  if (S_ISDIR(st.st_mode)) {
    dirp = opendir(dir);
    while (dptr = readdir(dirp)) {
      if (dir[strlen(dir)-1]=='/') sprintf(path, "%s%s", dir, dptr->d_name);
      else sprintf(path, "%s/%s", dir, dptr->d_name);

      if (stat(path, &st) == -1)
        printf("error (%d) %s\n", errno, strerror(errno));
      else {
        if ((st.st_mode & S_IFSOCK)==S_IFSOCK) printf("s"); //socket
        else if ((st.st_mode & S_IFLNK)==S_IFLNK) printf("l"); //symbolic link
        else if ((st.st_mode & S_IFREG)==S_IFREG) printf("-"); //regular file
        else if ((st.st_mode & S_IFBLK)==S_IFBLK) printf("b"); //block device
        else if ((st.st_mode & S_IFDIR)==S_IFDIR) printf("d"); // directory
        else if ((st.st_mode & S_IFCHR)==S_IFCHR) printf("c"); // character device
        else if ((st.st_mode & S_IFIFO)==S_IFIFO) printf("p"); //fifo

        printf("%c", (st.st_mode & S_IRUSR)==S_IRUSR ? 'r' : '-' );
        printf("%c", (st.st_mode & S_IWUSR)==S_IWUSR ? 'w' : '-' );
        printf("%c", (st.st_mode & S_IXUSR)==S_IXUSR ? 'x' : '-' );
        printf("%c", (st.st_mode & S_IRGRP)==S_IRGRP ? 'r' : '-' );
        printf("%c", (st.st_mode & S_IWGRP)==S_IWGRP ? 'w' : '-' );
        printf("%c", (st.st_mode & S_IXGRP)==S_IXGRP ? 'x' : '-' );
        printf("%c", (st.st_mode & S_IROTH)==S_IROTH ? 'r' : '-' );
        printf("%c", (st.st_mode & S_IWOTH)==S_IWOTH ? 'w' : '-' );
        printf("%c", (st.st_mode & S_IXOTH)==S_IXOTH ? 'x' : '-' );

        printf(" %4zu", st.st_nlink);

        userInfo=getpwuid(st.st_uid);
        printf(" %6s", userInfo->pw_name);

        groupInfo=getgrgid(st.st_gid);
        printf(" %6s", groupInfo->gr_name);

        printf(" %6zu", st.st_size);

        timeInfo=localtime(&st.st_mtime);
        printf("%4d-%02d-%4d %02d:%02d", timeInfo->tm_mon+1, timeInfo->tm_mday, timeInfo->tm_year+1900, timeInfo->tm_hour, timeInfo->tm_min);

        printf(" %s\n", dptr->d_name);
      }
    }
  }
  else {
    printf("%s\n", dir);
  }

  closedir(dirp);
  return(0);
}
