#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "decode.h"

int main(int argc,char* argv[])
{
    //structure names for encode and decode
    EncodeInfo encInfo;
    DecodeInfo decInfo;

    //when only ./a.out is passed
    if(argc==1){
        printf("./a.out: Encoding: ./a.out -e <.bmp file> <.txt file> [output file]\n");
        printf("./a.out: Decoding: ./a.out -d <.bmp file> [output file]\n");
        return e_failure;
    }

    //to find operation type
    if(check_operation_type(argv[1]) == e_encode){
        //do encoding

        //minimum 4 args are required for encoding
        if(argc<4){
            printf("./a.out: Encoding: ./a.out -e <.bmp file> <.txt file> [output file]\n");
            return e_failure;
        }
        
        //for destination file name when passed and should be a .bmp file
        if(argc == 5){
            if(strstr(argv[4],".bmp") == NULL){
                printf("INFO: %s is not a .bmp file!\n",argv[4]);
                return e_failure;
            }
            encInfo.stego_image_fname = argv[4];
        }
        //if not then default file
        else{
            encInfo.stego_image_fname = "staged_img.bmp";
        }
        //for scr file and should be .bmp file
        if((strstr(argv[2],".bmp")) == NULL){
            printf("INFO :%s is not a .bmp file!\n",argv[2]);
            return e_failure;
        }
        encInfo.src_image_fname = argv[2];

        //to check if the data file has any extension
        if(strchr(argv[3],'.') == NULL){
            printf("INFO: %s no extension mentioned!\n",argv[3]);
            return e_failure;
        }
        encInfo.secret_fname = argv[3];

        if(argc == 4){
            printf("INFO: Output File not mentioned. Creating staged_img.bmp as default\n");
        }

        //calling encoding function
        if(do_encoding(&encInfo) == e_success){
            printf("## Encoding Done Successfully ##\n");
        }
    }

    //for decoding
    else if(check_operation_type(argv[1]) == e_decode){
        //decoding
        if(argc<3){
            printf("./a.out: Decoding: ./a.out -d <.bmp file> [output file]\n");
        }
        //if output file is passed take until the .
        if(argc == 4){
            decInfo.file_name = strtok(argv[3],".");
        }
        //else default file is created
        else{
            decInfo.file_name = "decoded";
            decInfo.file_present = 1;
        }
        //to check src file is .bmp or not
        if(strstr(argv[2],".bmp") == NULL){
            printf("INFO: %s is not a .bmp file!\n",argv[2]);
        }
        decInfo.stego_image_fname = argv[2];

        printf("INFO: ## Decoding Procedure Started ##\n");
        //calling decoding function
        if(do_decoding(&decInfo) == e_success){
            printf("INFO: ## Decoding Done Successfully ##\n");
        }
    }

    //anything other than -e or -d
    else{
        printf("Invalid operation!\nGive -e for encoding or -d for decoding\n");
    }
    return 0;
}

//to check operation type
OperationType check_operation_type(char *argv){
        //if -e encode
        if(strcmp(argv,"-e") == 0){
            return e_encode;
        }
        //if -d decode
        else if(strcmp(argv,"-d") == 0 ){
            return e_decode;
        }
        //unsupported
        else{
            return e_unsupported;
        }
}
