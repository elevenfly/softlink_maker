#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <libgen.h>

#define LOCAL_FOLDER "/software/local/"
#define BIN_FOLDER "/software/bin/"


/*struct file_name {*/
    /*char* file_name;*/
    /*char* file_path;*/
    /*struct file_name * next_item;*/
/*};*/

/*struct file_name * last_item (struct file_name* start_item) {*/
    /*struct file_name * this_item = start_item;*/
    /*while (this_item->next_item ) {*/
        /*this_item=this_item->next_item;*/
    /*}*/
    /*return(this_item);*/
/*}*/

/*[>do i need to free the structure?<]*/
/*[>I think no<]*/
/*int add_item(struct file_name * head_item, char* file_name, char* file_path)*/
/*{*/
    /*struct file_name this={file_name:file_name,file_path:file_path,next_item=NULL};*/
    /*struct file_name* last_item = last_item(head_item);*/
    /*last_item->next_item=&this;*/
    /*return(0);*/
/*}*/

/*struct file_name * get_file_name_head()*/
/*{*/
    /*struct file_name * head = NULL;*/
    /*return(head);*/
/*}*/



 /*[>for bin file<]*/
/*struct file_name * bin=get_file_name_head();*/
 /*[>for softlink file<]*/
/*struct file_name * sl=get_file_name_head();*/

/*int get_bin_file_list(char* dir_name)*/
/*{*/
    /*char path[100];*/

    /*strcpy(path, dir_name);*/
    /*int path_length=strlen(path);*/
    /*strcpy(path+path_length,"/bin/");*/

    /*list_dir(path, )*/

/*}*/

int make_symlink(char * filename)
{

    char base[20];
    strcpy(base,basename(filename));

    char sympath[100];
    strcpy(sympath,getenv("HOME"));
    strcat(sympath,BIN_FOLDER);
    strcat(sympath,base);

    /*printf("%s\n%s\n\n",filename,sympath);*/

    symlink(filename,sympath);

    return(0);


}
int find_local_bin_folder(char * dirname)
{
    char this_dir[100];
    strcpy(this_dir,dirname);
    /*int this_dir_len=strlen(this_dir);*/
    /*this_dir[this_dir_len]='/';*/
    /*this_dir[this_dir_len]='\0';*/
    strcat(this_dir,"/bin/");

    int (*make_symlink_p)(char *)=&make_symlink;
    list_dir(this_dir,make_symlink_p);
    /*puts(this_dir);*/
    return(0);

}

int unlink_sym(char * filename)
{
    struct stat buf;
    int x = lstat (filename, &buf);

    if (S_ISLNK(buf.st_mode)){
        remove(filename);
        /*printf("%s\n",filename);*/
    }

    return(0);

}

int list_dir(char* dir_name, int (*behave)(char *))
{
    DIR *dp;
    struct dirent *ep;

    dp = opendir(dir_name);
    if (dp != NULL) {
        while (ep=readdir(dp)) {
            if (!strcmp(ep->d_name,".") || !strcmp(ep->d_name,"..")) {
                continue;
            }
            char this_dir[100];
            strcpy(this_dir,dir_name);
            int this_dir_len=strlen(this_dir);
            this_dir[this_dir_len]='/';
            this_dir[this_dir_len]='\0';
            /*strcat(this_dir,'/');*/
            strcat(this_dir,ep->d_name);
            ( *behave )(this_dir);
        }
    }
     /*else {*/
        /*perror("Couldn't open the directory");*/
    /*}*/

    return (0);
}


int main(void)
{

    /*remove all symlink in the bin folder*/


    char bin_folder[100];
    strcpy(bin_folder,getenv("HOME"));
    strcpy(bin_folder+strlen(bin_folder),BIN_FOLDER);

    mkdir(bin_folder,S_IRUSR | S_IWUSR | S_IXUSR|S_IRGRP |S_IWGRP |  S_IXGRP|S_IROTH |  S_IXOTH);

    int (*unlink_behave)(char *)= &unlink_sym;
    list_dir(bin_folder,unlink_behave);


    /*go through all the local folder*/
    char local_folder[100];
    strcpy(local_folder,getenv("HOME"));
    strcpy(local_folder+strlen(local_folder),LOCAL_FOLDER);

    int (*find_local_bin_folder_p)(char *)= &find_local_bin_folder;
    list_dir(local_folder,find_local_bin_folder_p);
    /*int*/


    return(0) ;
}
