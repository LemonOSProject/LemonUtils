#include <stdio.h>
#include <getopt.h>
#include <sys/stat.h>
#include <vector>
#include <lemon/filesystem.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <string>

int help = 0;
int inode = 0;
int size = 0;
int listDirectories = 0;
int recursive = 0;

void DisplayEntry(const char* path, struct stat& st){
    std::string entryString = "";

    if(S_ISDIR(st.st_mode)){
        entryString += "\e[38;5;163m"; // Magneta foregrouud
    } else if(S_ISLNK(st.st_mode)){
        entryString += "\e[38;5;208m"; // Orange foregrouud
    } else if(S_ISCHR(st.st_mode)){
        entryString += "\e[38;5;38m"; // Cyan foreground
    } else {
        entryString += "\e[38;5;124m"; // Red foregrouud
    }

    entryString += path;

    puts(entryString.c_str());
}

void DisplayPath(const char* path){
    if(listDirectories){
        struct stat sResult;
        stat(path, &sResult);
        DisplayEntry(path, sResult);
    } else {
        struct stat sResult;
        int ret = stat(path, &sResult);
        if(ret){
            fprintf(stderr, "ls: %s: %s", path, strerror(errno));
            return;
        }

        if(!S_ISDIR(sResult.st_mode)){
            DisplayEntry(path, sResult);
            return;
        } else {
            printf("%s:\n", path);

            int dirfd = open(path, O_DIRECTORY);
            if(dirfd <= 0){
                fprintf(stderr, "ls: %s: %s", path, strerror(errno));
                return;
            }

            int index = 0;
            lemon_dirent_t dirent;
            while(lemon_readdir(dirfd, index++, &dirent)){
                if(recursive){
                    std::string dirPath = path;
                    dirPath.append("/");
                    dirPath.append(dirent.name);

                    DisplayPath(dirPath.c_str());
                } else {
                    std::string dirPath = path;
                    dirPath.append("/");
                    dirPath.append(dirent.name);
                    struct stat sResult;
                    stat(dirPath.c_str(), &sResult);
                    DisplayEntry(dirent.name, sResult);
                }
            }
        }
    }
}

int main(int argc, char** argv){
    
    option opts[] = {
        {"help", no_argument, &help, true},
        {"inode", no_argument, nullptr, 'i'},
        {"size", no_argument, nullptr, 's'},
        {"recursive", no_argument, nullptr, 'R'},
    };
    
    int option;
    while((option = getopt_long(argc, argv, "isdR", opts, nullptr)) >= 0){
        switch(option){
            case 'i':
                inode = true;
                break;
            case 's':
                size = true;
                break;
            case 'd':
                listDirectories = true;
                break;
            case 'R':
                recursive = true;
                break;
            case '?':
                printf("For usage see '%s --help'", argv[0]);
                return 1;
        }
    }

    if(help){
        printf("Usage: %s [options] [directory] [directory2] ...\n\
            --help            Show this help\n\
            -i, --inode       Show file inode numbers\n\
            -R, --recursive   Recursively show directory contents\n\
            -s, --size        Show file sizes\n");
        return 1;
    }

    if(optind >= argc){
        DisplayPath(".");
    } else for(; optind < argc; optind++){
        DisplayPath(argv[optind]);
    }

    return 0;
}