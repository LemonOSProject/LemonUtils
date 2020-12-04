#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <vector>

std::vector<FILE*> files;

int main(int argc, char** argv){
    if(argc < 2){
        files.push_back(stdin);
    } else {
        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i], "-") == 0){
                files.push_back(stdin);
                continue;
            }

            FILE* f = fopen(argv[i], "r");

            if(!f){
                fprintf(stderr, "%s: %s: %s\n", argv[0], argv[i], strerror(errno));
                continue;
            }

            files.push_back(f);
        }
    }

    for(FILE*& f : files){
        while(char c = fgetc(f)){
            if(feof(f)){
                break;
            }

            fputc(c, stdout);
        }
    }

    return 0;
}