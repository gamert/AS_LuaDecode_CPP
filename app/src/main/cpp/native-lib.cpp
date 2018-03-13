#include <jni.h>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>

#include "xxtea.h"

#define assert(cond, err) if (!(cond)) {printf(err);exit(1);}

//typedef bool (*initWithMPIData_t)(Image*, char *, ssize_t);
//const char* initWithMPIData_mangled = "_ZN7cocos2d5Image15initWithMPIDataEPKhi";

//int main(int argc, char** argv) {
//    assert(argc > 1, "usage: decrypt [encrypted_png]\n");
//
//    Image *img = new Image();
//
//
//}




//typedef bool (*initWithMPIData_t)(Image*, char *, ssize_t);

//const char* initWithMPIData_mangled = "_ZN7cocos2d5Image15initWithMPIDataEPKhi";
typedef int (*_ZN2JM3gdkEPhjS0_Pj)(unsigned char *, unsigned int, unsigned char *, unsigned int *);


extern "C"
JNIEXPORT jstring

JNICALL
Java_com_example_txz_as_1testcpp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    std::string hello = "Hello from C++";
    //
    const char *lua = "/data/local/tmp/Decorator.lua";
    FILE *f = fopen(lua, "rb");
    assert(f != NULL, "File not exists!");

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    printf("Source file size: %ld\n", fsize);
    fseek(f, 0, SEEK_SET);

    char *buf = (char *)malloc(fsize + 1);
    fread(buf, fsize, 1, f);
    buf[fsize] = 0;
    fclose(f);
    //assert(!memcmp(buf, "FXXF01", 6), "File already decrypted~~\n");

//    void* handle = dlopen("/data/local/tmp/libcocos2dlua.so", RTLD_LAZY);
    void* handle = dlopen("libcocos2dlua.so", RTLD_LAZY);
    if (NULL == handle)
    {
        printf("dlopen fail:%s\n", dlerror());
        return env->NewStringUTF(hello.c_str());
    }

    assert(handle != NULL, "libcocos2dlua.so missing or corrupted!\n");

    _ZN2JM3gdkEPhjS0_Pj initWithMPIData_ptr = (_ZN2JM3gdkEPhjS0_Pj)dlsym(handle, "_ZN2JM3gdkEPhjS0_Pj");

    assert(initWithMPIData_ptr != NULL, "Image::initWithMPIData not found\n");
    printf("Image::initWithMPIData found at: %p\n", initWithMPIData_ptr);


    char *key = (char *)malloc(fsize + 1);
    unsigned int fsize2 = fsize+1;
    int res = initWithMPIData_ptr((unsigned char *)buf,fsize,(unsigned char *)key,&fsize2);

    if(res)
    {
        size_t out_len = 0;
        //void * xxtea_decrypt(const void * data, size_t len, const void * key, size_t * out_len);
        char *decrypt_data = (char *)xxtea_decrypt(buf+fsize2, fsize -fsize2 , key, &out_len);
        //result = (void *)xxtea_decrypt((char *)v3 + v8, v4 - v8, &v9, 128);
        //长度为4个组元，4*32=128bit = 16B
        printf("xxtea_decrypt found at: %p ;%d\n", decrypt_data,out_len);
//        if(out_len > 0)
//        {
//            FILE *f2 = fopen("/data/local/tmp/Decorator.txt", "wb");
//            if(f2!=NULL)
//            {
//                fwrite(decrypt_data,1,out_len,f2);
//                fclose(f2);
//            }
//        }
//        else
//        {
//        }

    }


//    initWithMPIData_ptr(img, buf, fsize);
//    printf("Decrypted image %d x %d, raw size %d.\n",
//           img->_width, img->_height, img->_dataLen);

    // 留给大家的思考题
    return env->NewStringUTF(hello.c_str());
}
